#include <iostream>
using namespace std;

/* Se debe crear la función void duplicar_arr(int *arr, int &tam) la cual recibirá un arreglo dinámico arr el cual deberá ser duplicado. También se debe actualizar el valor de tam correspondientemente.
Ejemplo: 
antes de la llamada a la función: arr = {7,14,6,13,20} , tam = 5
después de la llamada a la función: arr = {7,14,6,13,20,7,14,6,13,20}, tam = 10 */

void duplicar_arr(int **arr, int &tam){
	int *pv;
	//tam = 2*tam;
	pv = new int[tam]; 
	for(int i = 0; i<tam; i++){ 
		cout << pv[i]<<endl;   //imprimir el vector
	}

}

int main(){
	int *p; //Declaramos puntero
	int tam;
	p = new int[5]{10, 7, 15, 3, 11};
	tam = 5;
	for(int i = 0; i<tam; i++){ 
		cout << p[i]<<endl;   //imprimir el vector
	}
	//duplicar_arr(arr, dim)
	//delete[] arr;  //borrar la memoria destinada al arr
	return 0;
}	
