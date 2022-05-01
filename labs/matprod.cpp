#include <iostream> 
using namespace std;

int **crear_matriz(int n){
	int **mat = new int*[n];
	for(int i = 0; i<n; i++){
		//Cada fila se rellena con una columna m
		mat[i] = new int[n];  //No se le coloca *  porque es un arreglo de enteros
	}
	return mat;
}

int produco_escalar(int* v1, int* v2, int n){
	int suma = 0;
	for(int i=0;i<n;i++){
		suma = suma + (v1[i])*(v2[i]);
	}
	return suma;
}

int main(){
	int n;
	cout<<"ingrese n:";
	cin>> n;
	//int **mat = new int*[n]; //Cantidad de filas n (Se le coloca * porque es un arreglo de punteros)
	//int **mat2 = new int*[n]; //Segunda matriz a multiplicad
	//int **mat3 = new int*[n]; //La matriz producto
	int **mat1 = crear_matriz(n);
	int **mat2 = crear_matriz(n);
	int **mat3 = crear_matriz(n);

	cout<<"Ingrese los elementos de la matriz mat1:";
	for(int i = 0; i<n; i++){
		for(int j = 0; j<n; j++){
			cin>>mat1[i][j]; 
		}
	}

	cout<<"Ingrese los elementos de la matriz mat2:";
	for(int i = 0; i<n; i++){
		for(int j = 0; j<n; j++){
			cin>>mat2[i][j]; 
		}
	}

	//Creamos puntero con las columnas de B (la idea es trasponerla)
	int **colB = crear_matriz(n);

	for(int i = 0; i<n; i++){
		for(int j = 0;j<n; j++){
			colB[i][j] = mat2[j][i];
		}
	}

	for(int i = 0; i<n; i++){
		for(int j = 0; j<n;j++){
			mat3[i][j] = produco_escalar(mat1[i],colB[j],n);
		}
	}
	cout<<endl;
	cout<<"La matriz del producto es"<<endl;
	for(int i = 0; i<n; i++){
		for(int j = 0; j<n; j++){
			cout<<mat3[i][j]<<" ";
			
		}
		cout<<endl;
	}

	return 0;
}
