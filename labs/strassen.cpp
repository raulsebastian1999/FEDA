#include <iostream>
using namespace std;


int **crear_matriz(int m, int n){
		int **mat = new int*[m];
		for(int i = 0; i<m; i++){
			mat[i] = new int [n];
		}
		return mat;
}

int **sumar_matrices(int **A, int** B, int n){
	int **C = crear_matriz(n,n);
	for(int i = 0; i<n; i++){
		for(int j = 0; j<n;j++){
			C[i][j] = A[i][j]+B[i][j];
		}
	}
	return C;
	}
/*int *trasponer_fila(int* v, int n){
	int **vtraspuesto = crear_matriz(n,1);
	for(int i = 0; i<n; i++){
		vtraspuesto[1][i] = v[i];
	}
	return *vtraspuesto;
}
*/

int **trasponer(int**A, int m, int n){
	int **At = crear_matriz(n,m);
	for(int i = 0; i<m; i++){
		for(int j = 0; j<n;j++){
			At[i][j] = A[j][i];
		}
	}
	return At;
}

void imprimir_matriz(int **mat, int m, int n){
	
	for(int i = 0; i<m; i++){
		for(int j = 0; j<n; j++){
			cout<<mat[i][j]<<" ";
		}
		cout <<endl;
	}
}


int producto_escalar(int* v1, int* v2, int n){
	int suma = 0;
	for(int i = 0; i<n; i++){
		suma = suma + (v1[i])*(v2[i]);
	}
	return suma;
}





int main(){
	int n1,m1, n2, m2;
	cout<<"Ingrese m1 (cantidad de filas de la matriz A):\n";
	cin>>m1;
	cout<<"Ingrese n1 (cantidad de columnas de la matriz A):\n";
	cin>>n1;
	/*
	cout<<"Ingrese m2 (cantidad de filas de la matriz B):\n";
	cin>>m2;
	cout<<"Ingrese n2 (cantidad de columnas de la matriz B):\n";
	cin>>n2;
	*/
	//Entonces, la matriz producto A*B tiene m1 filas y n2 columnas
	int m, n;
	m = m1;
	n = n2;

	int **A = crear_matriz(m1,n1);
	int **B = crear_matriz(m2,n2);
	//int **C = crear_matriz(m,n);
	//int **mat3 = crear_matriz(n);


	cout<<"Ingrese los elementos de la matriz A:";
	for(int i = 0; i<m1; i++){
		for(int j = 0;j<n1; j++){
			cin>>A[i][j];
		}
	}

	cout<<"\n";
	/*
	cout<<"Ingrese los elementos de la matriz B:";

	for(int i = 0; i<m2; i++){
		for(int j = 0;j<n2; j++){
			cin>>B[i][j];
		}
	}
	*/
	cout<<"La matriz A es:\n";
	imprimir_matriz(A, m1,n1);
	/*
	cout<<"La matriz B es:\n";
	imprimir_matriz(B, m2,n2);
	*/
	int** C = trasponer(A,m1,n1);
	imprimir_matriz(C,n1,m1);
	return 0;

}
