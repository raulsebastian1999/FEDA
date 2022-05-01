#include <iostream>
using namespace std;

void duplicar_arr(int **arr, int &tam){
	int *newArr = new int[2*tam];
	//Ahora tenemos que rellenar este arreglo
	for(int i = 0; i<tam; i++){
		newArr[i] = (*arr)[i]:
	}
	for(int i = 0; i<tam; i++){
		newArr[i+tam] = (*arr)[i]:
	}
	for(int i = 0; i<2*tam; i++){
		cout << newArrr[i]<<" "; 
	}
	delete[] (*arr);
	(*arr) = newArr;
	tam = tam*2;
}

int main(){
	int *p;
	p = new int[5]{10, 7, 15, 3, 11};
	duplicar_arr(&p, tam);
}
