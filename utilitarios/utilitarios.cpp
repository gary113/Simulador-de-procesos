#include "../principal.hpp"

void imprimirProcesos(vector <Proceso> &listaProcesos){
	cout << "ID | Tamaño | Heap | Datos | Stack | Instrucciones | Burst time | Llegada | Prioridad | Error" << endl;
	for(unsigned int i=0;i<listaProcesos.size();i++){
		cout << listaProcesos[i].idProceso << " | ";
		cout << listaProcesos[i].tamanioProceso << " MB | ";
		cout << listaProcesos[i].heap << " MB | ";
		cout << listaProcesos[i].datos << " MB | ";
		cout << listaProcesos[i].stack << " MB | ";
		cout << listaProcesos[i].instrucciones << " MB | ";
		cout << listaProcesos[i].tiempoRequerido << " | ";
		cout << listaProcesos[i].momentoLlegada << " | ";
		cout << listaProcesos[i].prioridadProceso << " | ";
		cout << listaProcesos[i].tieneError << endl;
	}
}

void imprimirTiemposMedios(vector <Proceso> &listaProcesosFinalizados, vector<Proceso> &listaFallados, int &reloj, int &usoCpu, int &fragmentacionMaxima){

	cout<< "\nTiempos del algoritmo: " << endl;

	int respuesta=0;
	int espera=0;
	float respuestaAcumulado=0;
	float esperaAcumulado=0;
	float esperaMemoria=0;

	for(unsigned int i=0;i<listaProcesosFinalizados.size();i++){
		esperaMemoria+=listaProcesosFinalizados[i].tiempoEsperandoMemoria;
		respuesta = listaProcesosFinalizados[i].momentoTermino - listaProcesosFinalizados[i].momentoComenzo;
		espera = respuesta - listaProcesosFinalizados[i].tiempoRequerido;

		respuestaAcumulado += respuesta;
		esperaAcumulado += espera;
	}

	if(listaProcesosFinalizados.size()>0){
		respuestaAcumulado/=listaProcesosFinalizados.size();
		esperaAcumulado/=listaProcesosFinalizados.size();
		esperaMemoria/=listaProcesosFinalizados.size();
	}

	cout << "\nEl porcentaje de uso de CPU es: " << usoCpu*100/reloj << " %" << endl;
	cout << "El tiempo de respuesta medio es: " << respuestaAcumulado << " unidades de tiempo" << endl;
	cout << "El tiempo de espera medio es: " << esperaAcumulado << " unidades de tiempo" << endl;
	cout << "El tiempo de espera de memoria medio es: " << esperaMemoria << " unidades de tiempo" << endl;
	cout << "La cantidad máxima de fragmentos de memoria libre es: " << fragmentacionMaxima << endl;
	cout << "La cantidad de procesos con errores es: " << listaFallados.size() << endl;

}

