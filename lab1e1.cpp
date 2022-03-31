#include <iostream>
using namespace std;

int *encontrar_num(int *arr, int num, int tam){
	int *p1;
	for (int i = 0; i< tam; i++){
		if (arr[i] == num){
			p1 = &arr[i];
			cout<<p1<<endl;
			return p1;
		}
		
	}
	return NULL;
}

int main(){
	int tam, num;
	int arr[] = {1,2,3,4,5,6,7,8,4};
	tam = 8;
	num = 4;
	int *p = encontrar_num(arr, num, tam);
	cout << *p << endl;
	cout << p << endl;
	cout << &arr[3] << endl; 

		return 0;

}