#include "pantallas.hpp"

void pantallaApropiativos(vector <Proceso> listaProcesos){

	while(true){

		system("cls");

		cout << "Algoritmos de planificación apropiativos" << endl;
		int opcion = 0;

		cout << "\n1. Algoritmo Round Robin" << endl;
		cout << "2. Algoritmo por prioridades" << endl;
		cout << "3. Algoritmo SJF" << endl;
		cout << "4. Regresar" << endl;
		cout << "Eliga una opción: "; cin >> opcion;

		if(opcion == 1){

			pantallaComenzarSimulacion(listaProcesos, RR);

		}else if(opcion == 2){

			pantallaComenzarSimulacion(listaProcesos, PRIORIDADAPROPIATIVO);

		}else if(opcion == 3){

			pantallaComenzarSimulacion(listaProcesos, SJFAPROPIATIVO);

		}else if(opcion == 4){
			break;
		}

	}

}
