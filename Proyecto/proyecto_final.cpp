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
	int N=0;
	int E=0;

	getline(my_file, line);//Leeemos la primera fila (de etiquetas)
	vector<string> linestring; //declaramos el vector de strings linestring
	//Aqui definir los conjuntos
	unordered_set<node, node::HashFunction> nodos1;
	unordered_set<node, node::HashFunction> nodos2;
	unordered_set<node, node::HashFunction> nodos3;
	

	nodelist Lista;

	// Inicializamos el tiempo de construcción del grafo
	auto start = chrono::steady_clock::now();

	while(my_file.good()){ //Para las lineas del archivo csv
		if (cont>tol) break; //si ya leimos la cantidad correcta, break
		string line; //declaramos el string line
		getline(my_file, line); //y le asignamos la linea del archivo
		linestring = splitStrings(line, dl); //Tokenizamos esa linea, y la guardamos como vector en linestring
		// datarow data = linestring; //Así, podemos declarar el datarow data con los campos adecuados
		
		node nodo0, nodo1, nodo3; 
		nodo0.data = linestring[0];
		nodo0.type = 0;
		// nodos0.insert(nodo0);
		// if(cont == 2500){
			// auto start6 = chrono::steady_clock::now();
			Lista.addnode(nodo0);
			// auto end6 = chrono::steady_clock::now();
			// cout << "Tiempo de añadir un nodo: " << chrono::duration_cast<chrono::nanoseconds>(end6-start6).count() << " x10^-9 segundos"<< endl;
		// }


		N++;

		nodo1.data = linestring[1];
		nodo1.type = 1;

		nodo3.data = linestring[3];
		nodo3.type = 3;

		if(!nodos1.count(nodo1)){
			nodos1.insert(nodo1);
		// 	//Sabemos que el nodo no estaba ingresado. Entonces, lo insertamos a la lista de adyacencia
			Lista.addnode(nodo1);
			N++;
			// Lista.addedge(nodo0, nodo1);
		}

		// if(cont==2500){
			// auto start7 = chrono::steady_clock::now();
			Lista.addedge(nodo0, nodo1);
			// auto end7 = chrono::steady_clock::now();
			// cout << "Tiempo de añadir una arista: " << chrono::duration_cast<chrono::nanoseconds>(end7-start7).count() << " x10^-9 segundos"<< endl;
		// }

		
		E++;

		if(!nodos3.count(nodo3)){
			nodos3.insert(nodo3);
			Lista.addnode(nodo3);
			N++;
		// 	Lista.addedge(nodo0,nodo3);
		}
		Lista.addedge(nodo0,nodo3);
		E++;
	
		//Las lineas anteriores ingresan todo menos las palabras del tweettext.

		vector<string> palabras_tweet = splitStrings(linestring[2],' '); //Separar tweettetxt en vector de palabras
		//Problema estamos ingresando repetidas

		for(int i = 0; i<palabras_tweet.size(); i++){ //Por cada palabra en el tweet text (para cada palabra no ingresadad debería ser)
			node nodoaux;
			nodoaux.data = palabras_tweet[i];
			nodoaux.type = 2;
			if(!nodos2.count(nodoaux)){ //Si no esta el nodo en el conjunto, lo ingresamos
				nodos2.insert(nodoaux);
				N++;
				Lista.addnode(nodoaux);
			}
			Lista.addedge(nodo0,nodoaux);
			E++;
		}


		cont++;//incrementamos el contador de lineas insertadas/leidas del csv

	}

	// LINEA COMENTADA QUE SIRVE PARA DESPLEGAR LOS NODOS DEL GRAFO

	// int N = nodos0.size()+nodos1.size()+nodos2.size()+nodos3.size();
	cout << endl;
	cout<<"INFORMACIÓN DEL GRAFO:"<<endl;
	cout<< "Nuestro grafo tiene " << N << " nodos y "<< E << " aristas" <<endl;
	Lista.get_num();
	// for(const auto& elem: nodos2){
		// cout<<elem.data<<endl;
	// }
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