#include<iostream>
#include <ctime>
using namespace std;

int main()
{
   int sz;
   srand(time(NULL));
   sz = 1000;
   int randArray[sz];
   for(int i=0;i<sz;i++)
      randArray[i]=rand()%1000;  //Generate number between 0 to 1000
  
   cout<<sz<<endl;
   
   for(int i=0;i<sz;i++){
      cout<<randArray[i]<<" ";
   }
   cout<<endl;
   return 0;
}