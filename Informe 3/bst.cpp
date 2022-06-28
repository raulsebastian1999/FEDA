////////  IMPLEMENTACION DEL ARBOL BINARIO DE BUSQUEDA////////

#include<iostream>
#include <string>
#include <fstream> //Lectura de archivo
#include <bits/stdc++.h> //Para definicion de fuincion splitString

//Librerias para la implementacion de la TablaHASH
#include<list>
#include<cstring>
#include <utility>

#include <vector>






using namespace std;




/// Definimos la funcion splitstring que tokeniza el string str, según el delimitador dl y devuelve un vector de string con sus componentes
//Obtenida de: https://www.geeksforgeeks.org/split-string-substrings-using-delimiter/

/////// FUNCIONES PARA LA LECTURA DEL DATASET //////
vector<string> splitStrings(string str, char dl)
{
    string word = "";
 
    // to count the number of split strings
    int num = 0;
 
    // adding delimiter character at the end
    // of 'str'
    str = str + dl;
 
    // length of 'str'
    int l = str.size();
 
    // traversing 'str' from left to right
    vector<string> substr_list;
    for (int i = 0; i < l; i++){
 
        // if str[i] is not equal to the delimiter
        // character then accumulate it to 'word'
        if (str[i] != dl)
            word = word + str[i];
 
        else {
 
            // if 'word' is not an empty string,
            // then add this 'word' to the array
            // 'substr_list[]'
            if ((int)word.size() != 0)
                substr_list.push_back(word);
 
            // reset 'word'
            word = "";
        }
    }
 
    // return the splitted strings
    return substr_list;
}


struct datarow{
	string university;
	string userID;
	string username;
	string numbertweets;
	string friendscount;
	string followerscount;
	string createdate;
	datarow(){} //constructor por defecto
	datarow(vector<string> linestring){ //constructor a partir de vector de strings
		university = linestring[0];
		userID = linestring[1];
		username = linestring[2];
		numbertweets = linestring[3];
		friendscount = linestring[4];
		followerscount = linestring[5];
		createdate = linestring[6];	
	}
	// ~datarow();
	void print(){
		cout<<university<<" "<< userID<<" "<<username<<" "<<friendscount<<" "<<followerscount<<" "<<createdate<<endl;
	}

};

//DEFINIMOS EL TIPO keydata QUE ES UN PAR STRING Y VECTOR DE STRINGS (KEY; VALUE)
typedef pair<string, vector<string>> keydata;

/////////////////////////////////////////////
//////////DEFINICION DE LA CLASE ////////////////////

//PRIMERO NECESITAMOS LA CLASE NODO
class Nodo{
public:
	keydata info; //CADA NODO POSEE UN KEYDATA LLAMADO INFO, (la informacion que representa)
	Nodo *izq; //Ademas de un puntero a  un hijo izqueirdo
	Nodo *der;  // y un punteron a un hijo derecho
	Nodo *padre; //Y un puntero a su padre
	Nodo(keydata info); //UN constructor a partir de la info
	Nodo(keydata info, Nodo*padre); //Y un constructor a partir de la info y un puntero a su padre
	~Nodo(); //Destructor por defecto
	void print(); //Funcion print para debuggeear

};



////AHORA DEFINIMOS LA CLASE BST: BINARY SEARCH TREE o ARBOL DE BUSQUEDA BINARIA

class BST{
public:
	BST(); //Constructor por defecto
	~BST();//destructor por defecto
	bool insertar(keydata info); //Funcion para insertar un par clave valor
	void buscar(string key); //Funcion para buscar por clave
	void inOrder(); //inOrder imprime el arbol InORDER

private: 
	Nodo * raiz; //El nodo raiz del BST
	bool insertar(keydata info, Nodo * n); //La funcion insertar, pero version que requiere el nodo sobre el cual insertamos
	Nodo * buscar(string key, Nodo * n); //funcion buscar pero desde cierto nodo
	void inOrder(Nodo * n); //InOrder desde cierto nodo
};

