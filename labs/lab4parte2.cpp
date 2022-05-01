#include<iostream>
#include <math.h>
using namespace std;

class Punto{
private:
	float x;
	float y;
public:
	Punto(){
		x = 0;
		y = 0;
	}
	~Punto(){
		cout<< "("<<x<<","<<y<<")"<<endl;
	}
	float get_x(){
		return x;
	}
	float get_y(){
		return y;
	}
	float set_x(float new_x){
		x = new_x;
	}
	float set_y(float new_y){
		y = new_y;
	}
	float calc_dist(){
		return(sqrt(x*x+y*y));
	}
};


/*Para pedir datos por teclado

	int n;
	cin >> n;
	cout<< n;
	*/

int main(){
	int n = 3;
	Punto **arr = new Punto*[n];
	for(int i = 0; i<n; i++){
		int x, y;
		cin>>x>>y;
		arr[i] = new Punto(x,y);
	}

	return 0;
}
