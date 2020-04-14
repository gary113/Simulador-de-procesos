#include "../principal.hpp"
#include "../modulos/planificador.hpp"
#include "../modulos/gestorInterrupciones.hpp"
#include "../utilitarios/utilitarios.hpp"

void simulador(vector <Proceso> listaProcesos,int modoProcesos, int modoMemoria, int &quantum){

	string salir="";
	char opcion=' ';
	bool avisoAlistarProcesos=false;
	bool avisoInterrupcionNuevoProceso=false;
	int usoCpu=0;
	int fragmentacionMaxima=0;
	int fragmentacionActual=0;

	struct gestorInterrupciones gestorInterrupciones;

	struct planificador planificador;
	planificador.modoProcesos=modoProcesos;
	planificador.modoMemoria=modoMemoria;

	int reloj = 0;
	int memoriaDisponible = MEMORIATOTAL-TAMANIOSO;
	unsigned int posicionActual=0; //Posicion del ultimo proceso que ha llegado, lo usa el planificador

	vector<Proceso> ram;
	struct Proceso primerLibre;
	struct Proceso so;
	primerLibre.idProceso=0;
	so.idProceso=-1;
	so.tamanioProceso=TAMANIOSO;
	primerLibre.tamanioProceso=MEMORIATOTAL-TAMANIOSO;
	ram.push_back(so);
	ram.push_back(primerLibre);

	vector <Proceso> colaListos(0);

	vector <vector <Proceso>> colasBloqueados(0);
	vector<Proceso> primerDispositivo(0);
	colasBloqueados.push_back(primerDispositivo);

	vector <Proceso> enEjecucion(0);

	vector <Proceso> listaFinalizados(0);
	vector <Proceso> listaFallados(0);

	while(listaProcesos.size()!=listaFinalizados.size()+listaFallados.size()){ //Mientras haya algun proceso sin finalizar

		if(opcion!='t'){
			system("cls");
		}

		avisoAlistarProcesos=planificador.alistarProcesos(listaProcesos, colaListos,enEjecucion, colasBloqueados, reloj, memoriaDisponible, ram, posicionActual);  //Verifica si se crean nuevos procesos y si los bloqueados ya recibieron lo que necesitaban

		if(reloj%TIMER == 0 && reloj!=0){ //Interrupcion por timer

			gestorInterrupciones.interrupcionTimer(listaProcesos, colaListos, enEjecucion, listaFallados, colasBloqueados, reloj, memoriaDisponible, ram);
			planificador.acomodarColaListos(colaListos);

		}else if(avisoAlistarProcesos==true && enEjecucion.size()>0){ //Interrupcion por llegada de nuevo proceso

			avisoInterrupcionNuevoProceso=gestorInterrupciones.interrupcionNuevoProceso(listaProcesos, colaListos, enEjecucion, reloj, planificador.modoProcesos);

			if(avisoInterrupcionNuevoProceso==true){ //Acomoda la cola de listos en caso se haya hecho cambio de contexto
				planificador.acomodarColaListos(colaListos);
			}

		}else if(enEjecucion.size() == 0 && colaListos.size()>0){ //Cuando no hay nada ejecutandose y hay procesos listos

			planificador.despachador.comenzarEjecucion(listaProcesos, colaListos, enEjecucion, reloj, planificador.modoProcesos);

		}else if(enEjecucion.size()>0){ //Cuando hay algo ejecutandose

			if(enEjecucion[0].tiempoRafagaAcumulado + enEjecucion[0].tiempoRafagaEjecucion == enEjecucion[0].tiempoRequerido){ //Finalizo

				planificador.despachador.cambioContextoFinalizado(listaProcesos, colaListos, enEjecucion, listaFinalizados, reloj, memoriaDisponible, modoProcesos, ram);

			}else if(enEjecucion[0].momentoUltimoBloqueo == enEjecucion[0].momentoBloqueo && enEjecucion[0].cantidadBloqueosRelizados < enEjecucion[0].cantidadBloqueos){ //Bloqueo por E/S

				gestorInterrupciones.interrupcionBloqueo(listaProcesos, colaListos, enEjecucion, colasBloqueados, reloj, modoProcesos);

			}else if(planificador.modoProcesos==RR && enEjecucion[0].tiempoRafagaEjecucion==quantum){ //Interrupcion por quantum

				gestorInterrupciones.interrupcionQuantum(listaProcesos, colaListos, enEjecucion, reloj);

			}else{ //Continua ejecutandose

				usoCpu++;
				enEjecucion[0].pc += enEjecucion[0].saltoPC;
				enEjecucion[0].momentoUltimoBloqueo++;

				for(unsigned int i=0;i<listaProcesos.size();i++){
					if(listaProcesos[i].idProceso==enEjecucion[0].idProceso){
						listaProcesos[i].pc+=listaProcesos[i].saltoPC;
						break;
					}
				}

				if(modoProcesos==PRIORIDADAPROPIATIVO || modoProcesos==PRIORIDADNOAPROPIATIVO){
					cout << "[Reloj = " << reloj << "] Ejecutando proceso " << enEjecucion[0].idProceso << " (Prioridad = " << enEjecucion[0].prioridadProceso << ") PC: " << enEjecucion[0].pc << endl;
				}else if(modoProcesos==SJFAPROPIATIVO || modoProcesos==SJFNOAPROPIATIVO){
					cout << "[Reloj = " << reloj << "] Ejecutando proceso " << enEjecucion[0].idProceso << " (Burst time = " << enEjecucion[0].tiempoRequerido << ") PC: " << enEjecucion[0].pc << endl;
				}else{
					cout << "[Reloj = " << reloj << "] Ejecutando proceso " << enEjecucion[0].idProceso << " - PC: " << enEjecucion[0].pc << endl;
				}


				enEjecucion[0].tiempoRafagaEjecucion++;

			}

		}else{ //Cuando no hay nada ejecutandose y NO hay procesos listos
			cout << "[Reloj = " << reloj << "] Ningun proceso en ejecucion" << endl;
		}

		if(opcion!='t'){

			imprimirColas(listaProcesos,colaListos,enEjecucion,colasBloqueados,reloj,memoriaDisponible, posicionActual, modoProcesos, modoMemoria);
			imprimirRam(ram, memoriaDisponible);

			if(reloj==0){ //Limpiar buffer del cin solo al comienzo, para no comenzar en reloj 1
				cin.clear();
				cin.ignore(1, '\n');
			}

			cout << "\nPresione ENTER para continuar o escriba 't' para terminar la simulación..." << endl;

			cin.get(opcion);

		}

		for(unsigned int i=0;i<colasBloqueados.size();i++){ //aumenta rafaga en bloqueados
			if(colasBloqueados[i].size()>0){
				colasBloqueados[i][0].tiempoRafagaBloqueo++;
			}
		}

		for(unsigned int i=0;i<ram.size();i++){
			if(ram[i].idProceso==0){
				fragmentacionActual++;
			}
		}

		if(fragmentacionActual>fragmentacionMaxima){
			fragmentacionMaxima=fragmentacionActual;
		}

		fragmentacionActual=0;

		reloj++;
	}

	system("cls");

	cout << "Reloj = " <<reloj << endl;;

	imprimirColas(listaProcesos,colaListos,enEjecucion,colasBloqueados,reloj,memoriaDisponible, posicionActual, modoProcesos, modoMemoria);
	imprimirRam(ram, memoriaDisponible);

	imprimirTiemposMedios(listaFinalizados, listaFallados, reloj, usoCpu, fragmentacionMaxima);

	cout << "\nSimulación terminada, escriba 'si' para salir..." << endl;

	while(salir!="si"){
		cin >> salir;
	}

}