//CONSTRUCTOR DE NODO A PARTIR DE KEYDATA
Nodo::Nodo(keydata info){
	izq = NULL; //SETEAMOS EL HIJO IZQ DER Y PADRE A NULL y GUARDAMOS LA INFO
	der = NULL;
	padre = NULL;
	this->info = info;
}
//CONSTRUCTOR A PARTIR DE UN PADRE
Nodo::Nodo(keydata info, Nodo * padre){
	izq = NULL; //LO MISMO PERO GUARDAMOS EL PADRE
	der = NULL;
	this -> padre = padre;
	this -> info = info;
}

//PARA IMPRIMIR EL NODO; IMPRIMIMOS SU VALOR
void Nodo::print(){
	cout<<info.second[0]<<" "<<info.second[1]<<" ";
	cout<<info.second[2]<<" "<<info.second[3]<<" ";
	cout<<info.second[4]<<" "<<info.second[5]<<" ";
	cout<<info.second[6]<<endl;
}
//EL DESTRUCTOR DEL NODO BORRA SUS PUNTEROS IZQ DER
Nodo::~Nodo(){
	delete izq;
	delete der;
}


//CONSTRUCTOR POR DEFECTO DE BST SETEA RAIZ A NULL
BST::BST(){
	raiz = NULL;
}

//DESTRUCTOR POR DEFECCTO BORRA RAIZ
BST::~BST(){
	delete raiz;
}





/////INSERTAR: funcion que inserta el keydata. Es O(N) en el peor caso porque habría que retornar insertar(info, raiz)////
bool BST::insertar(keydata info){
	if(raiz == NULL){ 
		raiz = new Nodo(info); //SI el arbol esta vacio, no tiene raiz, asi que definimos un nodo con info como raiz
		return true;
	}
	return insertar(info, raiz); //Sino, lo insertamos desde la raiz
}

//INSERTAR DESDE CIERTO NODO //Es O(N) en el peor caso para un arbol desbalanceado, con N cantidad de datos insertados
bool BST::insertar(keydata info, Nodo * n){ 
	if(info.first == (n->info).first){ //Si el valor está repetido, no se inserta el nodo 
		return false;
	}

	//Si el valor a insertar es menor al del nodo (la key, en sentido lexicografico), hacia la izquierda
	if(info.first< (n ->info).first){
		if(n->izq == NULL){		// Si el hijo izquierdo esta vacio, insertar
			n->izq = new Nodo(info, n);
			return true;
		}
		return insertar(info, n->izq);// Si no está vacio, bajar a la izquierda e intentar insertar

	}
	// Si el nodo no tiene hijo derecho, y llegamos hasta aca es porque el valor a insertar es mayor al nodo
	if(n-> der == NULL){
		n-> der = new Nodo(info, n); //asi que lo insertamos a la derecha del nodo n
		return true;
	}
	//Sino, continuamos bajando por la derecha
	return insertar(info, n->der);
}



//FUNCION PARA BUSCAR A PARTIR DE UNA KEY (STRING)
void BST::buscar(string key){       // O(log(n)) si estuviera balanceado O(n) peor caso
	Nodo * resultado = buscar(key, raiz);  // buscamos a partir de la raiz
	if(resultado == NULL){
		cout<<"No se encontró la clave."<<endl; //si resulta NULL, no esta en el BST
		return;
	}
	else{ //Caso contrario, si está
		cout<<"Si encontramos la clave, y sus valores son: "<<" ";
		cout<<(resultado->info).second[0]<<" "<<(resultado->info).second[1]<<" ";
		cout<<(resultado->info).second[2]<<" "<<(resultado->info).second[3]<<" ";
		cout<<(resultado->info).second[4]<<" "<<(resultado->info).second[5]<<" ";
		cout<<(resultado->info).second[6]<<endl;
	}
}

