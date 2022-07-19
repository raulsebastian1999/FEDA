#ifndef __Proyecto__
#define __Proyecto__


#include<iostream>
#include<vector>
#include<fstream>
#include<string>
#include<chrono>
#include<unordered_set>
using namespace std;



vector<string> splitStrings(string str, char dl){

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

// bool findvector(vector<string>, vector<>)



struct datarow{
	string tweetID;
	string tweetDate;
	string tweetText;
	string userID;
	datarow(){} //constructor por defecto
	datarow(vector<string> linestring){ //constructor a partir de vector de strings
		tweetID = linestring[0];
		tweetDate = linestring[1];
		tweetText = linestring[2];
		tweetID = linestring[3];
	}
	// ~datarow();
	void print(){
		cout<<tweetID<<" "<< tweetDate<<" "<<tweetText<<" "<<userID<<endl;
	}

};



//(dato string, int tipo)
struct node{
	string data;
	int type;

	node(){
		data = " ";
		type = -1;
	}
	node(string s, int tipo){
		data = s;
		type = tipo;
	}

	string get_data(){
		return data;
	}
	int get_type(){
		return type;
	}

	// int get_index(){
	// 	return index;
	// }

	bool operator==(const node & othernode) const
	{
    	if (this->data == othernode.data && this->type == othernode.type) return true;
   	 	else return false;
  	}

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
	vector<vector<node>> lista;
	vector<node> V; //Vector de los nodos

	int size = 0;
	int num_edges = 0;
	int nodos_tipo0 = 0;
	int nodos_tipo1 = 0;
	int nodos_tipo2 = 0;
	int nodos_tipo3 = 0;
	
	void addnode(node nodo){
		//No hay que verificar que esté repetida, entonces lo añadimos
			vector<node> aux;
			aux.push_back(nodo);
			lista.push_back(aux);
			V.push_back(nodo);
			size++;
			if(nodo.type == 0){
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
	//IMagineasreas que tenemos nodo.index
	//Así, nodo1.index = i
	void addedge(node nodo1, node nodo2){ //O(n)
		for(int i = 0; i<V.size(); i++){
			if(V[i].data == nodo1.data && V[i].type == nodo1.type){
				//El indice de nodo1 es i. 
				lista[i].push_back(nodo2);
			}
			else if(V[i].data == nodo2.data && V[i].type == nodo2.type){
				lista[i].push_back(nodo1);
			}
			num_edges++;
		}

	}

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

	void fecha_con_mas_publicaciones(){ //O(n)
		string fecha_de_mas_tweets = "";
		int mayor_dia = 0;
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



	void usuario_con_mas_publicaciones(){
		string twittero = "";
		int mayor = 0;
		int indice = 0;
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

	void users_que_publicaron_la_palabra(string palabra){
			vector<node> users;
			vector<node> tweets;
			int i = 0;
			while(lista[i][0].data!=palabra){
				// cout<<"i: "<<i<<endl;
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
				for(int k = 0; k<V.size(); k++){
					if(lista[k][0].data == lista[i][j].data){
						cout<<"k: " <<k<<endl; //En el indice k esta encontramos el tweetID
						for(int m = 0; m<lista[k].size(); m++){
							if(lista[k][m].type == 3)
								users.push_back(lista[k][m]);
						}
					}
				}

			}
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


	void fechas_palabra(vector<string> palabra){
		// cout << "buscando palabra" << endl;
		// vector<node> TwID;
		// int l=0;
		unordered_set<node, node::HashFunction> fechas;
		int k=0;
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