#include<iostream>
using namespace std;



//Utilizamos el selectionSort visto en clases
void selectionSort(int n, long* v){
	for(int i = 0; i<n; i++){
		for(int j = i+1;j<n;j++){
			if(v[i]>v[j]){
				//si esto ocurre hacer swap entre v[i] y v[j]
				int aux = v[i];
				v[i] = v[j];
				v[j] = aux;
			}
		}
	}
}



//Funciones Utiles para recibir arreglos por la terminal

void imprimir_arreglo(long *arr, int size){
	for(int i = 0; i<size; i++){
		cout<<arr[i]<<" ";
	}
	cout<<endl;
}

long *pedir_arreglo(int size){
	long *arr = new long[size];
	cout<<"Ingrese los elementos del arreglo"<<endl;
	for(int i = 0; i<size; i++){
		cin>>arr[i];
	}

	return arr;
	delete[] arr;

}

///////////////////////////////////////////////////////


// MERGE SORT /////
//dadas ciertas complicaciones tecnicas respecto al algoritmo de mezclar en orden visto en clases, 
//se obtuvo inspiracion del algoritmo de merge disponible en https://gist.github.com/harish-r/10025634, el cual utiliza un while en lugar de un for


//Observando que durante cualquier merge, seguiremos considerando subarreglos del arreglo v original,
//no parece necesario entregar a la funcion mezclar los subarreglos (como se hizo en clases), para ello
//Creamos una variante del algoritmo visto en laboratorio que solo requiere como entrada los indices l y r
//entre los cuales se encuentran los subarreglos que vamos a mezclar (y reordenar (mezclar) en v)



//En efecto, 
//Buscamos mezclar dos subarreglos de v, entre los indices l y r
// y cada uno de  (r-l+1) elementos (mas precisamente, el arreglo vL tendra (r-l)/2 +1 elementos, 
//y el arreglo de la derecha los restantes)

void mezclar_en_orden(long *v, int l, int r)
{
    int i, j, k; //Definimos i como un contador de elementos mezclados en el subarreglo de la izquierda
    //j la cantidad de elementos mezclados del subarreglo de la derecha de m
    // y k como

    int m = l+(r-l)/2; //este es el indice de la mitad de los arreglos (hasta aca llega el subarreglo L)
    int n1 = m - l + 1; //esta es la cantidad de elementos de L
    int n2 =  r - m; //esta es la cantidad de elementos de R

    //creamos los arreglos del lado izquierdo y el lado derecho
    long vL[n1], vR[n2];

    //Guardamos los elementos la primera mitad de v (entre l y r) en vL y la segunda en vR
    for (i = 0; i < n1; i++)
        vL[i] = v[l + i];
    for (j = 0; j < n2; j++)
        vR[j] = v[m + 1+ j];


    //En lo que sigue, viene la fase de mezclar ambos arreglos de vuelta en v,
    //pero de modo que queden ordenados
    //los siguientes indices tambien pueden ser vistos como contadores
    i = 0; //Es el indice inicial de vL
    j = 0; // Indice inicial de vR
    k = l; // Indice del arreglo mezclado (empieza desde l pues solo vamos a mezclar las posiciones de v desde l hasta r)

    while (i < n1 && j < n2) //Mientras sigan quedando elementos no mezclados en vL y vR
    {
        if (vL[i] <= vR[j]) //Si el elemento i del arreglo izquierdo es mas pequeno que el j del arreglo vR
     						//guardamos el menor en el arreglo original (que quedara mezclado en orden)
        {
            v[k] = vL[i]; //En tal caso, en la posicion k guardamos el que estaba en la posicion i del vL 
            i++; //e incrementamos nuestro indice del arreglo izquierdo, pues ya agregamos el vector en la posicion i a la mezcla
        }
        else //Si en cambio vL[i]>vR[j], agregamos vR[j] en la posicion k del arreglo mezclado (v) e incrementamos el indice del arreglo de la derecha
        {
            v[k] = vR[j];
            j++;
        }
        k++; //Para cualquiera de los dos casos anteriores, se incrementa en 1 la cantidad de elementos ya ordenados en el vector mezclado
    }
    //si nos quedan elementos restantes en el vector de la derecha, los agregamos tal cual al vector mezclado (pues dada la naturaleza del proceso de separar los subarreglos, ellos preservan un orden relativo local, i.e. vL y vR estan ya ordenados)

    while (i < n1)
    {
        v[k] = vL[i];
        i++; //incrementamos en uno el indice del arreglo de la izquierda
        k++; //incrementamos en uno el indice de los
    }

   //Analogamente, si nos quedaron elementos extra en vR, ya estan ordenados y los agregamos todos al v mezclado
    while (j < n2)
    {
        v[k] = vR[j];
        j++;
        k++;
    }
}





//Utilizando la funcion mezclar_en_orden ya descrita, podemos proceder a definir el procedimiento MergeSort recursivo ya visto en clases

//recibimos como entrada un arreglo v de n elementos
void MergeSort(long* v, int l, int r){
	
	//mientras tengamos sub arreglos 
	if(l<r){
		//definimos la mitad de l a r
		int m = l+(r-l)/2;
		//y ahora ordenamos la mitad izquierda y la mitad derecha
		MergeSort(v, l, m);
		MergeSort(v, m+1, r);

		//y mezclamos ambos subarreglos ordenados
		mezclar_en_orden(v, l, r);
	}

}




int main(){
	int size;
	cout<<" Ingrese el tamano del arreglo"<<endl;
	cin>>size;
	long *arr = pedir_arreglo(size);
	//imprimir_arreglo(arr, size);
	cout<<endl;

	cout<<"El arreglo ordenado es:";
	MergeSort(arr, 0, size-1);

	imprimir_arreglo(arr, size);



	return 0;
}