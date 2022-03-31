#include <iostream>
#include <cstdlib>
#include <string.h>
#include <cstdio>
#include <stdio.h>

using namespace std;
/* Función para calcular el factorial de un número
int f(int n){
	if(n==1){
		return 1;
	}
	
	return f(n-1)*n;

}

 */

/* Explique qué hace la función fun en el siguiente código */
/*
int fun(int a, int b){
	if (b == 0)
		return 1;
	if (b%2 ==0)
		return fun(a*a, b/2);
	return fun(a*a, b/2)*a;
}

int main(){
	int a = 2;
	int b = 4;
	cout << fun(a,b)<< endl;

	return 0;
}

*/ 




/* Cree una función que reciba como uno de sus parámetros una cadena de 
caracteres, y de manera recursiva de vuelta su contenido*/


/* Aun no compila, en proceso
bool esPalindromo(char *p, int n){
	if(n==0 or n==1){
		return(true);
	}
	else{
		if(p[0]==p[n-1]){
			return(esPalindromo(p+1,n-2));
		}
		else{
			return(false);
		}
		
	}
}


void main(){
	printf("Ingrese cadena a verificar");
	char palabra[1000];
	scanf("%s", palabra);
	bool pal = esPalindromo(palabra, strlen(palabra));
	if (pal == true) printf("s\n");
	else{
		printf("No\n");
	}
	return(0);
}

*/


// Primero haremos una función swap de dos caracteres en un arreglo 

#include <string>
#include<cstring>
/*
void swapcaracter(string p, int a, int b){
	char temp = palabra[a];
	palabra[a] = palabra[b];
	palabra[b] = temp; 

}*/
int main(){
	char* palabra;
	cout <<"Ingrese cadena a invertir";
	cin>> palabra;
	/*char temp = palabra[1];
	palabra[1] = palabra[2];
	palabra[2] = temp; */
	cout<< palabra[1] <<endl;

}




