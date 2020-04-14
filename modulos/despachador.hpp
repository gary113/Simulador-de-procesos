#ifndef MODULOS_DESPACHADOR_HPP_
#define MODULOS_DESPACHADOR_HPP_

#include "gestorMemoria.hpp"

struct despachador{

	struct gestorMemoria gestorMemoria;

	void comenzarEjecucion(vector <Proceso> &listaProcesos, vector <Proceso> &colaListos, vector <Proceso> &enEjecucion, int &reloj, int &modoProcesos){ //Listo -> Ejecutando

		colaListos[0].estado = EJECUTANDO;
		enEjecucion.push_back(colaListos[0]);

		for(unsigned int i=0;i<listaProcesos.size();i++){
			if(listaProcesos[i].idProceso==enEjecucion[0].idProceso){
				listaProcesos[i].estado=EJECUTANDO;
				break;
			}
		}

		if(modoProcesos==PRIORIDADAPROPIATIVO || modoProcesos==PRIORIDADNOAPROPIATIVO){
			cout << "[Reloj = " << reloj << "] Proceso " << colaListos[0].idProceso << " (Prioridad = " << colaListos[0].prioridadProceso << ") Listo -> Ejecutando" << endl;
		}else if(modoProcesos==SJFAPROPIATIVO || modoProcesos==SJFNOAPROPIATIVO){
			cout << "[Reloj = " << reloj << "] Proceso " << colaListos[0].idProceso << " (Burst time = " << colaListos[0].tiempoRequerido << ") Listo -> Ejecutando" << endl;
		}else{
			cout << "[Reloj = " << reloj << "] Proceso " << colaListos[0].idProceso << " Listo -> Ejecutando" << endl;
		}

		colaListos.erase(colaListos.begin());
	}

	void cambioContextoFinalizado(vector <Proceso> &listaProcesos, vector <Proceso> &colaListos, vector <Proceso> &enEjecucion, vector <Proceso> &listaFinalizados, int &reloj, int &memoriaDisponible, int &modoProcesos, vector<Proceso> &ram){ //Ejecutando -> Finalizado & Listo->Ejecutando

		if(colaListos.size()>0){
			cout << "[Reloj = " << reloj << "] ***** Cambio de contexto por proceso finalizado *****" << endl;
		}

		//Saca el proceso del CPU y lo finaliza

		if(modoProcesos==PRIORIDADAPROPIATIVO || modoProcesos==PRIORIDADNOAPROPIATIVO){
			cout << "[Reloj = " << reloj << "] Proceso " << enEjecucion[0].idProceso << " (Prioridad = " << enEjecucion[0].prioridadProceso << ") Ejecutando -> Finalizado" << endl;
		}else if(modoProcesos==SJFAPROPIATIVO || modoProcesos==SJFNOAPROPIATIVO){
			cout << "[Reloj = " << reloj << "] Proceso " << enEjecucion[0].idProceso << " (Burst time = " << enEjecucion[0].tiempoRequerido << ") Ejecutando -> Finalizado" << endl;
		}else{
			cout << "[Reloj = " << reloj << "] Proceso " << enEjecucion[0].idProceso << " Ejecutando -> Finalizado" << endl;
		}

		enEjecucion[0].estado = FINALIZADO;
		enEjecucion[0].momentoTermino = reloj;

		for(unsigned int i=0;i<listaProcesos.size();i++){
			if(listaProcesos[i].idProceso==enEjecucion[0].idProceso){
				listaProcesos[i].estado=FINALIZADO;
				break;
			}
		}

		gestorMemoria.liberarMemoria(enEjecucion[0], ram, memoriaDisponible);

		listaFinalizados.push_back(enEjecucion[0]);
		enEjecucion.erase(enEjecucion.begin());

		if(colaListos.size()>0){ //Saca el proceso de la cola de listos y lo ejecuta

			enEjecucion.push_back(colaListos[0]);
			colaListos.erase(colaListos.begin());

			for(unsigned int i=0;i<listaProcesos.size();i++){
				if(listaProcesos[i].idProceso==enEjecucion[0].idProceso){
					listaProcesos[i].estado=EJECUTANDO;
					break;
				}
			}

			if(modoProcesos==PRIORIDADAPROPIATIVO || modoProcesos==PRIORIDADNOAPROPIATIVO){
				cout << "[Reloj = " << reloj << "] Proceso " << enEjecucion[0].idProceso << " (Prioridad = " << enEjecucion[0].prioridadProceso << ") Listo -> Ejecutando" << endl;
			}else if(modoProcesos==SJFAPROPIATIVO || modoProcesos==SJFNOAPROPIATIVO){
				cout << "[Reloj = " << reloj << "] Proceso " << enEjecucion[0].idProceso << " (Burst time = " << enEjecucion[0].tiempoRequerido << ") Listo -> Ejecutando" << endl;
			}else{
				cout << "[Reloj = " << reloj << "] Proceso " << enEjecucion[0].idProceso << " Listo -> Ejecutando" << endl;
			}

			enEjecucion[0].estado = EJECUTANDO;

		}
	}

