#include<iostream>
using namespace std;
//es selection sort no insertion sort

void swap(int *b, int *c) { //Intercambia los elementos de la posición b con la posición c del arreglo a
    int temp = *b;
    *b = *c;
    *c = temp;
}

void print_array(int a[], int n){ //Imprime el arreglo a de tamaño n, separando con espacio
	for(int i = 0; i<n; i++){
		cout<<a[i]<<" ";
	}
	cout<<endl;
}


void selection_sort(int *A, int n){
	int min_index;
	for(int i = 0; i<n; i++){
		min_index = i;
		for(int j = i+1; j<n; j++){
			if(A[min_index]>A[j]){
				min_index = j;

			}
		}
		swap(&A[min_index],&A[i]);
	}

}


int main(){
	int n;
	int min_index;
	cin>>n;
	int *A = new int[n];

	for(int j = 0; j<n; j++){
		cin>>A[j];
	}

	selection_sort(A, n);

	print_array(A, n);
	delete [] A;

}