#ifndef __Proyecto__
#define __Proyecto__


#include<iostream>
#include<vector>
#include<fstream>
#include<string>
#include<chrono>
#include<unordered_set>
using namespace std;



vector<string> splitStrings(string str, char dl){ //Función para vectorizar string según delimitador dl (obtenida de https://acervolima.com/divida-a-string-em-substrings-usando-delimitador/)

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






//(dato string, int tipo)
//La clase nodo
struct node{ 
	string data; //posee dos atributos, dato y tipo
	int type;
	//El constructor por defecto, generara el dato " " y tipo -1 (no lo usaremos acá)
	node(){
		data = " ";
		type = -1;
	}
	//El constructor dado un string s y entero tipo, asigna el tipo como type y el s como data
	node(string s, int tipo){
		data = s;
		type = tipo;
	}
	
	//Mas adelante vamos a necesitar hashear nodos, pues los queremos guardar en un unordered_set
	//PAra ello debemos definir una funcion de comparacion
	//En este caso dos nodos son iguales si tienen el mismo tipo y dato

	bool operator==(const node & othernode) const
	{
    	if (this->data == othernode.data && this->type == othernode.type) return true;
   	 	else return false;
  	}
	//Ademas definimos una funcion hash, que se define a partir de la funcion de la STL pero ahora hashea nodos
  	struct HashFunction
  	{
    	size_t operator()(const node & nodo) const
    	{
      	size_t xHash = std::hash<string>()(nodo.data);
      	size_t yHash = std::hash<int>()(nodo.type) << 1;
      	return xHash ^ yHash;
    }
  };
};



bool findvectornode(vector<string> palabras, vector<node> V){
	int L = palabras.size();
	int k = 0;
	for(int i=0; i<V.size(); i++){
		for(int j=0; j<L; j++){
			if(V[i].data == palabras[j]){
				k++;
			}
		}
	}
	if(k==L){
		return true;
	}
	else{
		return false;
	}
}



//Clase de la lista de adyacencia
class nodelist{	

//Tipo 0: TweetID (único)
//Tipo 1: TweetDate 
//Tipo 2: palabras 
//Tipo 3: UserID 
// private:
	//Conjuntos de los nodos ya ingresados

public:
	vector<vector<node>> lista;  //lista es la lista de adyacencia
	vector<node> V; //Vector de los nodos 

	int size = 0; //Cantidad de vertices
	int num_edges = 0; //Cantidad de aristas
	int nodos_tipo0 = 0; //Nodos tipo 0
	int nodos_tipo1 = 0; //Analog
	int nodos_tipo2 = 0;
	int nodos_tipo3 = 0;
		
	//Funcion para añadir nodo
	void addnode(node nodo){  //O(1)
		//No hay que verificar que esté repetida (pues se hace en el .cpp), entonces lo añadimos
			vector<node> aux;  //creamos vector auxiliar de nodos
			aux.push_back(nodo); //le pusheamos el nodo a insertar
			lista.push_back(aux); //y este vector que solo tiene al nodo nodo
			V.push_back(nodo); //lo pusheamos al V y la lista
			size++; //incrementamosla cant de vertices
			if(nodo.type == 0){ //Si son de cierto tipo incrementamos los contadores
				nodos_tipo0++;
			}
			if(nodo.type == 1){
				nodos_tipo1++;
			}
			if(nodo.type == 2){
				nodos_tipo2++;
			}
			if(nodo.type == 3){
				nodos_tipo3++;
			}
	}
	//Método para añadir aristas
	void addedge(node nodo1, node nodo2){ //O(n)
		for(int i = 0; i<V.size(); i++){ //Buscamos el vertice que coincida con nodo 1
			if(V[i].data == nodo1.data && V[i].type == nodo1.type){
				//El indice de nodo1 es i. 
				lista[i].push_back(nodo2); //Y en esa posicion, pusheamos el nodo 2
			}
			//Analogo para nodo 1
			else if(V[i].data == nodo2.data && V[i].type == nodo2.type){
				lista[i].push_back(nodo1);
			}
			num_edges++; //Esto también podría estar dentro del if o elseif
		}

	}
	//Funcion para imprimir grafo, solo para debugeaer
	void print(){
		for(int i = 0; i<size; i++){
			// lista[i][0].index = i;
			cout<<" Nodo "<< i <<" - Tipo" <<lista[i][0].type<<" : "<<lista[i][0].data<<std::flush;
			// if(i == 204){
			// 	cout<<"Camurrictmteodio"<<endl;
			// }
			for(int j = 1; j<lista[i].size(); j++){
				cout<<" -> "<<lista[i][j].data<<" ";
			}
			cout<<"\n"<<std::flush;
		}
	}
	//Entrega la fecha en la que se publicaron más tweets
	void fecha_con_mas_publicaciones(){ //O(n)
		string fecha_de_mas_tweets = ""; //Inicializamos string vacio
		int mayor_dia = 0; //y buscamos el maximo de manera usual
		int index = 0;
		for(int i = 0; i<size; ++i){
			if(lista[i][0].type==1 && lista[i].size()>mayor_dia){
				mayor_dia = lista[i].size();
				fecha_de_mas_tweets = lista[i][0].data;
				index = i;
			}
		}
	 	cout<<"La fecha con más publicaciones fue: "<<fecha_de_mas_tweets<<endl;
	 	cout<<"Se publicaron: "<<mayor_dia-1<< " tweets"<<endl;
	 	cout<<"Almacenado en el nodo "<<index<<endl;
	}


	//Esta función es análoga a la anterior
	void usuario_con_mas_publicaciones(){
		string twittero = "";
		int mayor = 0; //Mayor es el valor de las publicaciones del twittero actual mas twittero (que publicamas)
		int indice = 0; //indice es el indice de ese twittero
		int cant_publicaciones = 0;
		for(int i = 0; i<size; ++i){
			if(lista[i][0].type==3 && lista[i].size()>mayor){
				mayor = lista[i].size();
				twittero = lista[i][0].data;
				indice = i;
			}
		}
		cout<<"El usuario con más publicaciones se encontró en: "<<endl;
		cout<<"En el nodo "<<indice<<" : "<< twittero<<endl;
		cout<<"y publicó "<<mayor - 1<<" publicaciones."<<endl;
	}
	//Funcion para encontrar los usuarios que publicaron cierta palabra
	void users_que_publicaron_la_palabra(string palabra){ //O(n2)
			vector<node> users; //Vector de los usuarios
			int i = 0; //i será el indice de la palabra palabra
			while(lista[i][0].data!=palabra){
				if(i == V.size()-1){
					cout<<"No se encontró la palabra :("<<endl;
					return;
				}
				i++;

			}
			cout<<"i: "<<i<<endl;
			//Aqui i es el index de palabra.
			for(int j = 0;j<lista[i].size(); j++){
				// cout<<lista[i][j].data<<" "<<endl; //Estos son los tweetsID que contienen a la palabra palabra
				for(int k = 0; k<V.size(); k++){ //Ahora buscamos los indices de los TweetsID
					if(lista[k][0].data == lista[i][j].data){ 
						cout<<"k: " <<k<<endl; //En el indice k esta encontramos el tweetID
						for(int m = 0; m<lista[k].size(); m++){ //Ahora, por todos los usuarios que publicaron dicho tweet
							if(lista[k][m].type == 3) //Si son users
								users.push_back(lista[k][m]); //los pusheamos al vector users
						}
					}
				}

			}
			//Duda: ¿Era necesario verificar repeticiones de users? Debería ser un unordered_set?
			// cout<<"Los usuarios que han encontrado algun tweet con esa palabra son"<< users.size()<<endl;
			if(users.size()==0){
				cout<< "Ningún usuario ha publicado algún tweet con esa palabra" << endl;
				return;
			}
			else{
				cout<< endl<<"size de users:"<<users.size()<<endl<<endl;
				cout<<"Los usuarios que han publicado tweets con la palabra "<<palabra<<" son:"<<endl; 
				for(int l = 0; l<users.size(); l++){
					cout<<users[l].data<<endl;
				}
			cout<<endl;
			}
			
	}

	//Esta función  da las fechas en las que se encontraron tweets que contenian las palabras del vector palabras 
	void fechas_palabra(vector<string> palabra){
		unordered_set<node, node::HashFunction> fechas;  //unordered_set que tiene las fechas
		int k=0; //
		for(int i=0; i<size; i++){
				// identificamos los tweets que contienen dichas palabras. luego, 
				// lista[i] es un vector que contiene todos las palabras asociadas
				// 
			if(lista[i][0].type == 0){
				for(int j=0; j<palabra.size(); j++){
					if(findvectornode(palabra,lista[i])){ 
						k++;
						// cout << palabra[j] << endl;
					}
				}
				if(k==palabra.size()){
					// unordered_set<node, node::HashFunction> fechas;
					for(int j=0; j<lista[i].size() ;j++){
						if(lista[i][j].type==1 and !fechas.count(lista[i][j])){
							cout << lista[i][j].data << endl;
							fechas.insert(lista[i][j]);
						}
					}
				}
			}
			k=0; // reiniciamos el contador
		}
		cout << endl;
		cout << "Se encontraron " << fechas.size() << " fechas en que se publicaron tweets que contienen todas las palabras deseadas" << endl;

	}


	void get_num(){
		cout<<"El grafo actual tiene:"<<endl;
		cout<<size<<" vertices,"<<endl;
		cout<<num_edges<<" aristas,"<<endl;
		cout<<nodos_tipo0<<" vertices de tipo 0 (TweetId's),"<<endl;
		cout<<nodos_tipo1<<" vertices de tipo 1 (TweetDate's),"<<endl;
		cout<<nodos_tipo2<<" vertices de tipo 2 (Palabras),"<<endl;
		cout<<nodos_tipo3<<" vertices de tipo 3 (UserID's),"<<endl;
	}
};



#endif
