#include <iostream>
using namespace std;


int main(){
	int arr[]= {1634496328,1853181216,2191204};
	char *p=(char *)arr;
	for (int i=0;i<=12;i++){
		cout<<p[i]<<endl;
	}
}
