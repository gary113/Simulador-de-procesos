#include "pantallas.hpp"

void pantallaNoApropiativos(vector <Proceso> listaProcesos){

	while(true){

		system("cls");

		cout << "Algoritmos de planificación no apropiativos" << endl;
		int opcion = 0;

		cout << "\n1. Algoritmo FCFS" << endl;
		cout << "2. Algoritmo por prioridades" << endl;
		cout << "3. Algoritmo SJF" << endl;
		cout << "4. Regresar" << endl;
		cout << "Eliga una opción: "; cin >> opcion;

		if(opcion == 1){

			pantallaComenzarSimulacion(listaProcesos, FCFS);

		}else if(opcion == 2){

			pantallaComenzarSimulacion(listaProcesos, PRIORIDADNOAPROPIATIVO);

		}else if(opcion == 3){

			pantallaComenzarSimulacion(listaProcesos, SJFNOAPROPIATIVO);

		}else if(opcion == 4){
			break;
		}
	}

}

