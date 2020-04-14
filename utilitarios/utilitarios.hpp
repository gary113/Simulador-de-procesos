#ifndef UTILITARIOS_UTILITARIOS_HPP_
#define UTILITARIOS_UTILITARIOS_HPP_

void imprimirProcesos(vector <Proceso> &listaProcesos);
void imprimirTiemposMedios(vector <Proceso> &listaProcesosFinalizados, vector<Proceso> &listaFallados, int &reloj, int &usoCpu, int &fragmentacionMaxima);
void imprimirColas(vector<Proceso> &listaProcesos, vector<Proceso> &colaListos, vector<Proceso> &enEjecucion, vector<vector<Proceso>> &colasBloqueados, int &reloj, int &memoriaDisponible, unsigned int &posicionActual, int modoProcesos, int modoMemoria);
void imprimirRam(vector<Proceso> &ram, int &memoriaDisponible);
bool compararPrioridades(Proceso a, Proceso b);
bool compararBurstTime(Proceso a, Proceso b);

#endif