void imprimirColas(vector<Proceso> &listaProcesos, vector<Proceso> &colaListos, vector<Proceso> &enEjecucion, vector<vector<Proceso>> &colasBloqueados, int &reloj, int &memoriaDisponible, unsigned int &posicionActual, int modoProcesos, int modoMemoria){

	int contadorColumnasListos=0;

	cout << "\nPolítica de procesos: ";
	if(modoProcesos==PRIORIDADAPROPIATIVO){
		cout << "Por prioridades apropiativo";
	}else if(modoProcesos==SJFAPROPIATIVO){
		cout << "SJF apropiativo";
	}else if(modoProcesos==RR){
		cout << "Round Robin";
	}else if(modoProcesos==SJFNOAPROPIATIVO){
		cout << "SJF no apropiativo";
	}else if(modoProcesos==PRIORIDADNOAPROPIATIVO){
		cout << "Por prioridades no apropiativo";
	}else if(modoProcesos==FCFS){
		cout << "FCFS";
	}

	cout << " - Estrategia de asignación de memoria: ";
	if(modoMemoria==FIRSTFIT){
		cout << "First fit" << endl;
	}else if(modoMemoria==BESTFIT){
		cout << "Best fit" << endl;
	}else if(modoMemoria==WORSTFIT){
		cout << "Worst fit" << endl;
	}

	cout << "\n********** Cola de procesos totales **********\n" << endl;

	if(listaProcesos.size()==0){
		cout << "No hay procesos en la cola de procesos totales, regrese a la opción ver procesos para crear procesos" << endl;
	}else{
		for(unsigned int i=0;i<listaProcesos.size();i++){
			if(listaProcesos[i].momentoLlegada<=reloj){ //Solo muestra los que ya llegaron

				cout << "ID: " << listaProcesos[i].idProceso << " - Estado:";

				if(listaProcesos[i].estado==NUEVO){
					cout << "N";
				}else if(listaProcesos[i].estado==LISTO){
					cout << "L";
				}else if(listaProcesos[i].estado==BLOQUEADO){
					cout << "B";
				}else if(listaProcesos[i].estado==ABORTADO){
					cout << "A";
				}else if(listaProcesos[i].estado==FINALIZADO){
					cout << "F";
				}else if(listaProcesos[i].estado==EJECUTANDO){
					cout << "E";
				}

				cout << " - Nuevo/Listo:" << listaProcesos[i].momentoLlegada << "/" << listaProcesos[i].momentoAlistado << " - Dir. inicial:" << listaProcesos[i].direccionInicial << " - PC:" << listaProcesos[i].pc << " - Tamaño:" << listaProcesos[i].tamanioProceso << " MB - Heap:" << listaProcesos[i].heap << " MB - Datos:" << listaProcesos[i].datos << " MB - Stack:" << listaProcesos[i].stack << " MB - Instrucciones:" << listaProcesos[i].instrucciones  << " MB - Burst Time:" << listaProcesos[i].tiempoRequerido << " - Prioridad:" << listaProcesos[i].prioridadProceso << endl;

			}
		}

		if(posicionActual<listaProcesos.size()-1){
			cout << "\nLlegada del siguiente proceso en: " << listaProcesos[posicionActual+1].momentoLlegada-reloj <<" - Tamaño: " << listaProcesos[posicionActual+1].tamanioProceso << " MB" << endl;
		}
	}

	cout << "\n********** Cola de procesos listos **********\n" << endl;

	if(colaListos.size()==0){
		cout << "No hay procesos en la cola de listos" << endl;
	}else{

		for(unsigned int i=0;i<colaListos.size();i++){

			cout << "ID:" << colaListos[i].idProceso << " - Estado:";

			if(colaListos[i].estado==NUEVO){
				cout << "N";
			}else if(colaListos[i].estado==LISTO){
				cout << "L";
			}else if(colaListos[i].estado==BLOQUEADO){
				cout << "B";
			}else if(colaListos[i].estado==ABORTADO){
				cout << "A";
			}else if(colaListos[i].estado==FINALIZADO){
				cout << "F";
			}else if(colaListos[i].estado==EJECUTANDO){
				cout << "E";
			}

			if(modoProcesos==PRIORIDADAPROPIATIVO || modoProcesos==PRIORIDADNOAPROPIATIVO){
				cout << " - Prioridad:" << colaListos[i].prioridadProceso;
			}
			else if(modoProcesos==SJFAPROPIATIVO || modoProcesos==SJFNOAPROPIATIVO){
				cout << " - Burst time:" << colaListos[i].tiempoRequerido;
			}

			cout << " || ";

			contadorColumnasListos++;
			if(contadorColumnasListos==4 || i==colaListos.size()-1){
				cout << endl;
				contadorColumnasListos=0;
			}

		}
	}

	cout << "\n********** Proceso en ejecución **********\n" << endl;

	if(enEjecucion.size()==0){
		cout << "No hay proceso en ejecución" << endl;
	}else{
		cout << "||ID:" << enEjecucion[0].idProceso << " - Estado:";

		if(enEjecucion[0].estado==NUEVO){
			cout << "N";
		}else if(enEjecucion[0].estado==LISTO){
			cout << "L";
		}else if(enEjecucion[0].estado==BLOQUEADO){
			cout << "B";
		}else if(enEjecucion[0].estado==ABORTADO){
			cout << "A";
		}else if(enEjecucion[0].estado==FINALIZADO){
			cout << "F";
		}else if(enEjecucion[0].estado==EJECUTANDO){
			cout << "E";
		}

		if(modoProcesos==PRIORIDADAPROPIATIVO || modoProcesos==PRIORIDADNOAPROPIATIVO){
			cout << " - Prioridad:" << enEjecucion[0].prioridadProceso;
		}
		else if(modoProcesos==SJFAPROPIATIVO || modoProcesos==SJFNOAPROPIATIVO){
			cout << " - Burst time:" << enEjecucion[0].tiempoRequerido;
		}

		cout << " - PC:" << enEjecucion[0].pc << " - Tiempo en ejecución:" << enEjecucion[0].tiempoRafagaAcumulado+enEjecucion[0].tiempoRafagaEjecucion << "/" << enEjecucion[0].tiempoRequerido << " || " << endl;
	}

	cout << "\n********** Colas de bloqueados **********" << endl;

	for(unsigned int i=0;i<colasBloqueados.size();i++){

		cout << "\nCola del dispositivo " << (i+1) << ":" << endl;

		if(colasBloqueados[i].size()>0){

			for(unsigned int j=0;j<colasBloqueados[i].size();j++){

				if(j==0){
					cout << "|| ";
				}

				cout << "ID:" << colasBloqueados[i][j].idProceso << " - Estado:";

				if(colasBloqueados[i][j].estado==NUEVO){
					cout << "N";
				}else if(colasBloqueados[i][j].estado==LISTO){
					cout << "L";
				}else if(colasBloqueados[i][j].estado==BLOQUEADO){
					cout << "B";
				}else if(colasBloqueados[i][j].estado==ABORTADO){
					cout << "A";
				}else if(colasBloqueados[i][j].estado==FINALIZADO){
					cout << "F";
				}else if(colasBloqueados[i][j].estado==EJECUTANDO){
					cout << "E";
				}

				if(j==0){
					cout << " - Duración de bloqueo:" << colasBloqueados[i][j].tiempoRafagaBloqueo << "/" << colasBloqueados[i][j].duracionBloqueo;
				}

				if(j==colasBloqueados[i].size()-1){
					cout << " ||" << endl;;
				}else{
					cout << " || ";
				}
			}

		}else{
			cout << "No hay procesos en la cola del dispositivo " << (i+1) << endl;
		}
	}
}

