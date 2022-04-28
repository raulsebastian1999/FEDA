#include <iostream>
#include <ctime>
#include<random>

using namespace std;

double **crear_matriz(int m, int n){
	double **mat = new double *[m];  
	for(int i = 0; i<m; i++){
		mat[i] = new double[n];
	}
	return mat; 
	delete[] mat; //borramos la memoria solicitada, una vez ya se entrega en la salida
}


int main(){
   std::random_device rd;  //Will be used to obtain a seed for the random number engine
   std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
   std::uniform_int_distribution<> distrib(1, 6);
   

   //uniform_real_distribution<int> dist(0, 1000);  //(min, max)
   //mt19937 rng; 
   //Initialize with non-deterministic seeds
   //rng.seed(std::random_device{}()); 
   int m, n;
   m =  512;
   n = 512;


   double** A = crear_matriz(m,n);
   double** B = crear_matriz(m,n);
 	
   for(int i = 0; i<m; i++){
   	for(int j = 0; j<n; j++){
   		A[i][j]=static_cast<double>(distrib(gen));  
   		B[i][j]= static_cast<double>(distrib(gen));  
   	}
   }
  	
   cout<<m<<" "<<n<<" "<<endl;

   for(int i = 0; i<m; i++){
   	for(int j = 0; j<n; j++){
   		cout<<A[i][j]<<" ";
   	}cout<<endl;
   }
  	
  cout<<endl;
   cout<<m<<" "<<n<<" "<<endl;
   for(int i = 0; i<m; i++){
   	for(int j = 0; j<n; j++){
   		cout<<B[i][j]<<" ";
   	}cout<<endl;
   }
  
   return 0;
}