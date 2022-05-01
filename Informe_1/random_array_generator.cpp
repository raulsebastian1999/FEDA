#include <iostream>
#include <ctime>
#include<random>
#include<limits>
#include<stdlib.h>
#include<algorithm>
#include<cmath>
using namespace std;



int main(){
    srand (time(NULL)); //generacion de semilla
 std::random_device rd;     //Uso del generador de numeros pseudoaleatorios de merseenne twistter
  std::mt19937_64 eng(rd());  //Idea obtenida de https://stackoverflow.com/questions/22883840/c-get-random-number-from-0-to-max-long-long-integer
  std::uniform_int_distribution<long long int> distr(-9999,9999);

  

   int n;
   n = pow(2,18); //parametros a cambiar para generar arreglos de distinto tamaño
   







   double* A = new double[n]; //Creamos el arreglo A de n elementos
   
   for(int i = 0; i<n; i++){
      A[i] = distr(eng);  //y lo rellenamos de valores (pseudo)aleatorios
   }
   

   //Si queremos inducir un orden parcial, o que estén de mayor a menor (de izquierda a derecha) hacemos los siguiente
   //std::sort(A, A+size, greater());
   //std::sort(A, A+n, std::greater<>()); //para que estén de mayor a menor 
  //Ordenamos solo la mitad
   //std::sort(A, A+n/2);
 //Ordenamos todo el arreglo

   std:sort(A,A+n);




   cout<<n<<" "<<endl;

   for(int i = 0; i<n; i++){
      cout<<A[i]<<" ";
   }
   
  cout<<endl;

  

  delete[] A;
  return 0;
}