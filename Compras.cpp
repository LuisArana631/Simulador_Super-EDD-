#include <iostream>
#include <stdlib.h>
#include <fstream>

using namespace std;

class Compras{
    public:
        int NoCliente;
        int NoCarreta;
        Compras *Siguiente;
        Compras *Anterior;
};

bool ListaVacia(Compras *Inicio){
	return(Inicio!=NULL)? true:false;
}

void InsertarCompras(Compras *&Iniciopila, Compras *&Finpila, int NoCliente, int NoCarreta){
	Compras *NuevaCompra = new Compras();
	
	NuevaCompra -> NoCliente = NoCliente;
	NuevaCompra -> NoCarreta = NoCarreta;
	
	if(ListaVacia(Iniciopila)){
		Finpila  -> Siguiente = NuevaCompra;
		NuevaCompra -> Anterior = Finpila;
		NuevaCompra -> Siguiente  = Iniciopila;
		Finpila = NuevaCompra;
		Iniciopila -> Anterior = Finpila;
	}else{
		Iniciopila = NuevaCompra;
		Finpila = NuevaCompra;
		Iniciopila -> Siguiente = Iniciopila;
		Finpila -> Siguiente = Finpila;
	}
}

void EliminarInicioCompra(Compras *&Inicio, Compras *&Fin, int& NoCarreta,int& NoCliente){
	Compras *Buscar = Inicio;
	if(Inicio!=NULL){
		NoCarreta = Buscar -> NoCarreta;
		NoCliente = Buscar -> NoCliente;
		Inicio = Inicio->Siguiente;
		Inicio -> Anterior = Fin;
		Fin -> Siguiente = Inicio;
	}
	delete Buscar;
}

void EliminarUltimaCompra(Compras *&Inicio, Compras *&Fin, int& NoCarreta, int&  NoCliente){
	Compras *Buscar = Fin;		
	if(Inicio!=NULL){			
		NoCarreta = Buscar -> NoCarreta;
		NoCliente = Buscar -> NoCliente;
		Fin = Fin -> Anterior;
		Inicio -> Anterior = Fin;
		Fin -> Siguiente = Inicio;
	}
	delete Buscar;
}

void EliminarCompra(Compras *&Inicio, Compras *&Fin,int Pos, int& NoCarreta, int& NoCliente){	
	Compras *Buscar = Inicio;		
	if(Inicio!=NULL){
		for(int i=0; i<Pos; i++){
			Buscar = Buscar -> Siguiente;
		}
		Compras *AnteriorBuscar  = Buscar->Anterior;
		Compras *SiguienteBuscar = Buscar -> Siguiente;			
		NoCarreta = Buscar -> NoCarreta;
		NoCliente = Buscar -> NoCliente;				
		AnteriorBuscar -> Siguiente = Buscar -> Siguiente;
		SiguienteBuscar -> Anterior = Buscar -> Anterior;
	}	
	delete Buscar;	
}

void GenerarCompras(Compras *Inicio, Compras *Fin){
	if(ListaVacia(Inicio)){
		//Iniciando archivo
		ofstream archivo;
		
		archivo.open("Reporte.txt",ios::app);
		
		if(archivo.fail()){
			cout<<"No se puede abrir el archivo";
			exit(1);	
		}		
		
		archivo<<"subgraph Compras {"<<endl;	
		
		if(Inicio!=Fin){
						
			//Dibujando siguientes
			Compras *aux = Inicio;						
			do{
				archivo<<"Cliente_"<<Inicio->NoCliente<<"_Carreta_"<<Inicio->NoCarreta;
				Inicio = Inicio -> Siguiente;
				if(Inicio!=aux){
					archivo<<" -> ";
				}else{
					if(Inicio->Siguiente!=Fin){
						archivo<<" -> "<<"Cliente_"<<Inicio->NoCliente<<"_Carreta_"<<Inicio->NoCarreta;	
					}					
				}
			}while(Inicio!=aux);
			
				archivo<<""<<endl;
				
			//Dibujando anteriores
			aux = Fin;
			do{
				archivo<<"Cliente_"<<Fin->NoCliente<<"_Carreta_"<<Fin->NoCarreta;
				Fin = Fin -> Anterior;
				if(Fin!=aux){
					archivo<<" -> ";
				}else{
					if(Fin->Anterior!=Inicio){
						archivo<<" -> "<<"Cliente_"<<Fin->NoCliente<<"_Carreta_"<<Fin->NoCarreta;
					}										
				}
			}while(Fin!=aux);
					
		}else{		
			
			//Dibujando unico nodo
			archivo<<"Cliente_"<<Inicio->NoCliente<<"_Carreta_"<<Inicio->NoCarreta<<" -> "<<"Cliente_"<<Fin->NoCliente<<"_Carreta_"<<Fin->NoCarreta<<endl;
			archivo<<"Cliente_"<<Fin->NoCliente<<"_Carreta_"<<Fin->NoCarreta<<" -> "<<"Cliente_"<<Inicio->NoCliente<<"_Carreta_"<<Inicio->NoCarreta;
			
		}
		//Terminando archivo
		archivo<<";"<<endl;
		archivo<<"label = \"Compras\";"<<endl;
		archivo<<"};"<<endl;
		
		archivo.close();
	}
}
