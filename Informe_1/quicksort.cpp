#include<iostream>
using namespace std;

//Funciones Utiles para recibir arreglos por la terminal
void swap(long *r, long *s){
	long aux = *r;
	*r = *s;
	*s = aux;
}



void imprimir_arreglo(long *arr, int size){
	for(int i = 0; i<size; i++){
		cout<<arr[i]<<" ";
	}
	cout<<endl;
}

long *pedir_arreglo(int size){
	long *arr = new long[size];
	cout<<"Ingrese los elementos del arreglo"<<endl;
	for(int i = 0; i<size; i++){
		cin>>arr[i];
	}

	return arr;
	delete[] arr;

}



////////QUICK SORT ////////
/* Recordemos primero el quick sort
Tenemos un arreglo v de n elementos

sea  p = una posicion cualquiera entre 0 y n-1 (nuestro pivote)
Supongamos spdg p = n-1. En tal caso, el algoritmo quicksort es
para i = 0; i<n; i++
	si v[i]>v[p];
		swap(&v[i], &v[p]);
		p = i; (cambiamos el pivote a i)
	hacemos quicksort con el nuevo pivote i
	hacemos quicksort con v desplazado p+1 y n-p-1

*/


void quicksort(long* v, int n)
{
	long p = v[n-1]; //Tomamos como pivote el valor de v[n-1]
	int index = 0; //index sera el indice del elemento mas grande
	for(int i = 0; i < n-1; i++){ //vamos desplazando todos los elementos
		//mas grandes que el pivote a la posicion del actual elemento mas grande
		//asi al final de este for el index guardara el elemento mas grande
		if(v[i]<p){		//Si v[i] es mas pequeno que p,  
			swap(&v[index], &v[i]); 
				index++; //y aumentamos index
                }
        }
        swap(&v[index],&v[n-1]); //intercambiamos el elemento mas grande con el pivote
        if(index>1){ //si el elemento mas grande no es el extremo izquierdo
                quicksort(v, index);}  //hacemos quicksort entre v e index (pues a la derecha de index ya esta ordenado)
        if(n-index-1 > 1){ //si 
                quicksort(v+index+1, n-index-1);} 

}
















int main(){
	int size;
	cout<<" Ingrese el tamano del arreglo"<<endl;
	cin>>size;
	long *arr = pedir_arreglo(size);
	
	quicksort(arr, size);
	//swap(&arr[0],&arr[1]);


	imprimir_arreglo(arr, size);
	cout<<endl;

	


	return 0;
}