//FUNCION PARA BUSCAR KEY A PARTIR DEL NODO   
Nodo * BST::buscar(string key, Nodo *n){    // O(log(n)) si estuviera balanceado O(n) peor caso

	// ---- Casos Base ---- //
	// Si es una hoja o raiz, el valor no existe
	if(n == NULL)
		return NULL; 
	// Si encontramos el valor, retornar direccion del nodo
	if((n -> info).first == key)
		return n;
	// ---- Casos Recursivos ---- //
	if(key < (n -> info).first)
		return buscar(key, n -> izq);
	return buscar(key, n -> der);
} 



void BST::inOrder(){
	cout<<"InOrder:" <<endl;
	inOrder(raiz);
	cout<<endl;
}

void BST::inOrder(Nodo * n){
	if(n == NULL) return;
	inOrder(n -> izq);
	cout<< (n -> info).first << " ";
	inOrder(n->der);
}





int main(){
	///LECTURA DEL DATASET /////

	ifstream my_file;  
	my_file.open("universities_followers_2022.csv"); //Abrimos el archivo
	char dl = ';'; //Con el delimitador ;
	string line;	 ///declaramos el string linea
	int cont = 0; //cont sera un contador de las lineas leídas
	int tol = 20000; //tol es la cantidad de lineas que vamos a leer
	tol--; //restamos uno pues empezamos de cero

	getline(my_file, line);//Leeemos la primera fila (de etiquetas)
	vector<string> linestring; //declaramos el vector de strings linestring
	BST arbol; //Declaramos la tabla hash

	float tiempo_insertar = 0;

	while(my_file.good()){ //Para las lineas del archivo csv
		if (cont>tol) break; //si ya leimos la cantidad correcta, break
		string line; //declaramos el string line
		getline(my_file, line); //y le asignamos la linea del archivo
		linestring = splitStrings(line, dl); //Tokenizamos esa linea, y la guardamos como vector en linestring
		datarow data = linestring; //Así, podemos declarar el datarow data con los campos adecuados
		
		keydata info; //declaramos un par (key, valor) info
		info.first = linestring[2]; //cuya primera componente será linestring[2] si queremos que las claves sean username 
		// info.first = linestring[1]; //y linestring[1] si queremos que las claves sean los userID's	
		info.second = linestring; //La segunda componente del par es toda la fila
		auto start = chrono::steady_clock::now();
		arbol.insertar(info); //insertamos el keydata en la tabla hash
		auto end = chrono::steady_clock::now();
		float tiempo1 = chrono::duration_cast<chrono::microseconds>(end - start).count();
		tiempo_insertar = tiempo_insertar + tiempo1;
		cont++;//incrementamos el contador de lineas insertadas/leidas del csv

	}

	cout<<"El tiempo total que tardo insertar "<<tol + 1<<" elementos, fue de "<<tiempo_insertar<<" mircosegundos"<<endl;


 	//Ejemplo de consulta
	// arbol.inOrder();
	// string key = "Issugov";
	// cout<<"La clave a buscar fue: "<<key<<endl;
	// arbol.buscar(key);
	// cout<<endl;
	
	vector<float> tiempos; //Vector que almacenará los tiempos de testeo de la entrada, para buscar
	string key2search;
	cout<<"Ingrese la key del elemento que desea buscar"<<endl;
	while(getline(cin,key2search)){
		cout<<"Ingrese la key del elemento que desea buscar"<<endl;
		if(key2search.empty()) break;

		cout<<"El resultado de buscar fue:" <<endl;
		auto start = chrono::steady_clock::now();
		arbol.buscar(key2search);
		auto end = chrono::steady_clock::now();
		cout<<endl;
		float tiempo2 = chrono::duration_cast<chrono::microseconds>(end - start).count();
		tiempos.push_back(tiempo2);

	}

	float suma = 0;
	cout<<"Los tiempos de inserción fueron: ";
	for(int i = 0; i<tiempos.size(); i++){
		cout<<tiempos[i]<<" ";
		suma+=tiempos[i];
	}
	cout<<endl;
	float promedio = suma/tiempos.size();

	cout<<"Tiempo promedio: "<<promedio<<" microsegundos"<<endl;


	my_file.close();
	return 0;

}
