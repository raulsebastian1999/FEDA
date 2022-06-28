////////  IMPLEMENTACION DE TABLA DE HASH ABIERTA, CON SEPARATE CHAINING EN VECTORES ////////

#include<iostream> //Para imprimir 
#include <string>  //Para el manejo de strings
#include <fstream> //Lectura de archivo
#include <bits/stdc++.h> //Para definicion de funcion splitString
#include <vector> //Para manejo de vectores
#include <chrono> //Para la medicion del tiempo
#include <unistd.h> //Para la medicion del tiempo
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



//VECTOR CON NUMEROS PRIMOS, CADA UNO ES CERCANO AL DOBLE DEL ANTERIOR. IDEA OBTENIDA DE AYUDANTIA /////
static const int hash_primos[] = {53, 97, 193, 389, 769, 1543, 3079, 6151, 12289, 24593, 49157};




/////DEFINICION DE LA CLASE TABLAHASHABIERTA //////
class TablaHashAbierta{
public: 

	//// CONSTRUCTOR O(1) //// 
	TablaHashAbierta(){
		size = 0; //inicializamos el tamaño en cero (es el numero de celdas que no estan vacias)
		real_size = 0; //realsize en cero igual (es un indice que indicara el tamaño de la tabla)
		alpha = 0; //factor de carga en cero 
		hash = new vector<vector<keydata>>(hash_primos[0]);//inicializamos la tabla con el tamaño primo mas pequeño (53)
	}
	
	/// DESTRUCTOR O(1) ////
	~TablaHashAbierta(){
		delete hash;
	}

	///(FUNCION PARA DEBUG) DEVUELVE EL INDICE DE HASH DE UN STRING //////////
	int get_hashvalue(string key){
		return hash_foo(key) % hash_primos[real_size];
	}
	int get_size(){
		return size;
	}
	int get_realsize(){
		return hash_primos[real_size];
	}
	float get_alpha(){
		return alpha;
	}
	
	/////Sea n la cantidad de elementos insertados en TablaHashAbierta /////

	/// INSERT: inserta el elemento data = (key, valor) en la tabla. Caso promedio O(1), Mejor caso O(n)   //////////
	bool insert(keydata data){   //Sea n = size(data.first) (tamaño del string)
		//en este caso los elementos a insertar serán dados por la clave (string)
	
		float alpha_plus = (float)(size +1 ) / hash_primos[real_size];   //Calculamos el factor de carga con el nuevo valor de size y real_size
		
		if(alpha_plus > 0.5){  //Si el factor de carga es mayor a 0.5, hacemos resize
			resize();		
		}
		int index = hash_foo(data.first) % hash_primos[real_size]; //hay que tener en consideracion que el first del tipo keydata es la key del datarow
		
		if((*hash)[index].empty()){ //Si insertamos en una celda vacia, incrementamos size
			size++;
		} 
		(*hash)[index].push_back(data); //insertamos data en su posicion
		return true;
	}

	/// BUSCAR: busca el valor cuya clave es key. Si no existe retorna false. Caso promedio O(1), Peor caso O(n)/////
	bool buscar(string key){ 	
		int index = hash_foo(key) % hash_primos[real_size]; //Calcular el indice de la clave key
		for(int i = 0; i<(*hash)[index].size(); i++){ //Recorremos la posicion index en la tabla hash
			if(key.compare((*hash)[index][i].first) == 0){ //Si la clave de alguno de ellos coincide con la clave key son los mismos (supuesto)
				cout<<"CLAVE ENCONTRADA EN TABLA, SU VALOR ES: ";  
				cout<<(*hash)[index][i].second[0]<<" "<<(*hash)[index][i].second[1]<<" ";
				cout<<(*hash)[index][i].second[2]<<" "<<(*hash)[index][i].second[3]<<" ";
				cout<<(*hash)[index][i].second[4]<<" "<<(*hash)[index][i].second[5]<<" ";
				cout<<(*hash)[index][i].second[6]<<endl;
				//Imprimimos el valor y retornamos true

				return true;	
			}
		}
		//Si recorrimos todo el vector de la posicion index y ninguna clave coincidía, no hay ningun elemento con clave key
		cout<<"No encontrado"<<endl; //Return false
		return false;
	}



