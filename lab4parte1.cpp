//Programacion orientada a objetos
//Los métodos permiten enviarle mensajes a los objetos
//Para ello, tenemos struct o class. La diferencia principal es que struct viene de C
//y asume que todos los métodos son públicos, mientras que class los asume privados

//Una clase es como un molde de galletas, al momento de crear las galletas hay que
// usar el método constructor
#include <iostream>
#include "Audifono.h"

using namespace std;

int main(){
	int n;
	cin >> n;
	Audifono *a = new Audifono("Rojo");
	Audifono b("Negro");
	a->prender();  //Si está declarada como puntero
	b.prender(); //Sin puntero y sin new

	for(int i = 0; i<n; i++){
		string color;
		cin>> color;
		Audifono b(color);
	}
	

	string colorDeA = a->get_color();
	delete a;
}