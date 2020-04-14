
#include "../principal.hpp"
#include "../utilitarios/utilitarios.hpp"

void pantallaVerProcesos(vector <Proceso> &listaProcesos){

	while(true){

		system("cls");

		struct Proceso nuevoProceso;
		int opcion = 0;

		if(listaProcesos.size()==0){
			cout << "No hay procesos" << endl;
		}else{
			imprimirProcesos(listaProcesos);
		}

		cout << "\n1. Crear un proceso aleatorio" << endl;
		cout << "2. Crear 20 procesos aleatorios" << endl;
		cout << "3. Crear un proceso de forma manual" << endl;
		cout << "4. Borrar todos los procesos" << endl;
		cout << "5. Volver" << endl;
		cout << "Seleccione una opción: "; cin >> opcion;

		if(opcion == 1){

			nuevoProceso = nuevoProceso.crearProcesoAleatorio(listaProcesos);
			listaProcesos.push_back(nuevoProceso);

		}else if(opcion == 2){

			for(int i=0;i<20;i++){
				nuevoProceso = nuevoProceso.crearProcesoAleatorio(listaProcesos);
				listaProcesos.push_back(nuevoProceso);
			}

		}else if(opcion == 3){
			nuevoProceso = nuevoProceso.crearProcesoManual(listaProcesos);
			listaProcesos.push_back(nuevoProceso);
		}else if(opcion == 4){
			listaProcesos.clear();
		}else if(opcion == 5){
			break;
		}

	}
}
