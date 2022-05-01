#include<iostream>
#include <chrono>
#include <unistd.h>


using namespace std;


////// PREAMBULO //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Creamos la funcion que pide el espacio para guardar una matriz de m x n
//(m filas y n columnas) como un arreglo de m elementos, en el que cada uno de ellos
//apunta a otro arreglo de n elementos

double **crear_matriz(int m, int n){
	double **mat = new double *[m];  
	for(int i = 0; i<m; i++){
		mat[i] = new double[n];
	}
	return mat; 
	
}

//Sobrecargamos esta funcion
double **crear_matriz(int n){
	double **mat = new double *[n];  
	for(int i = 0; i<n; i++){
		mat[i] = new double[n];
	}
	return mat; 
	
}

//Esta funcion despliega en la pantalla los elementos  de una matriz matt de "filas" filas y "columnas" columnas
void imprimir_matriz(double **mat, int filas, int columnas){
	for(int i = 0; i<filas; i++){
		for(int j = 0; j<columnas; j++){
			cout<<mat[i][j]<<" ";
		}
	cout<< endl;
	}	
}



//Esta funcion calcula el producto de matrices de manera clasica. Es un algoritmo cubico pues
//coniste en un triple for anidado con una asignacion  y suma (orden constante) en el interior
double **producto_matrices(double **A,int mA, int nA, double **B, int mB, int nB){
	if(nA!=mB){
		cout<<"Las matrices no se pueden multiplicar"<<endl;
		return {};
	}

	int mC = mA;
	int nC = nB;

	double **C = crear_matriz(mC,nC);
	for(int i = 0; i<mC;i++){
		for(int j = 0; j<nC;j++){
			C[i][j] = 0;
			for(int k = 0; k<nA; k++){
				C[i][j] = C[i][j] + A[i][k]*B[k][j];
			}

		}
	}
	return C;
	delete[] C;
}


//Para el algoritmo cubico que aprovecha la localidad de los datos, usarmeos la funcion producto escalar
double produco_escalar(double* v1, double* v2, int n){
	double suma = 0;
	for(int i=0;i<n;i++){
		suma = suma + (v1[i])*(v2[i]);
	}
	return suma;
}

//Este es el algoritmo cubico que aprovecha la localidad de los datos. Para ello, asumimos que la matriz B viene dada transpuesta 
//(se lee al reves al momento de ingresarla, de modo que no significa trabajo extra con respecto al algoritmo clasico)
double **pr_mat_optimizado(double **A, int mA, int nA, double **B, int mB, int nB){
	if(nA!=mB){
		cout<<"Las matrices no se pueden multiplicar"<<endl;
		return {};
	}

	int mC = mA;
	int nC = nB;

	double **C = crear_matriz(mC,nC);

	for(int i = 0; i<mC; i++){  //Para realizar al producto calculamos C_ij como la fila i de la matriz A producto punto con la columna j de la matriz B (que en este caso, como la matriz viene transpuesta, coincide con la fila j)
		for(int j = 0; j<nC;j++){
			//C[i][j] = produco_escalar(A[i],B[j],nA); //si usamos la funcion producto escalar
			C[i][j] = 0;
			for(int k = 0; k<nA; k++){
				C[i][j] = C[i][j] + A[i][k]*B[j][k];
			}
		}
	}

	return C;

}

///// FUNCIONES PARA STRASSEN 
//solo las haremos para funciones cuadradas, pues probaremos strassen en potencias cua
double **sumar_matrices(double **A, double **B, int m, int n){
	double **SUM = crear_matriz(m, n);
	for(int i = 0; i<m;i++){
		for(int j = 0; j<n; j++){
			SUM[i][j] = A[i][j] + B[i][j];
		}
	}
	return SUM;
}



double **prod_matriz_por_escalar(double **A, double lambda, int m, int n){
	double **SCALAR = crear_matriz(m, n);
	for(int i = 0; i<m;i++){
		for(int j = 0; j<n; j++){
			SCALAR[i][j] = lambda*A[i][j];
		}
	}
	return SCALAR;
}


