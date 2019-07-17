#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <time.h>

using namespace std;

class Cajas{
    public:
        int NoCaja;
        int TiempoServicio;
        int TiempoTranscurrido;
        int NoCliente;
        int NoCarreta;
        bool Estado;
        Cajas *Siguiente;
        Cajas *Anterior;
};

bool ListaVacia(Cajas *Inicio){
	return(Inicio!=NULL)? true:false;
}

void InsertarCaja(Cajas *&InicioCaja, Cajas *&FinCaja, int NoCaja, int TiempoServicio, int TiempoTrans, int NoCarreta, int NoCliente, bool Estado){
	Cajas *NuevaCaja = new Cajas();	
	
	NuevaCaja -> NoCaja = NoCaja;
	NuevaCaja -> TiempoServicio = TiempoServicio;
	NuevaCaja -> TiempoTranscurrido = TiempoTrans;
	NuevaCaja -> NoCliente = NoCliente;
	NuevaCaja -> NoCarreta = NoCarreta;
	NuevaCaja -> Estado = Estado;	
	NuevaCaja -> Siguiente = NULL;
	
	if(ListaVacia(InicioCaja)){		
		FinCaja -> Siguiente = NuevaCaja;
		NuevaCaja -> Anterior = FinCaja;
	}else{						
		NuevaCaja -> Anterior = NULL;		
		InicioCaja = NuevaCaja;
	}		
	FinCaja = NuevaCaja;
}

bool VerificarEstado(Cajas *Inicio){
	bool Estado = false;
	while(Inicio!=NULL){
		if(Inicio->Estado==true){
			Estado = true;
			break;
		}else{
			Inicio = Inicio -> Siguiente;
		}
	}
	return Estado;
}

void ModificarCaja(Cajas *&Inicio, int NoCliente, int NoCarreta, int& NoCaja){
	Cajas *aux = Inicio;
	while(aux!=NULL){
		if(aux->Estado==true){
			aux -> NoCliente = NoCliente;
			aux -> NoCarreta = NoCarreta;			
			aux -> TiempoTranscurrido = aux -> TiempoServicio;
			NoCaja = aux -> NoCaja;
			aux -> Estado = false;
			break;
		}else{
			aux = aux -> Siguiente;
		}		
	}
}

int EvaluarTurno(Cajas *&Inicio){
	Cajas *aux = Inicio;
	int CarretasLibre = 0;
	while(aux!=NULL){
		if(aux->TiempoTranscurrido!=0){
			int Tiempo = aux->TiempoTranscurrido;
			Tiempo = Tiempo - 1;
			aux -> TiempoTranscurrido = Tiempo;
		}else{
			int NoCarreta = aux -> NoCarreta;
			int NoCliente = aux -> NoCliente;
			int NoCaja = aux -> NoCaja;		
			cout<<"El cliente "<<NoCliente<<" salio de la caja "<<NoCaja<<"."<<endl;
			CarretasLibre++;
			aux -> NoCarreta = 0;
			aux -> NoCliente = 0;
			aux -> Estado = true;
			aux -> TiempoTranscurrido = aux -> TiempoServicio;			
		}	
		aux = aux -> Siguiente;		
	}
	
	return CarretasLibre;
}
	

void GenerarCajas(Cajas *Inicio, Cajas *Fin){
	if(ListaVacia(Inicio)){
		ofstream archivo;
		
		archivo.open("Reporte.txt",ios::app);
		
		if(archivo.fail()){
			cout<<"No se puede abrir archivo";
			exit(1);
		}	
	
		archivo<<"subgraph Cajas {"<<endl;
		
		while(Inicio!=NULL){
			archivo<<"Caja_"<<Inicio->NoCaja<<"_Turnos_"<<Inicio->TiempoServicio<<"_Estado_";
			if(Inicio->Estado==true){
				archivo<<"Libre";
			}else{
				archivo<<"Ocupado";
			}
			Inicio =  Inicio -> Siguiente;
			if(Inicio!=NULL){
				archivo<<"  -> ";
			}
		}
			archivo<<""<<endl;
		while(Fin!=NULL){
			archivo<<"Caja_"<<Fin->NoCaja<<"_Turnos_"<<Fin->TiempoServicio<<"_Estado_";
			if(Fin->Estado==true){
				archivo<<"Libre";
			}else{
				archivo<<"Ocupado";
			}
			Fin = Fin -> Anterior;
			if(Fin!=NULL){
				archivo<<" -> ";
			}
		}
	
		archivo<<";"<<endl;
		archivo<<"label = \"Cajas\";"<<endl;
		archivo<<"};"<<endl;
		
		archivo.close();
	}
}
