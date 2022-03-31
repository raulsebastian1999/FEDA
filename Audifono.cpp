#include"Audifono.h"
#include<iostream>
using namespace std;

Audifono::Audifono(string color, bool ab, bool pren, int vol){
	this-> color  = color; //Así decimos que el color de la clase será igual al del objeto
	this-> abierto = ab;  // lo de la izquierda es lo que apunta a la instancia de la clase
	this-> prendido = pren;
	this-> volumen = vol;
	//arr = new int[5];
}
Audifono::Audifono(string color){
	this-> color  = color; //Así decimos que el color de la clase será igual al del objeto
	this-> abierto = false;  // lo de la izquierda es lo que apunta a la instancia de la clase
	this-> prendido = false;
	this-> volumen = 5;
}

//En este caso no necesita hacer nada porque no pedimos memoria dinámica
Audifono::~Audifono(){

	//delete arr; //ejecuta el método destructor de la clase Audifono
}


void Audifono::prender(){
	this->prendido = true;
}
void Audifono::apagar(){
	this->prendido = false;
}
void Audifono::abrir(){
	this->abierto = true;
}
void Audifono::cerrar(){
	this->abierto = false;
}
void Audifono::subirVol(){
	if(volumen<10){
		volumen++;
	}
}
void Audifono::bajarVol(){
	if(volumen>0){
		volumen--;
	}
}

string Audifono::get_color(){
	return color;
}