//Esta funcion entrega la matriz AB calculada segun el algoritmo de Strassen
double **STRASSEN(double **A, int mA, int nA, double **B, int mB, int nB){



	//fondo de la recursividad: 
	int mC = mA;
	int nC = nB;
	double **C_strassen = crear_matriz(mC, nC);
	
	
	
	if(mA == 2 && nA == 2){

		double M1, M2, M3, M4, M5, M6, M7;
   		double C11, C12, C21, C22;
    	M1 = (A[0][0]+A[1][1])*(B[0][0]+B[1][1]);
    	M2 = (A[1][0]+A[1][1])*B[0][0];
    	M3 = A[0][0]*(B[0][1]-B[1][1]);
    	M4 = A[1][1]*(B[1][0]-B[0][0]);
    	M5 = (A[0][0]+A[0][1])*B[1][1];
    	M6 = (A[1][0]-A[0][0])*(B[0][0]+B[0][1]);
    	M7 = (A[0][1]-A[1][1])*(B[1][0]+B[1][1]);

    	C11 = M1+M4-M5+M7;
    	C12 = M3+M5;
    	C21 = M2+M4;
    	C22 = M1-M2+M3+M6;

    	C_strassen[0][0] = C11;
    	C_strassen[0][1] = C12;
    	C_strassen[1][0] = C21;
    	C_strassen[1][1] = C22;

    	return C_strassen;

	}
	else{

	
	int mAreduced = mA/2;
	int nAreduced = nA/2;
	int mBreduced = mB/2;
	int nBreduced = nB/2;



	

	

	//Ahora las creamos
	double **A11 = crear_matriz(mAreduced,nAreduced);
	double **A12 = crear_matriz(mAreduced,nAreduced);
	double **A21 = crear_matriz(mAreduced,nAreduced);
	double **A22 = crear_matriz(mAreduced,nAreduced);

	double **B11 = crear_matriz(mBreduced,nBreduced);
	double **B12 = crear_matriz(mBreduced,nBreduced);
	double **B21 = crear_matriz(mBreduced,nBreduced);
	double **B22 = crear_matriz(mBreduced,nBreduced);
	
	//Ahora las rellenamos

	for(int i = 0; i<mAreduced; i++){
		for(int j = 0;j<nAreduced; j++){
			A11[i][j] = A[i][j];
			A12[i][j] = A[i][j+nAreduced];
			A21[i][j] = A[i+mAreduced][j];
			A22[i][j] = A[i+mAreduced][j+nAreduced];
		}
	}


	for(int i = 0; i<mBreduced; i++){
		for(int j = 0;j<nBreduced; j++){
			B11[i][j] = B[i][j];
			B12[i][j] = B[i][j+nBreduced];
			B21[i][j] = B[i+mBreduced][j];
			B22[i][j] = B[i+mBreduced][j+nBreduced];
		}
	}

	//Continuando con STRASSEN, calculamos las submatrices

	double **M1 = crear_matriz(mAreduced, nBreduced);
	double **M2 = crear_matriz(mAreduced, nBreduced);
	double **M3 = crear_matriz(mAreduced, nBreduced);
	double **M4 = crear_matriz(mAreduced, nBreduced);
	double **M5 = crear_matriz(mAreduced, nBreduced);
	double **M6 = crear_matriz(mAreduced, nBreduced);
	double **M7 = crear_matriz(mAreduced, nBreduced);

    double **C11 = crear_matriz(mAreduced, nBreduced);
    double **C12 = crear_matriz(mAreduced, nBreduced);
	double **C21 = crear_matriz(mAreduced, nBreduced);
	double **C22 = crear_matriz(mAreduced, nBreduced);




	M1 = STRASSEN(sumar_matrices(A11,A22, mAreduced, nAreduced), mAreduced, nAreduced,
		sumar_matrices(B11, B22, mBreduced, nBreduced), mBreduced, nBreduced);

	M2 = STRASSEN(sumar_matrices(A21, A22, mAreduced, nAreduced), mAreduced, nAreduced, 
		B11, mBreduced, nBreduced);

	M3 = STRASSEN(A11, mAreduced, nAreduced, sumar_matrices(B12,
		prod_matriz_por_escalar(B22, -1, mBreduced, nBreduced), mBreduced,
		 nBreduced), mBreduced, nBreduced);

	M4 = STRASSEN(A22, mAreduced, nAreduced, sumar_matrices(B21,
		prod_matriz_por_escalar(B11, -1, mBreduced, nBreduced), mBreduced,
		 nBreduced), mBreduced, nBreduced);

	M5 = STRASSEN(sumar_matrices(A11,A12, mAreduced, nAreduced),
		mAreduced, nAreduced, B22, mBreduced, nBreduced);

	M6 = STRASSEN(sumar_matrices(A21, prod_matriz_por_escalar(A11,-1, mAreduced, nAreduced),
	mAreduced, nAreduced), mAreduced, nAreduced, sumar_matrices(B11, B12, mBreduced, nBreduced), mBreduced,
	nBreduced);

	M7 = STRASSEN(sumar_matrices(A12,
		prod_matriz_por_escalar(A22, -1, mAreduced, nAreduced), mAreduced,
		 nAreduced), mAreduced, nAreduced, sumar_matrices(B21, B22, mBreduced, nBreduced), mBreduced, nBreduced);
		  
	C11 = sumar_matrices(M1, M4, mAreduced, nBreduced);
	C11 = sumar_matrices(C11, M7,mAreduced, nBreduced);
	C11 = sumar_matrices(C11,prod_matriz_por_escalar(M5,-1, mAreduced, nBreduced),mAreduced, nBreduced);

	C12 = sumar_matrices(M3,M5, mAreduced, nBreduced);
	C21 = sumar_matrices(M2, M4, mAreduced, nBreduced);


	C22 = sumar_matrices(M1, M3, mAreduced, nBreduced);
	C22 = sumar_matrices(C22, M6, mAreduced, nBreduced);
	C22 = sumar_matrices(C22, prod_matriz_por_escalar(M2,-1, mAreduced, nBreduced), mAreduced, nBreduced);



	//Ahora tenemos que reconstruir la matriz C
	
	
	for(int i = 0; i<mC; i++){
		for(int j = 0; j<nC; j++){
			if(i<mAreduced && j < nBreduced){
				C_strassen[i][j] = C11[i][j];
			}
			if(i<mAreduced && j>=nBreduced){
				C_strassen[i][j] = C12[i][j-nBreduced];	
			}
			
			if(i>=mAreduced && j<nBreduced){
				C_strassen[i][j] = C21[i-mAreduced][j];	
			}

			if(i>=mAreduced && j>=nBreduced){
				C_strassen[i][j] = C22[i-mAreduced][j-nBreduced];	
			}
			
		}
	}
	delete[] A11;
	delete[] A12;
	delete[] A22;
	delete[] A21;

	delete[] B11;
	delete[] B12;
	delete[] B22;
	delete[] B21;
	
	
	delete[] C11;
	delete[] C12;
	delete[] C22;
	delete[] C21;
	delete[] M1;
	delete[] M2;
	delete[] M3;
	delete[] M4;
	delete[] M5;
	delete[] M6;
	delete[] M7;

	return C_strassen;
}
}



