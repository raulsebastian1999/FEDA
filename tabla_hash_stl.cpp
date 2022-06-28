////////  EJEMPLO CON LA TABLA HASH DE LA STL  ////////

#include<iostream>
#include <string>
#include <fstream> //Lectura de archivo
#include <bits/stdc++.h> //Para definicion de fuincion splitString
#include <unordered_map>

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
	unordered_map<string, vector<string>> Tabla; //Declaramos la tabla hash

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
		cout<<Tabla.at(key2search)[0]<<" " <<Tabla.at(key2search)[1]<<" "<<Tabla.at(key2search)[2]<<" ";
		cout<<Tabla.at(key2search)[3]<<" " <<Tabla.at(key2search)[4]<<" "<<Tabla.at(key2search)[5]<<" ";
		cout<<Tabla.at(key2search)[6]<<endl;
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

	cout<<"Size: "<<sizeof(Tabla)<<endl;
	my_file.close();
	return 0;

}
