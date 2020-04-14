
#ifndef MODULOS_GESTORMEMORIA_HPP_
#define MODULOS_GESTORMEMORIA_HPP_

#include "../principal.hpp"

struct gestorMemoria{

	bool insertarProceso(Proceso &procesoInsertar, vector<Proceso> &ram, int &memoriaDisponible, int &reloj, int modoMemoria){

		bool exito=false;
		int direccionInicialActual=0;

		if(modoMemoria==FIRSTFIT){ //El primero
			for(unsigned int i=0;i<ram.size();i++){

				if(i>0){
					direccionInicialActual+=ram[i-1].tamanioProceso*1000;
				}

				if(ram[i].idProceso==0 && ram[i].tamanioProceso>=procesoInsertar.tamanioProceso){

					procesoInsertar.momentoAlistado=reloj;
					procesoInsertar.pc=direccionInicialActual+(procesoInsertar.tamanioProceso-procesoInsertar.instrucciones)*1000;
					procesoInsertar.direccionInicial=direccionInicialActual+(procesoInsertar.tamanioProceso-procesoInsertar.instrucciones)*1000;

					ram[i].tamanioProceso-=procesoInsertar.tamanioProceso;
					if(ram[i].tamanioProceso==0){
						ram.erase(ram.begin()+i);
					}
					memoriaDisponible-=procesoInsertar.tamanioProceso;

					ram.insert(ram.begin()+i,procesoInsertar);

					exito=true;

					break;
				}
			}

		}else if(modoMemoria==BESTFIT){ //El mejor

			int mejorPosicion=-1;
			int resta=MEMORIATOTAL;

			for(unsigned int i=0;i<ram.size();i++){

				if(ram[i].idProceso==0 && ram[i].tamanioProceso>=procesoInsertar.tamanioProceso){ //Para buscar el mejor lugar

					if(ram[i].tamanioProceso-procesoInsertar.tamanioProceso<resta){
						mejorPosicion=i;
						resta=ram[i].tamanioProceso-procesoInsertar.tamanioProceso;
					}

				}
			}

			if(mejorPosicion>-1){

				if(mejorPosicion==0){
					direccionInicialActual=0;
				}else{
					for(int i=0;i<mejorPosicion;i++){
						direccionInicialActual+=ram[i].tamanioProceso*1000;
					}
				}

				procesoInsertar.momentoAlistado=reloj;
				procesoInsertar.pc=direccionInicialActual+(procesoInsertar.tamanioProceso-procesoInsertar.instrucciones)*1000;
				procesoInsertar.direccionInicial=direccionInicialActual+(procesoInsertar.tamanioProceso-procesoInsertar.instrucciones)*1000;

				ram[mejorPosicion].tamanioProceso-=procesoInsertar.tamanioProceso;
				if(ram[mejorPosicion].tamanioProceso==0){
					ram.erase(ram.begin()+mejorPosicion);
				}
				memoriaDisponible-=procesoInsertar.tamanioProceso;

				ram.insert(ram.begin()+mejorPosicion,procesoInsertar);

				exito=true;
			}

		}else if(modoMemoria==WORSTFIT){ //El peor

			int peorPosicion=-1;
			int resta=0;

			for(unsigned int i=0;i<ram.size();i++){

				if(ram[i].idProceso==0 && ram[i].tamanioProceso>=procesoInsertar.tamanioProceso){ //Para buscar el peor lugar

					if(ram[i].tamanioProceso-procesoInsertar.tamanioProceso>=resta){
						peorPosicion=i;
						resta=ram[i].tamanioProceso-procesoInsertar.tamanioProceso;
					}

				}
			}

			if(peorPosicion>-1){

				if(peorPosicion==0){
					direccionInicialActual=0;
				}else{
					for(int i=0;i<peorPosicion;i++){
						direccionInicialActual+=ram[i].tamanioProceso*1000;
					}
				}

				procesoInsertar.momentoAlistado=reloj;
				procesoInsertar.pc=direccionInicialActual+(procesoInsertar.tamanioProceso-procesoInsertar.instrucciones)*1000;
				procesoInsertar.direccionInicial=direccionInicialActual+(procesoInsertar.tamanioProceso-procesoInsertar.instrucciones)*1000;

				ram[peorPosicion].tamanioProceso-=procesoInsertar.tamanioProceso;
				if(ram[peorPosicion].tamanioProceso==0){
					ram.erase(ram.begin()+peorPosicion);
				}
				memoriaDisponible-=procesoInsertar.tamanioProceso;

				ram.insert(ram.begin()+peorPosicion,procesoInsertar);

				exito=true;
			}

		}

		return exito;
	}

	void liberarMemoria(Proceso &procesoEliminar, vector<Proceso> &ram, int &memoriaDisponible){

		memoriaDisponible+=procesoEliminar.tamanioProceso;

		for(unsigned int i=0;i<ram.size();i++){
			if(ram[i].idProceso==procesoEliminar.idProceso){
				if(i==0){ //Esta al comienzo

					if(ram[i+1].idProceso==0){
						ram[i+1].tamanioProceso+=ram[i].tamanioProceso;
						ram.erase(ram.begin()+i);
					}else{
						ram[i].idProceso=0;
					}

				}else if(i==ram.size()-1){ //Esta al final

					if(ram[i-1].idProceso==0){
						ram[i-1].tamanioProceso+=ram[i].tamanioProceso;
						ram.erase(ram.begin()+i);
					}else{
						ram[i].idProceso=0;
					}

				}else{ //Esta al medio

					if(ram[i-1].idProceso==0 && ram[i+1].idProceso!=0){ //Vacio a la izquierda
						ram[i-1].tamanioProceso+=ram[i].tamanioProceso;
						ram.erase(ram.begin()+i);
					}else if(ram[i-1].idProceso!=0 && ram[i+1].idProceso==0){ //Vacio a la derecha
						ram[i+1].tamanioProceso+=ram[i].tamanioProceso;
						ram.erase(ram.begin()+i);
					}else if(ram[i-1].idProceso==0 && ram[i+1].idProceso==0){ //Vacio a ambos lados
						ram[i-1].tamanioProceso+=(ram[i].tamanioProceso+ram[i+1].tamanioProceso);
						ram.erase(ram.begin()+(i+1));
						ram.erase(ram.begin()+i);
					}else{ //Sin vacios a los lados
						ram[i].idProceso=0;
					}

				}
				break;
			}
		}

	}
};



#endif
