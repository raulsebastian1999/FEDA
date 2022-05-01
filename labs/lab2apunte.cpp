#include <iostream>
using namespace std;


// Hoy trabajaremos con la memoria dinámica (Heap memory). 
// Antes los O.S no eran tan seguros, por lo que pasar la memoria del stack, 
//era una gran vulnerabilidad para el sistema.

// Si quisieramos crear una función que retorna un arreglo.
/*
int *function(){
	int arrr[5];
	for(int i = 0; i<5; i++){
		arr[i] = i;
	}
	return arr;
}
*/
//Problema: este arreglo se crea de manera local en la funcion (se destruye cuando termina)
/*
int main(){ 
	int *arr;
	arr = funcion();
	for(int i = 0;i<5; i++){
		cout <<arr[i]<< " ";
	}
	return 0;
}
*/
//Entrega un error, pues la memoria a la que se está accediendo está vacía



// VERSION 2: Usando "new" para la creación de un sólo elemento

/*
int *function(){
	int *p;
	p = new int;  //Asigna espacio en Heap
	*p = 5;
	return p;
}





int main(){
	int *p;
	p = function();
	cout << *p << endl;
	delete p; //No borra el puntero, borra el espacio de memoria
	p = function(); //Ahora el espacio de memoria está vacío
	return 0;
}
*/
//Cada vez que se hace un new, hay que hacer un delete al final

//VERSION 3: Usando new para crear un arreglo 
/*
int *function(){
	int *p;
	p = new int[5];  //Asigna espacio en Heap
	for(int i = 0; i<5; i++){
		p[i] = i;
	}
	return p;
}





int main(){
	int *p;
	p = function();
	for(int i = 0;i<5; i++){
		cout <<p[i] << " ";
	}
	cout <<endl;
	delete[] p;
	return 0;
}

*/
//VERSION 4: Ahora queremos crear una matriz. Para ello, se requiere crear un arreglo de punteros. Cada puntero apuntará hacia un arreglo

/*
int *function(){
	int **p;
	p = new int*[5];  //Asigna espacio en Heap, creando espacio para un arreglo de punteros
	for(int i = 0; i<5; i++){
		p[i] = new int[2];
	}
	return p;
}


//Además, cada fila puede ser de distinto tamaño.


int main(){
	int *p;
	p = function();
	for(int i = 0;i<5; i++){
		cout <<p[i] << " ";
	}
	cout <<endl;
	delete[] p;
	return 0;
}

*/
//Si quisieramos en una matriz convencional intercambiar los valores de dos filas, tendriamos que hacer un swap de cada elemento.
//Para una matriz dinámica, bastaría con intercambiar los punteros respectivos a cada fila.

// EJEMPLO PREVIO 1: Vector Dinámico
/*
int main(){
	int *pv; //Declaramos puntero
	int dim; //Declaramos tamaño del vector

	cout << "Ingresa el tamano del vector" << endl;
	cin>>dim;
	pv = new int[dim]; //Esta linea destina el espacio en Heap para el arreglo entero de tamano dim

	for(int i = 0; i<dim; i++){
		pv[i] = i * i;  //Al elemento en la posicion i le asigna el valor i*i
		cout << pv[i] <<endl;   //imprimir el vector
	}
	delete[] pv;  //borrar la memoria destinada al pv
	return 0;
}	
*/

//EJEMPLO PREVIO 2: Con matrices
/* Como ya vimos, para crear una matriz dinamica debemos crear un doble puntero int** pm
y reservamos la memoria destinada para aquello con new (y delete para liberar).

*/

/*

int main(){
	int **pm; //Crea el puntero a una matriz
	int cols;
	int rows;

	cout <<"Ingresa nro de filas:";
	cin >> rows;

	cout << endl;
	cout <<"Ingresa nro de columnas:";
	cin>> cols;

	pm = new int* [rows];
	for(int i = 0; i<rows; i++){
		pm[i] = new int[cols];
	}

	cout <<"Elementos de la matriz con sus direccinoes"<< endl;
	for(int i = 0; i < rows; i++){
		for(int j = 0; j< cols; j++){
			pm[i][j] = i+j;
			cout << pm[i][j] <<"--_>";
			cout << &pm[i][j] << endl;
		}
		cout<<endl;
	}
	cout <<endl;

	//Ahora elmininamos cada vector de la matriz

	for(int i = 0; i< rows; i++){
		delete[] pm[i];
	}
	// y eliminamos el vector del arreglo 
	delete[] pm;

	return 0; 
}
*/


