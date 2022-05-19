/*Se trata de una batalla entre Lemmings azules y verdes.
Definición: Un lemming tiene puntos de poder entre 1 y 100.
Definición (Batalla entre dos lemmings): Si tenemos un Lemming verde v
con n1 puntos de poder y otro lemming azul A con n2 puntos de poder, 
entonces gana aquel de mayor poder y el perdedor se queda con la diferencia de la vida.
Si los dos tienen la misma cant. de puntos se mueren ambos.

Definición (Batalla entre grupos de lemmings):




Para la input viene N: Numero de casos de testeo
					B: Campos de batalla
					SG: Soldados verdes
					SB: Soldados azules
					mas SG lineas de las vidas de los SG lemmings verdes
					mas SB lineas de las vidas de los SB lemmings azules
					
		B es la cantidad de campos de batalla disponibles para que peleen los lemmings; en cada enfrentamiento se enfrentan a los mas B soldados
		En los primeros campos de batalla pelean los lemming de salud mas alta


Ejempl1.B SG SB
 		3  5  5
 		50
 		40
 		30
 		40
 		50  ---- Hasta aca SG
 		50  
 		30
 		20
 		30
 		60  ----- Hasta aca SB


 		Los ordenamos en una cola de prioridad

 		SG: 50 50 40 40 30
 		SB: 60 50 30 30 20

 		1° Ronda: pelean los B = 3 mas fuertes de cada equipo
 				G v/s B
 				50    60   Gana B con 10
 				50    50   Se mueren
 				40    30   Gana G con 10
				
		SG: 40 30 10
		SB: 30 20 10

		2° Ronda: pelean los B = 3 mas fuertes de cada equipo
				G v/s B
				40    30  Gana G 10
				30    20  Gana G 10
 				10    10  Mueren
		SG: 10 10
		SB: 

		Ganaron los verdes

		OUTPUT: green wins
				10
				10
		Si los dos mueren se green and blue died

Ejempl2: 2 2 3
	     20  Verdes
	     10 

	     10  Azules
	     10
	     15

	     SG: 20 10
	     SB: 15 10

	     Gana G 5

	     5
	     10

	     se enfrentan de nuevo
	     y SG : NULL

*/


#include<iostream>
#include<queue>
#include<vector>

/*
	Cola de prioridad
	L = [10 20 7 1 2 15]

	        20
	 	 10     
	   7    15
	 1   2 

*/




using namespace std; 

void printpq(priority_queue<long> pq){	
	priority_queue<long> g = pq;
    while (!g.empty()) {
        cout << g.top()<<endl;
        g.pop();
    }
}


void hacer_enfrentamiento(priority_queue<long> PB, priority_queue<long> PG, int SG, int SB, int B){
		int survG, survB;
		while(PG.size()>0 and PB.size()>0){ //Se ejecuta la maxima cantidad de rondas
		survG = 0;
		survB = 0;
		long* auxG = new long[B];
		long* auxB = new long[B];
		// vector<long> auxG;
		// vector<long> auxB;
			for(int i = 0; i<B; i++){
				if(PB.size()!= 0 and PG.size()!=0){
					// if(PA.size()=B )
					if(PG.top()>PB.top()){ //Gane el lider verde
						auxG[survG] = PG.top()-PB.top();
						PG.pop();
						PB.pop();
						survG++;
					}
					else if(PG.top()<PB.top()){ //Gana lider azul
						auxB[survB] = PB.top()-PG.top();
						PG.pop();
						PB.pop();
						survB++;
					}
					else{   //Ambos mueren
						PB.pop();
						PG.pop();
					}
				}

			}
			for(int j = 0; j<survB; j++){
				PB.push(auxB[j]);
			}
			for(int j = 0; j<survG;j++){
				PG.push(auxG[j]);
			}
		delete[] auxG;
		delete[] auxB;
	 }//endwhile

	 if(PG.empty() and PB.empty()) cout<<"green and blue died"<<endl;
	 else if(PB.empty() and !PG.empty()){
	 	cout<<"green wins"<<endl;
	 	printpq(PG);
	 }
	 else{
	 	cout<<"blue wins"<<endl;
	 	printpq(PB);
	 }

}


int main(){
	
	int N;
	cin>>N;
	for(int j = 0; j<N; j++){
		priority_queue<long> PB;
		priority_queue<long> PG;
		long n1,n2;
		int SG, SB, B;
		cin>>B;
		cin>>SG;
		cin>>SB;
		for(int i = 0; i<SG; i++){
			cin>>n1;
			PG.push(n1);
		}
		for(int i = 0; i<SB; i++){
			cin>>n2;
			PB.push(n2);
		}

		hacer_enfrentamiento(PB,PG,SG,SB,B);
		if(j!=N-1) cout<<endl;
	}



	return 0;
}