void imprimirRam(vector<Proceso> &ram, int &memoriaDisponible){

	int contadorColumnasRam=0;

	cout << "\n********** Memoria: Ocupado = " << MEMORIATOTAL-memoriaDisponible << " MB - Disponible = " << memoriaDisponible << " MB - Total = " << MEMORIATOTAL << " MB **********\n" << endl;

	for(unsigned int i=0;i<ram.size();i++){

		if(contadorColumnasRam==8){
			cout << endl;
			contadorColumnasRam=0;
		}

		if(ram[i].idProceso==-1){
			if(i==ram.size()-1){
				cout << "SO/" << ram[i].tamanioProceso << " MB" << endl;
			}else{
				cout << "SO/" << ram[i].tamanioProceso << " MB --> ";
			}
		}else if(ram[i].idProceso==0){
			if(i==ram.size()-1){
				cout << "Libre/" << ram[i].tamanioProceso << " MB" << endl;
			}else{
				cout << "Libre/" << ram[i].tamanioProceso << " MB --> ";
			}
		}else{
			if(i==ram.size()-1){
				cout << "ID:" << ram[i].idProceso << "/" << ram[i].tamanioProceso << " MB" << endl;
			}else{
				cout << "ID:" << ram[i].idProceso << "/" << ram[i].tamanioProceso << " MB --> ";
			}
		}

		contadorColumnasRam++;
	}
}

bool compararPrioridades(Proceso a, Proceso b){
	return a.prioridadProceso > b.prioridadProceso;
}

bool compararBurstTime(Proceso a, Proceso b){
	return a.tiempoRequerido < b.tiempoRequerido;
}