	void cambioContextoBloqueo(vector <Proceso> &listaProcesos, vector <Proceso> &colaListos, vector <Proceso> &enEjecucion, vector <vector<Proceso>> &colasBloqueados, int &reloj, int &modoProcesos){ //Bloqueado->Listo & Listo->Ejecutando

		int decidirNuevoDispositivo=rand()%10; //10% de probabilidad de que se cree un nuevo dispositivo (nueva cola de bloqueados)
		unsigned int colaSeleccionada=0;

		if(decidirNuevoDispositivo==0){ //Si es 0 significa que se debera crear una nueva cola
			colaSeleccionada=colasBloqueados.size();
		}else{
			colaSeleccionada=rand()%colasBloqueados.size(); //Decide en que cola existente ponerlo
		}

		enEjecucion[0].momentoUltimoBloqueo=0;

		if(colaListos.size()>0){
			cout << "[Reloj = " << reloj << "] ***** Cambio de contexto por bloqueo de E/S *****" << endl;
		}

		//Saca al proceso del CPU y lo bloquea

		enEjecucion[0].tiempoRafagaAcumulado+=enEjecucion[0].tiempoRafagaEjecucion;
		enEjecucion[0].tiempoRafagaEjecucion = 0;

		if(modoProcesos==PRIORIDADAPROPIATIVO || modoProcesos==PRIORIDADNOAPROPIATIVO){
			cout << "[Reloj = " << reloj << "] Proceso " << enEjecucion[0].idProceso << " (Prioridad = " << enEjecucion[0].prioridadProceso << ") Ejecutando -> Bloqueado" << endl;
		}else if(modoProcesos==SJFAPROPIATIVO || modoProcesos==SJFNOAPROPIATIVO){
			cout << "[Reloj = " << reloj << "] Proceso " << enEjecucion[0].idProceso << " (Burst time = " << enEjecucion[0].tiempoRequerido << ") Ejecutando -> Bloqueado" << endl;
		}else{
			cout << "[Reloj = " << reloj << "] Proceso " << enEjecucion[0].idProceso << " Ejecutando -> Bloqueado" << endl;
		}

		enEjecucion[0].cantidadBloqueosRelizados++;
		enEjecucion[0].estado = BLOQUEADO;

		for(unsigned int i=0;i<listaProcesos.size();i++){
			if(listaProcesos[i].idProceso==enEjecucion[0].idProceso){
				listaProcesos[i].estado=BLOQUEADO;
				break;
			}
		}

		if(colaSeleccionada==colasBloqueados.size()){ //Crea una nueva cola de bloqueados (nuevo dispositivo)
			vector<Proceso> nuevoDispositivo(0);
			colasBloqueados.push_back(nuevoDispositivo);
		}

		enEjecucion[0].duracionBloqueo=rand()%61+30; //Duracion del bloqueo aleatoria entre 30 y 90 unidades de tiempo

		colasBloqueados[colaSeleccionada].push_back(enEjecucion[0]);

		enEjecucion.erase(enEjecucion.begin());

		if(colaListos.size()>0){//Mete proceso de la cola de listo a ejecutarse

			enEjecucion.push_back(colaListos[0]);

			if(modoProcesos==PRIORIDADAPROPIATIVO || modoProcesos==PRIORIDADNOAPROPIATIVO){
				cout << "[Reloj = " << reloj << "] Proceso " << enEjecucion[0].idProceso << " (Prioridad = " << enEjecucion[0].prioridadProceso << ") Listo -> Ejecutando" << endl;
			}else if(modoProcesos==SJFAPROPIATIVO || modoProcesos==SJFNOAPROPIATIVO){
				cout << "[Reloj = " << reloj << "] Proceso " << enEjecucion[0].idProceso << " (Burst time = " << enEjecucion[0].tiempoRequerido << ") Listo -> Ejecutando" << endl;
			}else{
				cout << "[Reloj = " << reloj << "] Proceso " << enEjecucion[0].idProceso << " Listo -> Ejecutando" << endl;
			}

			enEjecucion[0].estado = EJECUTANDO;

			for(unsigned int i=0;i<listaProcesos.size();i++){
				if(listaProcesos[i].idProceso==enEjecucion[0].idProceso){
					listaProcesos[i].estado=EJECUTANDO;
					break;
				}
			}

			colaListos.erase(colaListos.begin());

		}
	}

