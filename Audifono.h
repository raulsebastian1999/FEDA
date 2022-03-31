#include <string>
using namespace std;
class Audifono{
private:
	string color;
	bool abierto;
	bool prendido;
	int volumen;
	//Que todas sean privadas ayuda al "encapsulamiento"

	//Ahora hay que definir el constructor
public:
	Audifono(string color, bool ab, bool prend, int vol);
	Audifono(string color);

	//Ahora definimos el destructor, es lo que se ejecuta cuando hacemos delete

	~Audifono();
	void prender();
	void apagar();

	void abrir();
	void cerrar();
	void subirVol();
	void bajarVol();


	//Metodo para indicar lo que hay en private
	string get_color();

};