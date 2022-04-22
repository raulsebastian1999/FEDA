#include"vector.h"
#include<iostream>
using namespace std;

vector::vector(int size, int capacidad, int *arr);
	this->size = size;
	this->capacidad = capacidad; 
	this->arr = new int*[capacidad];