	void cambioContextoQuantum(vector <Proceso> &listaProcesos, vector <Proceso> &colaListos, vector <Proceso> &enEjecucion, int &reloj){ //ejecutando -> listo (RR)

		if(colaListos.size()>0){

			//Saca el proceso del cpu y lo pone listo

			cout << "[Reloj = " << reloj << "] ***** Cambio de contexto por Quantum *****" << endl;

			enEjecucion[0].tiempoRafagaAcumulado+=enEjecucion[0].tiempoRafagaEjecucion;
			enEjecucion[0].tiempoRafagaEjecucion = 0;

			cout << "[Reloj = " << reloj << "] Proceso " << enEjecucion[0].idProceso << " Ejecutando -> Listo" << endl;

			enEjecucion[0].estado = LISTO;

			for(unsigned int i=0;i<listaProcesos.size();i++){
				if(listaProcesos[i].idProceso==enEjecucion[0].idProceso){
					listaProcesos[i].estado=LISTO;
					break;
				}
			}

			colaListos.push_back(enEjecucion[0]);
			enEjecucion.erase(enEjecucion.begin());

			//Mete el proceso de la cola de listos a ejecutarse

			enEjecucion.push_back(colaListos[0]);
			colaListos.erase(colaListos.begin());

			for(unsigned int i=0;i<listaProcesos.size();i++){
				if(listaProcesos[i].idProceso==enEjecucion[0].idProceso){
					listaProcesos[i].estado=EJECUTANDO;
					break;
				}
			}

			if(enEjecucion[0].tiempoRafagaAcumulado==0){
				enEjecucion[0].momentoComenzo = reloj;
			}

			cout << "[Reloj = " << reloj << "] Proceso " << enEjecucion[0].idProceso << " Listo -> Ejecutando" << endl;

			enEjecucion[0].estado = EJECUTANDO;

		}else{

			//Reinicia el tiempo de rafaga de ejecucion

			cout << "[Reloj = " << reloj << "] ***** Interrupción no atendida *****" << endl;

			enEjecucion[0].tiempoRafagaAcumulado+=enEjecucion[0].tiempoRafagaEjecucion;
			enEjecucion[0].tiempoRafagaEjecucion = 0;
		}
	}

	void cambioContextoNuevoProceso(vector <Proceso> &listaProcesos, vector <Proceso> &colaListos, vector <Proceso> &enEjecucion, int &reloj, int &modoProcesos){

		cout << "[Reloj = " << reloj << "] ***** Cambio de contexto por llegada de nuevo proceso *****" << endl;

		//Saca al proceso del CPU y lo pone listo

		enEjecucion[0].tiempoRafagaAcumulado+=enEjecucion[0].tiempoRafagaEjecucion;
		enEjecucion[0].tiempoRafagaEjecucion = 0;

		if(modoProcesos==PRIORIDADAPROPIATIVO || modoProcesos==PRIORIDADNOAPROPIATIVO){
			cout << "[Reloj = " << reloj << "] Proceso " << enEjecucion[0].idProceso << " (Prioridad = " << enEjecucion[0].prioridadProceso << ") Ejecutando -> Listo" << endl;
		}else if(modoProcesos==SJFAPROPIATIVO || modoProcesos==SJFNOAPROPIATIVO){
			cout << "[Reloj = " << reloj << "] Proceso " << enEjecucion[0].idProceso << " (Burst time = " << enEjecucion[0].tiempoRequerido << ") Ejecutando -> Listo" << endl;
		}else{
			cout << "[Reloj = " << reloj << "] Proceso " << enEjecucion[0].idProceso << " Ejecutando -> Listo" << endl;
		}

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

		//Mete proceso de la cola de listos al CPU

		enEjecucion.push_back(colaListos[0]);
		colaListos.erase(colaListos.begin());

		if(modoProcesos==PRIORIDADAPROPIATIVO || modoProcesos==PRIORIDADNOAPROPIATIVO){
			cout << "[Reloj = " << reloj << "] Proceso " << enEjecucion[0].idProceso << " (Prioridad = " << enEjecucion[0].prioridadProceso << ") Listo -> Ejecutando" << endl;
		}else if(modoProcesos==SJFAPROPIATIVO || modoProcesos==SJFNOAPROPIATIVO){
			cout << "[Reloj = " << reloj << "] Proceso " << enEjecucion[0].idProceso << " (Burst time = " << enEjecucion[0].tiempoRequerido << ") Listo -> Ejecutando" << endl;
		}else{
			cout << "[Reloj = " << reloj << "] Proceso " << enEjecucion[0].idProceso << " Listo -> Ejecutando" << endl;
		}

		enEjecucion[0].estado = EJECUTANDO;

		for(unsigned int i=0;i<listaProcesos.size();i++){
			if(listaProcesos[i].idProceso==enEjecucion[0].idProceso){
				listaProcesos[i].estado=EJECUTANDO;
				break;
			}
		}


	}

};

#endif /* MODULOS_DESPACHADOR_HPP_ */
