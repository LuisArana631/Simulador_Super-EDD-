#include <iostream>
#include <stdlib.h>
#include <fstream>

using namespace std;

class Carreta1{
    public:
        int NoCarreta;
        Carreta1 *Siguiente;
};

void InsertarCarreta1(Carreta1 *&pila, int NoCarreta){   
    Carreta1 *NuevaCarreta = new Carreta1();
    NuevaCarreta -> NoCarreta = NoCarreta;
    NuevaCarreta -> Siguiente =  pila;
    pila = NuevaCarreta;
}

int EliminarCarreta1(Carreta1 *&pila){
	Carreta1 *aux  = pila;
	int NoCarreta = aux ->  NoCarreta;
	pila =  aux->Siguiente;
	delete aux;
	return NoCarreta;
}

void GenerarPila1(Carreta1 *pila){	
	
	if(pila!=NULL){
		ofstream archivo;
	
		archivo.open("Reporte.txt",ios::app);//Abrir archivo para añadir texto
		
		if(archivo.fail()){
			cout<<"No se pudo abrir archivo";
			exit(1);
		}
		
		archivo<<"subgraph Pila1 {"<<endl;	
		archivo<<"  label=\"Carretas 1\";"<<endl;	
		archivo<<"    struct1 [label=\"{";
		int pos = 0;
		while(pila!=NULL){
			archivo<<"<f"<<pos<<"> "<<pila->NoCarreta;	
			pila = pila->Siguiente;
			if(pila!=NULL){
				archivo<<"|";
			}
			pos++;
		}
		archivo<<"}\"];"<<endl;	
		archivo<<"};"<<endl;		
		
		archivo.close();	
	}
	
}
