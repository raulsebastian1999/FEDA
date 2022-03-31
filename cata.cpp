#include <iostream>
using namespace std;

int *encontrar_num(int *arr,int num, int tam){
	int *p1 = NULL;
	for(int i=0; i<tam;i++){
		if (arr[i]==num){
			p1=&arr[i];
			return p1;
		}
	}
	return p1;
}

int main(){
	int arr[] = {1,7,2,9,10,7};
	int *res = encontrar_num(arr,7,6);
	cout << *res << endl;
	cout << res << endl;
	cout << &arr[1] << endl;
}
