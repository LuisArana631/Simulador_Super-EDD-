#include <iostream>
#include <stdlib.h>
#include <fstream>

using namespace std;

class EsperaCarreta{
    public:
        int NoCliente;
        EsperaCarreta *Siguiente;
};

bool ColaVacia(EsperaCarreta *Inicio){
	return (Inicio!=NULL)? true:false;	
}

void InsertarClienteCarreta(EsperaCarreta *&Inicio, EsperaCarreta *&Fin, int NoCliente){
	EsperaCarreta *NuevaCola = new EsperaCarreta();
	
	NuevaCola -> NoCliente = NoCliente;
	NuevaCola -> Siguiente = NULL;
	
	if(ColaVacia(Inicio)){
		Fin -> Siguiente  = NuevaCola; 	
	}else{
		Inicio = NuevaCola;		
	}	
	Fin = NuevaCola;
}

int EliminarClienteCarreta(EsperaCarreta *&Inicio, EsperaCarreta *&Fin){	
	EsperaCarreta *aux = Inicio;
	int NoCliente = aux -> NoCliente;
	
	if(Inicio == Fin){
		Inicio = NULL;
		Fin = NULL;
	}else{
		Inicio = Inicio -> Siguiente;
	}
	
	delete aux;	
	
	return NoCliente;
}

void GenerarColaCarreta(EsperaCarreta *Inicio){
	if(ColaVacia(Inicio)){
		ofstream archivo;
		
		archivo.open("Reporte.txt",ios::app);
		
		if(archivo.fail()){
			cout<<"No se puede abrir archivo";
			exit(1);
		}
		
		archivo<<"subgraph ColaCarreta {"<<endl;		
				
		while(Inicio!=NULL){						
			archivo<<"Cliente_"<<Inicio -> NoCliente;
			Inicio = Inicio -> Siguiente;
			if(Inicio!=NULL){
				archivo<<" -> ";
			}
		}
		
		archivo<<";"<<endl;
		archivo<<"label = \"Espera Carreta\";"<<endl;
		archivo<<"};"<<endl;
		
		archivo.close();
	}
}






