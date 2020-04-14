#ifndef PRINCIPAL_HPP_
#define PRINCIPAL_HPP_

#include <iostream>
#include <ctime>
#include <vector>
#include <algorithm>
#include <windows.h>

using namespace std;

const int NUEVO = 0;
const int LISTO = 1;
const int EJECUTANDO = 2;
const int BLOQUEADO = 3;
const int FINALIZADO = 4;
const int ABORTADO = 5;

const int RR = 10;
const int PRIORIDADAPROPIATIVO=11;
const int SJFAPROPIATIVO=12;
const int FCFS=13;
const int PRIORIDADNOAPROPIATIVO=14;;
const int SJFNOAPROPIATIVO=15;

const int FIRSTFIT=20;
const int BESTFIT=21;
const int WORSTFIT=22;

const int MEMORIATOTAL=2048;
const int TAMANIOSO=800;

const int TIMER = 250;

struct Proceso{
	//autom�tico
	int idProceso;
	int cantidadBloqueos;
	int estado;
	int momentoLlegada;
	int prioridadProceso;
	int pc;
	int direccionInicial;
	int heap;
	int datos;
	int stack;
	int instrucciones;
	bool tieneError;

	//manual
	int tamanioProceso; //En MB
	int tiempoRequerido; //En unidades de tiempo

	//datos utiles (automatico)
	int momentoBloqueo;
	int tiempoRafagaEjecucion;
	int tiempoRafagaAcumulado;
	int momentoComenzo;
	int momentoTermino;
	int duracionBloqueo;
	int tiempoRafagaBloqueo;
	int cantidadBloqueosRelizados;
	int saltoPC;
	int momentoUltimoBloqueo;
	int momentoAlistado;
	int tiempoEsperandoMemoria;

	Proceso crearProcesoAleatorio(vector <Proceso> listaProcesos){

		struct Proceso nuevoProceso;

		nuevoProceso.tamanioProceso = rand()%291+10;
		nuevoProceso.tiempoRequerido = rand()%101 + 100;

		if(listaProcesos.size()>0){
			nuevoProceso.momentoLlegada = rand()%100+1 + listaProcesos[listaProcesos.size()-1].momentoLlegada;
		}else{
			nuevoProceso.momentoLlegada = 0;
		}

		nuevoProceso.prioridadProceso = rand()%10 +1;
		nuevoProceso.idProceso = listaProcesos.size()+1;
		nuevoProceso.tieneError = generarError();
		nuevoProceso.cantidadBloqueos = nuevoProceso.calcularCantidadBloqueos();
		nuevoProceso.momentoBloqueo = nuevoProceso.calcularMomentoBloqueo();
		nuevoProceso.tiempoRafagaAcumulado=0;
		nuevoProceso.tiempoRafagaEjecucion=0;
		nuevoProceso.estado = NUEVO;
		nuevoProceso.tiempoRafagaBloqueo = 0;
		nuevoProceso.duracionBloqueo = 0;
		nuevoProceso.cantidadBloqueosRelizados = 0;
		nuevoProceso.pc=0;
		nuevoProceso.direccionInicial=0;
		nuevoProceso.momentoUltimoBloqueo=0;
		nuevoProceso.momentoAlistado=0;
		nuevoProceso.tiempoEsperandoMemoria=0;
		nuevoProceso.heap=nuevoProceso.tamanioProceso*0.3;
		nuevoProceso.stack=nuevoProceso.tamanioProceso*0.1;
		nuevoProceso.datos=nuevoProceso.tamanioProceso*0.2;
		nuevoProceso.instrucciones=nuevoProceso.tamanioProceso-(nuevoProceso.heap+nuevoProceso.stack+nuevoProceso.datos);
		nuevoProceso.saltoPC = nuevoProceso.instrucciones*1000/nuevoProceso.tiempoRequerido;

		return nuevoProceso;
	}


	Proceso crearProcesoManual(vector <Proceso> listaProcesos){

		struct Proceso nuevoProceso;
		int temp = 0;

		cout << "Ingrese el tamanio del proceso (10 - 300 MB): "; cin>> temp;
		nuevoProceso.tamanioProceso = temp;
		cout << "Ingrese el burst time (100 - 200 unidades de tiempo): "; cin >> temp;
		nuevoProceso.tiempoRequerido = temp;

		if(listaProcesos.size()>0){
			nuevoProceso.momentoLlegada = rand()%100+1 + listaProcesos[listaProcesos.size()-1].momentoLlegada;
		}else{
			nuevoProceso.momentoLlegada = 0;
		}

		nuevoProceso.prioridadProceso = rand()%10 +1;
		nuevoProceso.idProceso = listaProcesos.size()+1;
		nuevoProceso.tieneError = generarError();
		nuevoProceso.cantidadBloqueos = nuevoProceso.calcularCantidadBloqueos();
		nuevoProceso.momentoBloqueo = nuevoProceso.calcularMomentoBloqueo();
		nuevoProceso.tiempoRafagaAcumulado=0;
		nuevoProceso.tiempoRafagaEjecucion=0;
		nuevoProceso.estado = NUEVO;
		nuevoProceso.tiempoRafagaBloqueo = 0;
		nuevoProceso.duracionBloqueo = 0;
		nuevoProceso.cantidadBloqueosRelizados = 0;
		nuevoProceso.pc=0;
		nuevoProceso.direccionInicial=0;
		nuevoProceso.momentoUltimoBloqueo=0;
		nuevoProceso.momentoAlistado=0;
		nuevoProceso.tiempoEsperandoMemoria=0;
		nuevoProceso.heap=nuevoProceso.tamanioProceso*0.3;
		nuevoProceso.stack=nuevoProceso.tamanioProceso*0.1;
		nuevoProceso.datos=nuevoProceso.tamanioProceso*0.2;
		nuevoProceso.instrucciones=nuevoProceso.tamanioProceso-(nuevoProceso.heap+nuevoProceso.stack+nuevoProceso.datos);
		nuevoProceso.saltoPC = nuevoProceso.instrucciones*1000/nuevoProceso.tiempoRequerido;

		return nuevoProceso;
	}

	bool generarError(){

		int error = rand()%200;

		if(error==0){
			return true;
		}else{
			return false;
		}
	}

	int calcularCantidadBloqueos(){
		int cantidadInterrupciones = tiempoRequerido*0.09 - 8; //ecuacion de una recta (de 1 a 10 interrupciones)
		return cantidadInterrupciones;
	}

	int calcularMomentoBloqueo(){
		int momentoBloqueo = tiempoRequerido/(cantidadBloqueos+1);
		return momentoBloqueo;
	}

};

#endif
