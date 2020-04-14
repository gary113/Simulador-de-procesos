
#include "pantallas/pantallas.hpp"
#include <clocale>

using namespace std;

int main() {

	setlocale(LC_CTYPE,"Spanish"); //Para poder usar � y tildes

	srand (time(0)); //Semilla para rand()

	int opcion = 0;
	vector<Proceso> listaProcesos(0);

	while(true){

		system("cls");
		cout<<"\nTrabajo III\n"<<endl;
		cout<<"Sistemas Operativos 2019-2 - Grupo 4\n"<<endl;
		cout << "Alummos:" << endl;
		cout << "Candia Nina, Gary" << endl;
		cout << "D�vila Rosales, Alexander" << endl;
		cout << "Rodriguez Carre�o, Alexander" << endl;
		cout << "Vivar Carhuavilca, V�ctor\n" << endl;
		cout<<"1. Ver procesos"<<endl;
		cout<<"2. Ejecutar simulaci�n con algoritmos apropiativos"<<endl;
		cout<<"3. Ejecutar simulaci�n con algoritmos no apropiativos"<<endl;
		cout<<"4. Salir"<<endl;
		cout<<"Seleccione una opci�n: "; cin>>opcion;

		if(opcion == 1){

			pantallaVerProcesos(listaProcesos);

		}else if(opcion == 2){

			pantallaApropiativos(listaProcesos);

		}else if(opcion==3){

			pantallaNoApropiativos(listaProcesos);

		}else if(opcion==4){
			return 0;
		}

	}

	return 0;
}

