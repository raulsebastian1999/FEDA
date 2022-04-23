#include <iostream>
using namespace std;




int main(){
	vector v; 

	v.size = 3;
	v.capacidad = 10; 
	int A[3] = {1,2,3};
	v.arr = A;
	v.agrandar();
	cout<<v.arr[0]<<endl;

	return 0;
}
