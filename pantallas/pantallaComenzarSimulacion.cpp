
#include "../simulador/simulador.hpp"

void pantallaComenzarSimulacion(vector <Proceso> listaProcesos, int modoProcesos){

	int quantum = 0;
	int opcion = 0;
	int opcionMemoria=0;
	int modoMemoria=0;

	if(modoProcesos==RR){
		cout << "\nDefina el tama�o del quantum: "; cin >> quantum;
	}

	cout << "\nEstrategia de asignaci�n de memoria:" << endl;

	cout << "1. First fit" << endl;
	cout << "2. Best fit" << endl;
	cout << "3. Worst fit" << endl;
	cout << "Elija una estrategia: "; cin>>opcionMemoria;

	if(opcionMemoria==1){
		modoMemoria=FIRSTFIT;
	}else if(opcionMemoria==2){
		modoMemoria=BESTFIT;
	}else{
		modoMemoria=WORSTFIT;
	}

	cout << "\n1. Comenzar simulaci�n" << endl;
	cout << "2. Regresar" << endl;
	cout << "Elija una opci�n: "; cin >> opcion;

	if(opcion == 1){
		simulador(listaProcesos,modoProcesos, modoMemoria, quantum);
	}

}
