//Strassen limpio: primero separar en submatrices
#include <iostream>
using namespace std;


int **crear_matriz(int m, int n){
		int **mat = new int*[m];
		for(int i = 0; i<m; i++){
			mat[i] = new int [n];
		}
		return mat;
}


void imprimir_matriz(int **mat, int m, int n){
	
	for(int i = 0; i<m; i++){
		for(int j = 0; j<n; j++){
			cout<<mat[i][j]<<" ";
		}
		cout <<endl;
	}
}

int main(){

	int n,m;
	cout<<"Ingrese m (cantidad de filas de la matriz A):\n";
	cin>>m;
	cout<<"Ingrese n (cantidad de columnas de la matriz A):\n";
	cin>>n;
	
	int **A = crear_matriz(m,n);

	cout<<"Ingrese los elementos de la matriz A:";
	for(int i = 0; i<m; i++){
		for(int j = 0;j<n; j++){
			cin>>A[i][j];
		}
	}

	int mreduced = m/2;
	int nreduced = n/2;
	int **A11 = crear_matriz(mreduced,nreduced);
	int **A12 = crear_matriz(mreduced, nreduced);



	cout<<mreduced<<" "<<nreduced<<endl;

	for(int i = 0; i<mreduced; i++){
		for(int j = 0;j<nreduced; j++){
			A11[i][j] = A[i][j];
			A12[i][j] = A[i][j+mreduced];
		}
	}

	for(int i = 0; i<mreduced; i++){
		for(int j = 0; j<nreduced; j++){
			
		}
	}


	imprimir_matriz(A11,mreduced,nreduced);
	cout<<"\n";
	imprimir_matriz(A12,mreduced,nreduced);
	





	return 0;
}