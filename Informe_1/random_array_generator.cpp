#include <iostream>
#include <ctime>
#include<random>

using namespace std;


int main(){
   std::random_device rd;  //Will be used to obtain a seed for the random number engine
   std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
   std::uniform_int_distribution<> distrib(1, 6);
   

   //uniform_real_distribution<int> dist(0, 1000);  //(min, max)
   //mt19937 rng; 
   //Initialize with non-deterministic seeds
   //rng.seed(std::random_device{}()); 
   int n;
   n = 256;


   double* A = new double*[n];
   
   for(int i = 0; i<n; i++){
      A[i] = distrib(gen);
   }
   
   cout<<n<<" "<<endl;

   for(int i = 0; i<m; i++){
      cout<<A[i]<<" ";
   }
   
  cout<<endl;

  
   return 0;
}