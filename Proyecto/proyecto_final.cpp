#include<iostream>
#include<vector>
#include<fstream>
#include<string>
#include<chrono>
#include<unordered_set>
using namespace std;

#include "Grafo_Proyecto.h"


int main(){
	ifstream my_file;  
	my_file.open("dataset-sin-stop-words.csv"); //Abrimos el archivo
	char dl = ','; //Con el delimitador ;
	string line;	 ///declaramos el string linea
	int cont = 0; //cont sera un contador de las lineas leídas
	int tol = 5000; //tol es la cantidad de lineas que vamos a leer
	tol--; //restamos uno pues empezamos de cero
	getline(my_file, line);//Leeemos la primera fila (de etiquetas)
	vector<string> linestring; //declaramos el vector de strings linestring
	//Aqui definir los conjuntos
	unordered_set<node, node::HashFunction> nodos1; //Unordered_set que almacenará los nodos tipo1, para evitar verificar que ingresemos repetidos
	unordered_set<node, node::HashFunction> nodos2; //Analogo
	unordered_set<node, node::HashFunction> nodos3; //Analogo
	//No necesitamos uno para tipo 0 pues cada fila tiene TweetID distinto
	

	nodelist Lista; //Creamos nuestro grafo con lista de adyacencia Lista

	// Inicializamos el tiempo de construcción del grafo
	auto start = chrono::steady_clock::now();

	while(my_file.good()){ //Para las lineas del archivo csv
		if (cont>tol) break; //si ya leimos la cantidad correcta, break
		string line; //declaramos el string line
		getline(my_file, line); //y le asignamos la linea del archivo
		linestring = splitStrings(line, dl); //Tokenizamos esa linea, y la guardamos como vector en linestring
		// datarow data = linestring; //Así, podemos declarar el datarow data con los campos adecuados
		
		node nodo0, nodo1, nodo3;  //Declaramos los 3 tipos de nodo
		nodo0.data = linestring[0]; //El nodo 0 (nodo de tipo 0) es el primer elemento del vector linestring (TweetID)
		nodo0.type = 0; //Asignamos el tipo 0
		Lista.addnode(nodo0); //y lo añadimos a la lista
	
		nodo1.data = linestring[1];
		nodo1.type = 1;

		nodo3.data = linestring[3];
		nodo3.type = 3;
		//Si no se ha ingresado el nodo1, lo insertamos al unordered_set y a la lista
		if(!nodos1.count(nodo1)){
			nodos1.insert(nodo1);
		// 	//Sabemos que el nodo no estaba ingresado. Entonces, lo insertamos a la lista de adyacencia
			Lista.addnode(nodo1);
		}
		//Añadimos la arista respectiva entre el nodo de tipo 0 (TweetID) y el nodo de tipo 1 (TweetDate)
		Lista.addedge(nodo0, nodo1);
		//Analogo para nodo tipo 3
		if(!nodos3.count(nodo3)){
			nodos3.insert(nodo3);
			Lista.addnode(nodo3);
		}
		Lista.addedge(nodo0,nodo3);
	
		//Las lineas anteriores ingresan todo menos las palabras del tweettext.
		//Para las palabras del tweet, las separamos segun el espacio
		vector<string> palabras_tweet = splitStrings(linestring[2],' '); //Separar tweettetxt en vector de palabras
		//Problema estamos ingresando repetidas
		
		for(int i = 0; i<palabras_tweet.size(); i++){ //Por cada palabra en el tweet text 
			node nodoaux; //Creamos un nodo auxiliar
			nodoaux.data = palabras_tweet[i]; //A ese nodo le asignamos como dato el valor de la palabra i
			nodoaux.type = 2; //y tipo 2
			if(!nodos2.count(nodoaux)){ //Si no esta el nodo en el conjunto, lo ingresamos
				nodos2.insert(nodoaux);
				Lista.addnode(nodoaux);
			}
			Lista.addedge(nodo0,nodoaux); //Añadimos la arista entre el nodo tipo 0 y el nodo palabra
		}


		cont++;//incrementamos el contador de lineas insertadas/leidas del csv

	}

	
	// LINEA COMENTADA QUE SIRVE PARA DESPLEGAR LOS NODOS DEL GRAFO

	cout << endl;
	cout<<"INFORMACIÓN DEL GRAFO:"<<endl;
	cout<< "Nuestro grafo tiene " << Lista.size << " nodos y "<< Lista.num_edges << " aristas" <<endl;
	Lista.get_num();

	// Lista.print();

	auto end = chrono::steady_clock::now();
	cout<<"---------------------------------------------------------------------"<<endl;
	cout << "Tiempo de construcción del grafo: " << chrono::duration_cast<chrono::nanoseconds>(end-start).count() << " x10^-9 segundos"<< endl;
// 

	cout<<"---------------------------------------------------------------------"<<endl;


	

	bool flag = 0;
	vector<string> palabras;
	string palabra;
	cout << "Ingrese palabras que desea saber cuándo se publicaron (termine lista con un cero): ";
	cin >> palabra;
	while(flag==0){
		if(palabra!="0"){
			palabras.push_back(palabra);
			cin >> palabra;
		}
		else{
			flag = 1;
		}
	}
	

	clock_t final_time2;
	double total_time2;
	clock_t start_time2 = clock();

	auto start2 = chrono::steady_clock::now();



	cout << endl;
	Lista.fechas_palabra(palabras);
	cout << endl;

	auto end2 =chrono::steady_clock::now();
// 
	// final_time=clock();
	// total_time = ((double)(final_time2 - start_time2)) / CLOCKS_PER_SEC;


	cout << "Tiempo de búsqueda: " << chrono::duration_cast<chrono::nanoseconds>(end2-start2).count() << " x10^-9 segundos"<< endl;
	cout<<"---------------------------------------------------------------------"<<endl;

	cout<<endl;




	cout << "Ingrese palabra que desee encontrar los usuarios quienes la publicaron: ";
	cin >> palabra;

	auto start3 = chrono::steady_clock::now();
	Lista.users_que_publicaron_la_palabra(palabra);

	auto end3 = chrono::steady_clock::now();
	cout << "Tiempo de búsqueda: " << chrono::duration_cast<chrono::nanoseconds>(end3-start3).count() << " x10^-9 segundos" << endl;
	cout<<"---------------------------------------------------------------------"<<endl;

	cout << endl;
	
	auto start4 = chrono::steady_clock::now();
	Lista.usuario_con_mas_publicaciones();
	auto end4 = chrono::steady_clock::now();

	cout << "Tiempo de ejecución: " << chrono::duration_cast<chrono::nanoseconds>(end4-start4).count() << " x10^-9 segundos" << endl;
	cout<<"---------------------------------------------------------------------"<<endl;


	cout << endl;
	auto start5 = chrono::steady_clock::now();
	Lista.fecha_con_mas_publicaciones();
	auto end5 = chrono::steady_clock::now();

	cout << "Tiempo de ejecución: " << chrono::duration_cast<chrono::nanoseconds>(end5-start5).count() << " x10^-9 segundos" << endl;
	cout << endl;


	
	

	return 0; 
}