//////////// AQUI EMPIEZA EL MAIN ///////////////////////////////////////////
int main(){

	int nA, mA;
	cout<<"Ingrese cant. de filas y columnas de la matriz A:"<<endl;
	cin>>mA;
	cin>>nA;

	double **A = crear_matriz(mA,nA);
	cout<<"Ingresa los elementos de la matriz A"<<endl;

	for(int i = 0; i<mA;i++){
		for(int j = 0; j<nA; j++){
			cin>>A[i][j];
		}
	}
	cout<<endl;

	
	//cout<<"La matriz A es:"<<endl;
	//imprimir_matriz(A, mA, nA);
	
	int nB, mB;
	cout<<"Ingrese cant. filas y columnas de la matriz B:"<<endl;
	cin>>mB;
	cin>>nB;

	double **B = crear_matriz(mB,nB);
	double **B_trans = crear_matriz(mB, nB);
	cout<<"Ingresa los elementos de la matriz B"<<endl;

	for(int i = 0; i<mB;i++){
		for(int j = 0; j<nB; j++){
			cin>>B[i][j]; //Para correr Strassen o el Algoritmo clasico no optimizado
			B_trans[j][i] = B[i][j];
			//cin>>B[j][i]; //Para correr el algoritmo optimizado, al momento de guardar la matriz la hacemos traspuesta
			//de este modo cada columna es guardada en el mismo arreglo, y como la funcion producto escalar funciona a partir de 
			//dos arreglos, al momento de hacer el producto no se realizaran saltos entre posiciones de memoria lejanas

		}
	}
	cout<<endl;
	
	//cout<<"La matriz B es:"<<endl;
	//imprimir_matriz(B, mB, nB);
	

	int mC = mA;
	int nC = nB;

	cout<<endl;
	//cout<<"La matriz AB calculada segun el algoritmo cubico clasico es:"<<endl;
	auto start1 = chrono::steady_clock::now();
	
	double **C_usual = producto_matrices(A, mA, nA, B, mB, nB); //Para el producto usual (cubico no optimizado)

	auto end1 = chrono::steady_clock::now();
	
	cout<<endl;
    cout << "Tiempo de ejecucion del cubico clasico en ms: "
        << chrono::duration_cast<chrono::microseconds>(end1 - start1).count()
        << " ms" << endl;

    cout<<endl;


	//imprimir_matriz(C_usual, nC, mC);
	delete[] C_usual;

	cout<<endl;
	//cout<<"La matriz AB calculada segun el algoritmo cubico modificado es:"<<endl;

	auto start2 = chrono::steady_clock::now();
	double **C_mod = pr_mat_optimizado(A, mA, nA, B_trans, mB, nB); //Para el producto que aprovecha la localidad de los datos
	
	auto end2 = chrono::steady_clock::now();
	
	cout<<endl;
	cout << "Tiempo de ejecucion del cubico optimizado en ms: "
        << chrono::duration_cast<chrono::microseconds>(end2 - start2).count()
        << " ms" << endl;

    cout<<endl;
	//imprimir_matriz(C_mod, mC, nC);
    delete[] C_mod;
	cout<<endl;
	
	//cout<<"La matriz AB calculada segun el algoritmo de Strassen es:"<<endl;
	/*auto start3 = chrono::steady_clock::now();

	double **C_strassen_2 = STRASSEN(A,mA,nA,B,mB,nB);
	
	auto end3 = chrono::steady_clock::now();
	cout<<endl;
	cout << "Tiempo de ejecucion de Strassen en s: "
    << chrono::duration_cast<chrono::microseconds>(end3 - start3).count()
	<< " ms" << endl;
	//imprimir_matriz(C_strassen_2, mC, nC);
	delete[] C_strassen_2;
	*/
	delete[] A;
	delete[] B;
	delete[] B_trans;

	return 0;
}