	//FUNCION HASH: Es una implementación de la función de hash djb2, creada por el Profesor Daniel J. Bernstein. O(1) //////
	unsigned int hash_foo(string key){ //Implementacion de djb2, 
		const char *str = key.c_str();
   		unsigned int hash = 5381;
   		unsigned int i    = 0;

   		for (i = 0; i < key.size(); ++str, ++i){
      		hash = ((hash << 5) + hash) + (*str);
   		}

   		return hash;
	} 

	//FUNCION PRINT PARA DEBUGEAR- IMPRIME LA TABLA ////
	void print(){
		for(int i = 0; i<(*hash).size();i++){
			if((*hash)[i].empty()){
				cout<<"Fila "<<i<<" : "<<"Vacio"<<endl;
			}
			else{
				cout<<"Fila " <<i<< ": ";
				for (auto const& k : (*hash)[i]){
    				cout<<k.first<<" "<<"->";
				}
			cout<<endl;

			}
		}
	}

private:
	int size;  //Size es la cantidad de vectores no nulos en el vector de vectores (*hash)
	int real_size; //real_size es el indice que indica el tamaño total en el mismo vector
	float alpha; //alpha es el factor de carga
	vector<vector<keydata>> *hash; //el vector de vectores que representa a la tabla hash

	//FUNCIÓN RESIZE /////
	void resize(){
		//Creamos una tabla hash auxiliar, de mayor tamaño
		vector<vector<keydata>> *aux = new vector<vector<keydata>>(hash_primos[real_size + 1]); 

		//Copiamos los elementos que ya estaban en la tabla 
		for(int i = 0; i < hash_primos[real_size]; i++){
			if(!(*hash)[i].empty()){
				for(int j = 0; j<(*hash)[i].size(); j++){
					int index = hash_foo((*hash)[i][j].first) % hash_primos[real_size + 1]; //para cada uno de ellos recaclulamos la funcion hash, pues ahora cambia realsize
					(*aux)[index].push_back((*hash)[i][j]);
				}
			}
		}
		//incrementamos uno al realsize, pues ahora el vector sera mas grande
		this -> real_size++;
		//recalculamos el nuevo factor de carga
		this -> alpha = (float)size / hash_primos[real_size];
		delete hash;
		this -> hash = aux;
	}

};


//// FUNCION MAIN ////////



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
	TablaHashAbierta Tabla; //Declaramos la tabla hash

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
		Tabla.insert(info); //insertamos el keydata en la tabla hash
		auto end = chrono::steady_clock::now();
		float tiempo1 = chrono::duration_cast<chrono::microseconds>(end - start).count();
		tiempo_insertar = tiempo_insertar + tiempo1;
		cont++;//incrementamos el contador de lineas insertadas/leidas del csv

	}

	cout<<"El tiempo total que tardo insertar "<<tol + 1<<" elementos, fue de "<<tiempo_insertar<<" mircosegundos"<<endl;

	// //Ejemplo de consulta
	// string key = "106454302";
	
	// // Tabla.print();

	// cout<<"La funcion hash, lleva a "<<Tabla.get_hashvalue(key)<<endl;
	// // delete TablaHashCerrada;
	// cout<<"El resultado de buscar fue:" <<endl;
	// Tabla.buscar(key);

	vector<float> tiempos; //Vector que almacenará los tiempos de testeo de la entrada, para buscar
	string key2search;
	cout<<"Ingrese la key del elemento que desea buscar"<<endl;
	while(getline(cin,key2search)){
		cout<<"Ingrese la key del elemento que desea buscar"<<endl;
		if(key2search.empty()) break;

		cout<<"El resultado de buscar fue:" <<endl;
		auto start = chrono::steady_clock::now();
		Tabla.buscar(key2search);
		auto end = chrono::steady_clock::now();
		cout<<endl;
		float tiempo = chrono::duration_cast<chrono::microseconds>(end - start).count();
		// cout<<tiempo<<endl;;
		tiempos.push_back(tiempo);

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
	cout<<"Size: "<<Tabla.get_size()<<"; "<<"real_size: "<<Tabla.get_realsize()<<endl;
	my_file.close();
	return 0;

}