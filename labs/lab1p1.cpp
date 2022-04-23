#include <iostream>
using namespace std;

int suma(int a, int b){
	int res = a + b;
	return res;
}


int *encontrar_num_(int *arr, int num, int tam){
	for(int i = 0; i<tam; i++){
		cout << arr[i] << endl;
	}	
	return NULL;
	// si arr = {1,7,2,9,10,9}
	// num = 9
}
int main(){
	//int arr[] = {1,7,2,9,10,9};
	//encontrar_num_(arr,9,6);


	int arr[] = {1634496328,1853181216, 2191204}
	char *p = (char *)arr;   // Apunta exactamente a la misma direccion, pero cuando le pidamos que avance a partir de una dirección, no avanzará 4 bytes, sino que solo avanzará uno
	cout << arr[0] <<endl;
	cout << p[0] << endl;
	return 0;
}
