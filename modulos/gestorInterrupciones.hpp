#ifndef MODULOS_GESTORINTERRUPCIONES_HPP_
#define MODULOS_GESTORINTERRUPCIONES_HPP_

#include "despachador.hpp"
#include "gestorMemoria.hpp"

struct gestorInterrupciones{

	struct despachador despachador;
	struct gestorMemoria gestorMemoria;

	void interrupcionTimer(vector <Proceso> &listaProcesos, vector <Proceso> &colaListos, vector<Proceso> &enEjecucion, vector<Proceso> &listaFallados, vector<vector<Proceso>> &colasBloqueados, int &reloj, int &memoriaDisponible, vector<Proceso> &ram){

		cout << "[Reloj = " << reloj << "] ***** Interrupción por timer *****" << endl;

		//Quitar proceso al CPU

		if(enEjecucion.size()>0){ //Ejecutando->Listo

			enEjecucion[0].tiempoRafagaAcumulado+=enEjecucion[0].tiempoRafagaEjecucion;
			enEjecucion[0].tiempoRafagaEjecucion = 0;

			cout << "[Reloj = " << reloj << "] Proceso " << enEjecucion[0].idProceso << " Ejecutando -> Listo" << endl;

			enEjecucion[0].cantidadBloqueosRelizados++;
			enEjecucion[0].estado = LISTO;

			for(unsigned int i=0;i<listaProcesos.size();i++){
				if(listaProcesos[i].idProceso==enEjecucion[0].idProceso){
					listaProcesos[i].estado=LISTO;
					break;
				}
			}

			colaListos.push_back(enEjecucion[0]);
			enEjecucion.erase(enEjecucion.begin());
		}

		//Busqueda de errores

		for(unsigned int i=0;i<colaListos.size();i++){ //Listo->Abortado
			if(colaListos[i].tieneError == true && colaListos[i].tiempoRafagaAcumulado>0){

				cout << "[Reloj = " << reloj << "] El proceso " << colaListos[i].idProceso << " tiene error" << endl;
				cout << "[Reloj = " << reloj << "] Proceso " << colaListos[i].idProceso << " Listo -> Abortado" << endl;

				colaListos[i].estado = ABORTADO;
				colaListos[i].momentoTermino = reloj;

				for(unsigned int j=0;j<listaProcesos.size();j++){
					if(listaProcesos[j].idProceso==colaListos[i].idProceso){
						listaProcesos[j].estado=ABORTADO;
						break;
					}
				}

				listaFallados.push_back(colaListos[i]);
				gestorMemoria.liberarMemoria(colaListos[i], ram, memoriaDisponible);
				colaListos.erase(colaListos.begin()+i);

				i--;
			}
		}

		for(unsigned int i=0;i<colasBloqueados.size();i++){ //Bloqueado->Abortado
			for(unsigned int j=0;j<colasBloqueados[i].size();j++){
				if(colasBloqueados[i][j].tieneError == true && colasBloqueados[i][j].tiempoRafagaAcumulado>0){

					cout << "[Reloj = " << reloj << "] El proceso " << colasBloqueados[i][j].idProceso << " tiene error" << endl;
					cout << "[Reloj = " << reloj << "] Proceso " << colasBloqueados[i][j].idProceso << " Bloqueado -> Abortado" << endl;

					colasBloqueados[i][j].estado = ABORTADO;
					colasBloqueados[i][j].momentoTermino = reloj;

					for(unsigned int k=0;k<listaProcesos.size();k++){
						if(listaProcesos[k].idProceso==colasBloqueados[i][j].idProceso){
							listaProcesos[k].estado=ABORTADO;
							break;
						}
					}

					listaFallados.push_back(colasBloqueados[i][j]);
					gestorMemoria.liberarMemoria(colasBloqueados[i][j], ram, memoriaDisponible);
					colasBloqueados[i].erase(colasBloqueados[i].begin()+j);
					j--;
				}
			}

		}

	}

	void interrupcionBloqueo(vector <Proceso> &listaProcesos, vector <Proceso> &colaListos, vector<Proceso> &enEjecucion, vector<vector<Proceso>> &colasBloqueados, int &reloj, int &modoProcesos){

		cout << "[Reloj = " << reloj << "] ***** Interrupción por bloqueo de E/S *****" << endl;

		despachador.cambioContextoBloqueo(listaProcesos, colaListos, enEjecucion, colasBloqueados, reloj, modoProcesos);

	}

	void interrupcionQuantum(vector <Proceso> &listaProcesos, vector <Proceso> &colaListos, vector<Proceso> &enEjecucion, int &reloj){

		cout << "[Reloj = " << reloj << "] ***** Interrupción por Quantum *****" << endl;

		despachador.cambioContextoQuantum(listaProcesos, colaListos, enEjecucion, reloj);
	}

	bool interrupcionNuevoProceso(vector <Proceso> &listaProcesos, vector <Proceso> &colaListos, vector<Proceso> &enEjecucion, int &reloj, int &modoProcesos){

		bool salida=false;

		if(modoProcesos==PRIORIDADAPROPIATIVO){

			cout << "[Reloj = " << reloj << "] ***** Interrupción por llegada de nuevo proceso *****" << endl;

			if(colaListos[0].prioridadProceso>enEjecucion[0].prioridadProceso){
				despachador.cambioContextoNuevoProceso(listaProcesos, colaListos, enEjecucion, reloj, modoProcesos);
				salida=true;
			}else{
				cout << "[Reloj = " << reloj << "] ***** Interrupción no atendida *****" << endl;
			}

		}else if(modoProcesos==SJFAPROPIATIVO){
			cout << "[Reloj = " << reloj << "] ***** Interrupción por llegada de nuevo proceso *****" << endl;

			if(colaListos[0].tiempoRequerido<enEjecucion[0].tiempoRequerido){
				despachador.cambioContextoNuevoProceso(listaProcesos, colaListos, enEjecucion, reloj, modoProcesos);
				salida=true;
			}else{
				cout << "[Reloj = " << reloj << "] ***** Interrupción no atendida *****" << endl;
			}
		}

		return salida;
	}

};




#endif /* MODULOS_GESTORINTERRUPCIONES_HPP_ */
