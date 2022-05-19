//NOMBRE: Raúl Sebastián Astete Elguin
//Online Judge ID:	1235326
//Estado de solución: ACCEPTED, con tiempo 0.050s
//Sentencia de autoría: La solución a este problema fue realizada de manera independiente, pero con apoyo de foros como stackoverflow para la consulta
//de distintas implementaciones utilizadas. Además se contó con el apoyo del ayudante de la asignatura para resolver consultas, y de una instancia de conversación en pizarra
//con unos compañeros, en la que discutimos algunas formas de abordar el problema.



//Análisis asintótico de la solución: Tiempo: O(n), Espacio: O(n), donde $n = TC$ es la cantidad de casos de prueba (estudiantes) a considerar. 
//El detalle de este análisis se realiza a lo largo de los comentarios.


#include<iostream>
#include<bits/stdc++.h>
#include<vector>         //std::vector
#include<map>            //std::map
#include <algorithm>    // std::count
using namespace std;


//FUNCIONES UTILES //// 

//COSTO: O(size(combinaciones)) = O(TC) = O(n), donde TC = n es el numero de casos de testeo (estudiantes.) 
//Pues la funcion itera sobre todos los pares del diccionario (cada par es en el peor caso un estudiante distinto y para cada caso hay TC estudiantes)
int maxima_popularidad(map<vector<int>, int> combinaciones){ //Funcion que calcula la popularidad maximal de las combinciones en el diccionario combinaciones (calcular valor maximo)
	int maxpop = 0;
	for (const auto &par_curso : combinaciones){  //peor caso este for se realiza n veces
     		   if(par_curso.second>maxpop){     //es una comparación, se realiza en O(1)
     		   	maxpop = par_curso.second;		//al igual que esta asignación
     		   }
    		}
    return maxpop;
}

//COSTO: O(size(combinaciones)) = O(TC) = O(n), de manera análoga a la función maxima_popularidad
int num_maxpop(map<vector<int>, int> combinaciones, int valor){// Función que calcula la cantidad de combinaciones en el diccionario combinaciones cuyo valor es igual a valor
	int num = 0;
	for (const auto &par_curso : combinaciones){    //en el peor caso este for se realiza n veces
     		   if(par_curso.second == valor){      //comparación, O(1)
     		   	num++;					//asignacion O(1)
     		   }
    		}
    return num;
}


int main(){
	int TC;    
	while(scanf("%d",&TC)!=EOF and TC!=0){   //leemos los casos de prueba (cant. de estudiantes)    //este while se ejecutara tantas veces como casos de prueba sean otorgados en la entrada
		int arr[5];     //Creamos un arreglo temporal para leer los cursos   //O(1), 5*4*8 bits
		map<vector<int>, int> combinaciones;  //creamos un diccionario cuyas claves sean las combinaciones de cursos (vectores de tamaño 5)
											  //y con valores correspondientes a la popularidad de cada combinación
											  //este es un diccionario con TC = n claves en el peor caso, y cada clave es un arreglo de 5 enteros, por lo que requiere
											  //((4*8)*5 + 4*8)*n bits = 192*n bits para almacenar claves y valores en el peor caso (todos los arreglos con distinta popularidad)

		while(TC--){  //es un shortcut que equivale a for (int i = 0; i<TC; i++). Esta linea equivale a for all estudiante in (rango de TC) y por lo tanto se ejecuta TC = n veces

			scanf("%d %d %d %d %d", &arr[0],&arr[1],&arr[2],&arr[3],&arr[4]);   //leemos c1,c2,c3,c4,c5 (cursos de cada estudiante) O(1)
			vector<int> cursos(arr, arr+5);     //declaramos un vector cursos en el que guardaremos los elementos de arr

			//Hasta acá para evitar casos de combinaciones duplicadas (guardarlos como si fueran distintas al estar en distinto orden) podemos ordenar los datos
			// o bien implementarlos con un set u algun contenedor que no considere orden.

			sort(cursos.begin(),cursos.end());   // O(5log 5) = O(1), es el sort de la libreria estándar para ordenar un vector de 5 elementos

			//Si esta combinación de cursos ya habia sido seleccionada por alguna persona, habría sido ingresada al diccionario combinaciones
			if(combinaciones.count(cursos) == 1){ //el método count fue utilizado por la facilidad de implementarlo, idea tomada de https://stackoverflow.com/questions/3136520/determine-if-map-contains-a-value-for-a-key
				combinaciones[cursos]++; //En tal caso incrementamos la popularidad de la combinación cursos
			}
			else{
				combinaciones[cursos] = 1; //Si no lo encontramos en el diccionario es porque ningún estudiante habia seleccionado tal combinación (este es el primero), por lo que ahora asignamos su popularidad a 1
			}

		}  //HASTA AQUI se cierra el while TC--, es decir, aqui ya fueron ingresadas las combinacinoes de los estudiantes en los TC y sus respectivas popularidades
			// Todas las operaciones realizadas al interior del while anterior son de orden O(1) por lo que todo el proceso anterior se realiza en el peor caso O(n) 


			// En lo que sigue queda encontrar el valor de la popularidad maximal
			//Iteramos sobre el diccionario utilizando la idea tomada de https://stackoverflow.com/questions/4844886/how-can-i-loop-through-a-c-map-of-maps

			int maxpop = maxima_popularidad(combinaciones); //maxpop es la popularidad maximal en el diccionario  // O(n)

    		//Ahora que ya tenemos el valor de la popularidad maximal, queda contar cuantas combinaciones la alcanzan  
    		int num_mp = num_maxpop(combinaciones, maxpop);  //num_mp es el numero de combinaciones que tienen una popularidad igual a maxpop  //O(n)


    		//Finalmente, tenemos que num_mp combinaciones alcanzaron un nivel de popularidad max_pop maximal. Entonces, en total 
    		//num_mp*max_pop es la cantidad de estudiantes que inscribieron una asignatura de popoularidad maximal
    		cout<<maxpop*num_mp<<endl;   //O(1)


		
	 }



	return 0;

}


//Conclusiones: El costo de tiempo para la solucion planteada es O(n)+O(n)+O(n) = O(n) para cada caso de prueba, donde conjeturamos que la constante es grande pues se obviaron varios detalles y refinamientos en el análisis.
            //: El costo de espacio para la solucion planteada es 192*n bits + una cantidad de bits que no depende de n. Es decir, el costo espacial es lineal con respecto a la cantidad de casos de prueba (TC), al igual que el tiempo, y 
			// se concentra en la unica estructura de datos que tiene un tamaño variable en funcion de n en nuestro caso, que es el mapa (diccionario) combinaciones.
//Conclusión extra: este problema lo intenté implementar en Python de una manera eficiente (pero con menos comprensión de algunos términos, pues use funciones de hashing sin saber hashing), y a pesar de ser una implmentación mas elaborada que esta, 
//presentó un tiempo de ejecución de 0.220 en OnlineJudge, lo que vagamente compite con el tiempo de 0.050 logrado por esta implementación. Esta observación alimenta la idea de que la arquitectura sobre la que trabajamos es fundamental a la hora de minimizar el tiempo de ejecución.