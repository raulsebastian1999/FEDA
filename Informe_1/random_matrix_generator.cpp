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
}


int main(){
   std::random_device rd;  //Will be used to obtain a seed for the random number engine
   std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
   std::uniform_int_distribution<> distrib(1, 6);
   

   //uniform_real_distribution<int> dist(0, 1000);  //(min, max)
   //mt19937 rng; 
   //Initialize with non-deterministic seeds
   //rng.seed(std::random_device{}()); 
   int mA, nA,mB,nB;
   mA =  10;
   nA= 20;
   mB = 20;
   nB = 10;
   double** A = crear_matriz(mA,nA);
   double** B = crear_matriz(mB,nB);
 	
   for(int i = 0; i<mA; i++){
   	for(int j = 0; j<nA; j++){
   		A[i][j]=static_cast<double>(distrib(gen));    
   	}
   }
  	
   for(int i = 0; i<mB; i++){
      for(int j = 0; j<nB; j++){
         B[i][j]= static_cast<double>(distrib(gen));
   
      }
   }
   
   

   cout<<mA<<" "<<nA<<" "<<endl;

   for(int i = 0; i<mA; i++){
   	for(int j = 0; j<nA; j++){
   		cout<<A[i][j]<<" ";
   	}cout<<endl;
   }
  	
  cout<<endl;
   cout<<mB<<" "<<nB<<" "<<endl;
   for(int i = 0; i<mB; i++){
   	for(int j = 0; j<nB; j++){
   		cout<<B[i][j]<<" ";
   	}cout<<endl;
   }
  
   return 0;
}