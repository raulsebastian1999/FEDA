#include <iostream>
using namespace std;


int *encontrar_num(int arr[], int num, int tam){
	int *ptr = NULL
	for(int i = 0; i<tam; i++){
		if(arr[i]== num){
			//ptr = &arr[i];  Esta es la primera opción
			return arr + i; // Al sumarle un número nos desplaza i bytes (segun tipo de dato)
			break;
		}
	}
	return ptr;
}



int main(){
	// int *p = encontrar_num()
	int arr[] = {1634496328,185318128,21912204};
	int n = 3;
	char *ptr = (char *)arr;

	for(int i = 0;i<n*4; i++){
		cout << *ptr;
		ptr = ptr + 1; // = ptr++
	}
}



int a = 5, b = 7;
int *p1 = &a; // p1 es la direccino d ea
int *p2 = p1;
int **ppt = &p1; // ppt apunta a la direccion de p1


*p1 = b + *p2 // a = 7 + 5
// Ahora los valores son a = 12, b = 7, p1 = &a, p2=&a, ppt = &p1
*ppt = &b;

b = 41 +a;


func(int &a, int *b, int c)  //Al colocarle un ampersand antes de a, significa que le vamos a pasar una referencia de memoria (un entero)
a += *b-2;
c *= 8-a;
*b = c * 2;
a = a + b;

