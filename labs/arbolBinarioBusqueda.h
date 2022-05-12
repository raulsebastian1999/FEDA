#include<iostream>

//map<int, map<int,string>>

//En el caso de que tengamos un arreglo int  Array[n] y no conocesmo n, se puede usar 
//sizeof
//concatenar tres vectores [1,2,3] + [4,5] + [6]
//creamos un vector nuevo vector<int> v;
//for y v.pushback(arr_i)
//vector<int> v(ar_i)

//vector solamente admite un tipo de dato, pair permite guardar dos tipos de datos
//vector<pair<int,string>>

#ifndef ARBOLBUNARIOBUSQUEDA_H //etiqueta de la clase
#define ARBOLBINARIOBUSQUEDA_H


class Nodo{
public:
	int valor;
	Nodo* izq;
	Nodo* der;
	Nodo* padre;
	Nodo(int valor);
	Nodo(int valor, Nodo *padre);
	~Nodo();



};


//Arbolbinario sin nodos repetidos
class ArbolBinarioBusqueda(){
public:
		ArbolBinarioBusqueda(); //esta vacio y le ingresamos los nodos uno por uno
		~ArbolBinarioBusqueda();
		bool insertar(int valor);
		Nodo *buscar(int valor);  //es una funcion que devuelve un Nodo
		void * inOrder();  //Forma de recorrer un arbol
		Nodo *predecesor(int valor);
private:
	Nodo * raiz;    //puntero a primer nodo
	bool insertar(int valor, Nodo * n);  //devuelve true si se puede insertar o no
	Nodo * buscar(int valor, Nodo * n);  //Buscar devuelve un nodo si es que lo encuentra devuelve una referncia al nodo, sino NUll
 	void inOrder(Nodo * n);  //inOrder desde el nodo *n
	Nodo * mayor(Nodo * n);   

};




#endif