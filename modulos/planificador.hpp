
#ifndef MODULOS_PLANIFICADOR_HPP_
#define MODULOS_PLANIFICADOR_HPP_

#include "despachador.hpp"
#include "gestorMemoria.hpp"
#include "../utilitarios/utilitarios.hpp"

struct planificador{

	int modoProcesos;
	int modoMemoria;

	struct despachador despachador;
	struct gestorMemoria gestorMemoria;

	bool alistarProcesos(vector <Proceso> &listaProcesos,vector <Proceso> &colaListos,vector <Proceso> &enEjecucion, vector<vector<Proceso>> &colasBloqueados, int &reloj, int &memoriaDisponible, vector<Proceso> &ram, unsigned int &posicionActual){ //Nuevo->Listo & Bloqueado->Listo

		bool salida=false;
		bool exitoAlistar=false;

		for(unsigned int i=0;i<listaProcesos.size();i++){ //Nuevo->Listo

			if(reloj>0 && listaProcesos[i].momentoLlegada==reloj){
				posicionActual++;
			}

			if(listaProcesos[i].momentoLlegada <= reloj && listaProcesos[i].estado==NUEVO && listaProcesos[i].tamanioProceso<=memoriaDisponible){

				exitoAlistar=gestorMemoria.insertarProceso(listaProcesos[i], ram, memoriaDisponible, reloj, modoMemoria);

				if(exitoAlistar==true){
					if(modoProcesos==PRIORIDADAPROPIATIVO || modoProcesos==PRIORIDADNOAPROPIATIVO){
						cout << "[Reloj = " << reloj << "] Proceso " << listaProcesos[i].idProceso << " (Prioridad = " << listaProcesos[i].prioridadProceso << ") Nuevo -> Listo" << endl;
					}else if(modoProcesos==SJFAPROPIATIVO || modoProcesos==SJFNOAPROPIATIVO){
						cout << "[Reloj = " << reloj << "] Proceso " << listaProcesos[i].idProceso << " (Burst time = " << listaProcesos[i].tiempoRequerido << ") Nuevo -> Listo" << endl;
					}else{
						cout << "[Reloj = " << reloj << "] Proceso " << listaProcesos[i].idProceso << " Nuevo -> Listo" << endl;
					}

					listaProcesos[i].momentoComenzo = reloj;
					listaProcesos[i].estado = LISTO;
					colaListos.push_back(listaProcesos[i]);

					salida=true;
				}else{
					listaProcesos[i].tiempoEsperandoMemoria++;
				}

			}
		}

		for(unsigned int i=0;i<colasBloqueados.size();i++){ //Bloqueado->Listo

			if(colasBloqueados[i].size()>0){
				if(colasBloqueados[i][0].tiempoRafagaBloqueo >= colasBloqueados[i][0].duracionBloqueo){

					colasBloqueados[i][0].tiempoRafagaBloqueo = 0;

					if(modoProcesos==PRIORIDADAPROPIATIVO || modoProcesos==PRIORIDADNOAPROPIATIVO){
						cout << "[Reloj = " << reloj << "] Proceso " << colasBloqueados[i][0].idProceso << " (Prioridad = " << colasBloqueados[i][0].prioridadProceso << ") Bloqueado -> Listo" << endl;
					}else if(modoProcesos==SJFAPROPIATIVO || modoProcesos==SJFNOAPROPIATIVO){
						cout << "[Reloj = " << reloj << "] Proceso " << colasBloqueados[i][0].idProceso << " (Burst time = " << colasBloqueados[i][0].tiempoRequerido << ") Bloqueado -> Listo" << endl;
					}else{
						cout << "[Reloj = " << reloj << "] Proceso " << colasBloqueados[i][0].idProceso << " Bloqueado -> Listo" << endl;
					}

					colasBloqueados[i][0].estado = LISTO;

					for(unsigned int j=0;j<listaProcesos.size();j++){
						if(listaProcesos[j].idProceso==colasBloqueados[i][0].idProceso){
							listaProcesos[j].estado=LISTO;
							break;
						}
					}

					colaListos.push_back(colasBloqueados[i][0]);
					colasBloqueados[i].erase(colasBloqueados[i].begin());

					salida=true;
				}
			}
		}

		acomodarColaListos(colaListos);
		return salida;
	}

	void acomodarColaListos(vector <Proceso> &colaListos){

		if(modoProcesos==PRIORIDADAPROPIATIVO || modoProcesos==PRIORIDADNOAPROPIATIVO){
			sort(colaListos.begin(),colaListos.end(),compararPrioridades);
		}else if(modoProcesos==SJFAPROPIATIVO || modoProcesos==SJFNOAPROPIATIVO){
			sort(colaListos.begin(),colaListos.end(),compararBurstTime);
		}
	}

};

#endif /* MODULOS_PLANIFICADOR_HPP_ */
