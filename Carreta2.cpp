#include <iostream>
#include <stdlib.h>
#include <fstream>

using namespace std;

class Carreta2{
    public:
        int NoCarreta;
        Carreta2 *Siguiente;
};

void InsertarCarreta2(Carreta2 *&pila, int NoCarreta){
	Carreta2 *NuevaCarreta = new Carreta2();
	NuevaCarreta -> NoCarreta = NoCarreta;
	NuevaCarreta -> Siguiente = pila;
	pila = NuevaCarreta;
}

int EliminarCarreta2(Carreta2 *&pila){
	Carreta2 *aux = pila;
	int NoCarreta = aux -> NoCarreta;
	pila = aux->Siguiente;
	delete aux;
	return NoCarreta;
}

void GenerarPila2(Carreta2 *pila){
	
	if(pila!=NULL){
		ofstream archivo;
	
		archivo.open("Reporte.txt",ios::app); //Abrir el archivo
		
		if(archivo.fail()){
			cout<<"No se pudo abrir el archivo";
			exit(1);
		}
		
		archivo<<"subgraph Pila2 {"<<endl;	
		archivo<<"  label=\"Carretas 2\";"<<endl;	
		archivo<<"    struct2 [label=\"{";
		
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
