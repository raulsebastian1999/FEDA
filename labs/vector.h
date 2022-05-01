using namespace std; 
class vector{
private:
	int capacidad;//La máxima cantidad de elementos
	void agrandar(){
		int aux[2*size];
		for(int i = 0; i<size; i++){
			aux[i] = arr[i];
		}
		capacidad = 2*capacidad;
	}  //Solo se debe llamar desde pushback o insert

public:
	int size; //El tamaño del vector
	int *arr; //El arreglo que contiene a los elementos
	vector(int size, int capacidad, int *arr); //constructor

	~vector(); //destructor por defecto

	
	//push_back(num);
	//pop_back(num);
	//size();
	 //Metodo para saber que valor esta en esa posición
	//set(pos, num); //A la posición pos asignamos el numero num
	//insert(pos, num); //Meter un elemento num en la posición num
	//erase(pos); // Borrar un elemento
};
