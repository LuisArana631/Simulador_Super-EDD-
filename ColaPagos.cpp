#include <iostream>
#include <stdlib.h>
#include <fstream>

using namespace std;

class ColaPagos{
    public:
        int NoCliente;
        int NoCarreta;
        ColaPagos *Siguiente;
};

bool ColaVacia(ColaPagos *Inicio){
	return(Inicio!=NULL)? true:false;
}

void InsertarPago(ColaPagos *&Inicio, ColaPagos *&Fin, int NoCliente,  int NoCarreta){
	ColaPagos *NuevaCola = new ColaPagos();	
	
	NuevaCola -> NoCliente = NoCliente;
	NuevaCola -> NoCarreta = NoCarreta;
	NuevaCola -> Siguiente = NULL;
	
	if(ColaVacia(Inicio)){
		Fin -> Siguiente  = NuevaCola;
	}else{
		Inicio = NuevaCola;
	}
	Fin = NuevaCola;
}

void EliminarPago(ColaPagos *&Inicio, ColaPagos*&Fin, int& NoCliente, int& NoCarreta){
	ColaPagos *aux = Inicio;
	
	NoCliente = aux -> NoCliente;
	NoCarreta = aux -> NoCarreta;
	
	if(Inicio==Fin){
		Inicio = NULL;
		Fin = NULL;
	}else{
		Inicio = Inicio -> Siguiente;
	}
	
	delete aux;	
}

void GenerarColaPagos(ColaPagos *Inicio){
	if(ColaVacia(Inicio)){
		ofstream archivo;
		
		archivo.open("Reporte.txt",ios::app);
		
		if(archivo.fail()){
			cout<<"No se puede abrir archivo";
			exit(1);
		}
		
		archivo<<"subgraph ColaPagos {"<<endl;
		
		while(Inicio!=NULL){
			archivo<<"Cliente_"<<Inicio -> NoCliente;
			Inicio = Inicio -> Siguiente;
			if(Inicio!=NULL){
				archivo<<" -> ";
			}
		}
		
		archivo<<";"<<endl;
		archivo<<"label = \"Cola Pagos\";"<<endl;
		archivo<<"};"<<endl;
		
		archivo.close();
	}
}
