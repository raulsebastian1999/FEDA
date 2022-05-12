#include "arbolBinarioBusqueda.h"


///METODOS DE LA CLASE NODO

Nodo::Nodo(int valor){ //Constructor nodo raiz

	izq = NULL;
	der = NULL;
	padre = NULL;
	this ->valor = valor; //el valor de la derecha es el de arriba en la funcion y el de la izquierda es el de la clase;

}


//constructor nodo no raiz

Nodo::Nodo(int valor, Nodo* padre){
	izq = NULL;
	der = NULL;
	this->padre = padre;
	this -> valor = valor;
}


//destructor

Nodo::~Nodo(){
	delete izq;
	delete der;
}




//METODOS DE LA CLASE ARBOLBINARIOBUSQUEDA

ArbolBinarioBusqueda::ArbolBinarioBusqueda(){
	raiz = NULL;
}

ArbolBinarioBusqueda::~ArbolBinarioBusqueda(){
	//Eliminar todos los rodos hacia abajo (implementar, falta borrar todos los nodos para abajo)
	delete raiz;
}



//Publico: Insertar un valor en el arbol
bool ArbolBinarioBusqueda::insertar(int valor){
	if(raiz == NULL){
		raiz = new Nodo(valor);
		return true;

	}
	return insertar(valor, raiz);
}	

//Privado: insertar un nodo no raiz solo si n!= NULL
bool ArbolBinarioBusqueda::insertar(int valor, Nodo *n){
	//Caso base si el valor está repetido no se inserta
	if(valor == n ->valor){ //se está accediendo a la clase por referencia, por eso es flecha (tenemos un puntero al nodo, no el nodo original)
		return false;
	}


	//Si el valor a insertar es menor al del nodo, hacia la izquierda
	if(valor < n -> valor){
		if(n->izq == NULL){ //si el nodo n no tiene hijo izquierdo lo ingresamos ahi
			n->izq = new Nodo(valor,n);
			return true;
		}

		//si no está vacío, bajamos hacía la izquierda e intentamos insertar
		return insertar(valor, n->izq);
	}


	//Si el valor a insertar es mayor al del nodo, vemos hacia la derecha
	if(n-> der == NULL){
		n ->der = new Nodo(valor, n);
		return true;
	}


	return insertar(valor, n->der);

}


//Public buscar el valor en el arbol, NuLL si no esiste

Nodo *ArbolBinarioBusqueda::buscar(int valor){
	return buscar(valor, raiz);
}


//Private busca el valor en un nodo, si no es, baja hasta llegar a una hoja

Nodo *ArbolBinarioBusqueda::buscar(int valor, Nodo *n){
	//Caso base
	//si es una hoja o raiz, el valor no existe
	if(n == NULL)
		return NULL;

	//Si encontramos el valor, retornamos la direccion del nodo
	if(n -> valor == valor)
		return n;
	//Casos recursivos
	if(valor <n ->valor);
		return buscar(valor, n->izq);


	return buscar(valor, n->der);
}


//public: Imprimir arbol in Order
void ArbolBinarioBusqueda::inOrder(){
	std::cout<< "In Order:" << std::endl;
	inOrder(raiz);
	std::cout<< std::endl;
}


void ArbolBinarioBusqueda::inOrder(Nodo *n){
	if (n == NULL)
		return;
	inOrder(n->izq);
	std::cout<<n -> valor << " ";
	inOrder(n -> der);
}