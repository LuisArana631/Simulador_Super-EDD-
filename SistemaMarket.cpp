#include <iostream>
#include <conio.h>
#include <stdlib.h>
#include <fstream>
#include <time.h>
//Incluir todas las clases
#include "Carreta1.cpp"
#include "Carreta2.cpp"
#include "EsperaCarreta.cpp"
#include "Cajas.cpp"
#include "ColaPagos.cpp"
#include "Compras.cpp"

using namespace std;

//Variables globales para la configuracion del sistema
	//Variables de configuracion inicial
	int ClientesCarretas = 0;
	int CarretasPila = 0;
	int ClientesCompras = 0;
	int ClientesPagos = 0;
	int CajasNum = 0;
	//Contador de turnos
	int turnos = 1;
	//Contenedor de clientes nuevos
	int ClientesNews=0;
	//Contador de clientes en el sistema
	int TotalCliente = 1;
	//Personas esperando carretas
	int ClienteSinCarreta = 0;
	//Contador de cliente comprando
	int ClientesComprando = 0;
	//Contador de clientes en cola de pagos
	int ClientesdePagos = 0;
	//Variables para Compras y pagos
	int ClienteExtraer = 0;
	int CarretaExtraer = 0;
	//Variables para caja	
	int ClienteCaja = 0;
	int CarretaCaja = 0;
	int CajaUsada =0;
	//Almacenar carretas libres
	int CarretasLibres = 0;	
	int NumeradorCarreta = 1;	

//Inicializando todas las listas, se inicializan globales para poder usarse en todo el sistmea
//Pila de carretas
Carreta1 *Pila1 = NULL;
Carreta2 *Pila2 = NULL;
//Cajas
Cajas *CajasInicio = NULL;
Cajas *CajasFin = NULL;
//Cola de espera
EsperaCarreta *FrenteCarreta = NULL;
EsperaCarreta *FinCarreta =NULL;
//Lista de compras
Compras *ComprasInicio = NULL;
Compras *ComprasFin = NULL;
//Cola Pagos
ColaPagos *PagosInicio = NULL;
ColaPagos *PagosFin = NULL;

//Creacion de metodos para su uso
void Turnos();
void GenerarReporte();
void ConfiguracionInicial();
void MenuTurnos();
void PrimerTurno();
void IniciarSimulacion();
void MenuInicial();

//Menu entre turnos
void MenuTurnos(){
	int Opcion;
	//Menu Grafico
	cout<<"*******************************************"<<endl;
	cout<<"1. Ingresar Nuevos Clientes"<<endl;
	cout<<"2. Reporte"<<endl;
	cout<<"3. Salir"<<endl;
	cout<<"*******************************************"<<endl;
	cout<<"Opcion a seleccionar: ";	
	cin>>Opcion;			
	cout<<"*******************************************"<<endl;
	//Casos para realizar segun la opcion
	switch(Opcion){
		case  1:
			cout<<"Cantidad de clientes nuevos: ";			
			cin>>ClientesNews;
			cout<<"*******************************************"<<endl;
			Turnos();			
			break;
		case 2:
			GenerarReporte();
			MenuTurnos();
			break;
		case 3:
			exit(0);
			break;
		default:
			cout<<"*******************************************"<<endl;
			cout<<"****** Opcion seleccionada no existe ******"<<endl;
			cout<<"*******************************************"<<endl;
			MenuTurnos();
	}
}

void GenerarReporte(){
	
	ofstream Reporte;
	
	Reporte.open("Reporte.txt",ios::out); //Abrir el archivo
		
	if(Reporte.fail()){
		cout<<"No se pudo abrir el archivo";
		exit(1);
	}
	
	Reporte<<"digraph Reporte {"<<endl;
	Reporte<<"graph [fontsize=10 fontname=\"Verdana\" compound=true];"<<endl;
    Reporte<<"node [shape=record fontsize=10 fontname=\"Verdana\"];"<<endl;
	Reporte.close();
		//Agregar todas las graficas		
		GenerarColaCarreta(FrenteCarreta);
		GenerarPila1(Pila1);
		GenerarPila2(Pila2);		
		GenerarCompras(ComprasInicio,ComprasFin);
		GenerarColaPagos(PagosInicio);		
		GenerarCajas(CajasInicio,CajasFin);
	Reporte.open("Reporte.txt",ios::app);		
	Reporte<<"}"<<endl;
	Reporte.close();					
	system("dot -Tpng Reporte.txt -o Reporte.png");	
	system("Reporte.png");
		
}

//Metodo para el primer turno
void PrimerTurno(){	
	cout<<"***************** Turno 1 *****************"<<endl;
	cout<<"*******************************************"<<endl;
	
	//Cargamos las carretas a las pilas		
	for(int i=0;i<CarretasPila;i++){
		InsertarCarreta1(Pila1,NumeradorCarreta);
		NumeradorCarreta++;
		InsertarCarreta2(Pila2,NumeradorCarreta);
		NumeradorCarreta++;
	}
	
	//Cargar la cantidad de cajas
	int  NumeradorCaja = 1;
	for(int i=0;i<CajasNum;i++){
		InsertarCaja(CajasInicio, CajasFin,NumeradorCaja,1+rand()%(11-1),0,0,0,true);
		NumeradorCaja++;
	}
	
	//Cargar la cola de espera de carretas
	if(ClientesCarretas>0){
		for(int i=0;i<ClientesCarretas;i++){
			InsertarClienteCarreta(FrenteCarreta,FinCarreta,TotalCliente);
			cout<<"Cliente "<<TotalCliente<<" se coloco en la cola para esperar carreta."<<endl;
			TotalCliente++;
		}	
	}	
	ClienteSinCarreta = ClientesCarretas;
		
	//Cargar la lista de compras	
	for(int i=0;i<ClientesCompras;i++){
		int SelPila  = 1+rand()%(3-1);
		int NoCarreta;
		switch(SelPila){
			case 1:
				if(Pila1!=NULL){
					NoCarreta = EliminarCarreta1(Pila1);
					InsertarCompras(ComprasInicio, ComprasFin, TotalCliente, NoCarreta);
					cout<<"Cliente "<<TotalCliente<<" esta comprando con la carreta "<<NoCarreta<<"."<<endl;
					ClientesComprando++;						
				}else if(Pila2!=NULL){				
					NoCarreta = EliminarCarreta2(Pila2);
					InsertarCompras(ComprasInicio, ComprasFin, TotalCliente, NoCarreta);		
					cout<<"Cliente "<<TotalCliente<<" esta comprando con la carreta "<<NoCarreta<<"."<<endl;						
					ClientesComprando++;
				}else{
					cout<<"Carretas insuficientes, cliente "<<TotalCliente <<" enviado a esperar carreta."<<endl;
					InsertarClienteCarreta(FrenteCarreta,FinCarreta,TotalCliente);
				}				
				break;					
			case 2:
				if(Pila2!=NULL){
					NoCarreta = EliminarCarreta2(Pila2);
					InsertarCompras(ComprasInicio, ComprasFin, TotalCliente, NoCarreta);		
					cout<<"Cliente "<<TotalCliente<<" esta comprando con la carreta "<<NoCarreta<<"."<<endl;
					ClientesComprando++;						
				}else if(Pila1!=NULL){
					NoCarreta = EliminarCarreta1(Pila1);
					InsertarCompras(ComprasInicio, ComprasFin, TotalCliente, NoCarreta);
					cout<<"Cliente "<<TotalCliente<<" esta comprando con la carreta "<<NoCarreta<<"."<<endl;						
					ClientesComprando++;
				}else{
					cout<<"Carretas insuficientes, cliente "<<TotalCliente <<" enviado a esperar carreta."<<endl;
					InsertarClienteCarreta(FrenteCarreta,FinCarreta,TotalCliente);
				}				
				break;					
			default:
				cout<<"Pila "<<SelPila<<" no existe."<<endl;				
		}
		TotalCliente++;		
	}
	
	//Cargar la cola de pagos
	for(int i=0;i<ClientesPagos;i++){
		int SelPila  = 1+rand()%(3-1);
		int NoCarreta;
		//cout<<"Rnd: "<<SelPila<<endl;				
		switch(SelPila){
			case 1:
				if(Pila1!=NULL){
					NoCarreta = EliminarCarreta1(Pila1);
					InsertarPago(PagosInicio, PagosFin, TotalCliente, NoCarreta);
					cout<<"Cliente "<<TotalCliente<<" se coloco en la cola para pagar con carreta "<<NoCarreta<<"."<<endl;	
					ClientesdePagos++;					
				}else if(Pila2!=NULL){				
					NoCarreta = EliminarCarreta2(Pila2);
					InsertarPago(PagosInicio, PagosFin, TotalCliente, NoCarreta);		
					cout<<"Cliente "<<TotalCliente<<" se coloco en la cola para pagar con carreta "<<NoCarreta<<"."<<endl;	
					ClientesdePagos++;					
				}else{
					cout<<"Carretas insuficientes, cliente "<<TotalCliente <<" enviado a esperar carreta."<<endl;
					InsertarClienteCarreta(FrenteCarreta,FinCarreta,TotalCliente);
				}				
				break;					
			case 2:
				if(Pila2!=NULL){
					NoCarreta = EliminarCarreta2(Pila2);
					InsertarPago(PagosInicio, PagosFin, TotalCliente, NoCarreta);		
					cout<<"Cliente "<<TotalCliente<<" se coloco en la cola para pagar con carreta "<<NoCarreta<<"."<<endl;						
					ClientesdePagos++;
				}else if(Pila1!=NULL){
					NoCarreta = EliminarCarreta1(Pila1);
					InsertarPago(PagosInicio, PagosFin, TotalCliente, NoCarreta);
					cout<<"Cliente "<<TotalCliente<<" se coloco en la cola para pagar con carreta "<<NoCarreta<<"."<<endl;	
					ClientesdePagos++;					
				}else{
					cout<<"Carretas insuficientes, cliente "<<TotalCliente <<" enviado a esperar carreta."<<endl;
					InsertarClienteCarreta(FrenteCarreta,FinCarreta,TotalCliente);
				}				
				break;					
			default:
				cout<<"Pila "<<SelPila<<" no existe."<<endl;						
		//cout<<"Carretas disponibles: "<<TotalCarretas<<endl;		
		}
		TotalCliente++;			
	}	
	//TerminarTurno
	turnos++;
	MenuTurnos();
}

//Metodo para todos los turnos
void Turnos(){
	cout<<"***************** Turno "<< turnos <<" *****************"<<endl;	
	cout<<"*******************************************"<<endl;	
	
	//Verificar la cola de espera de carretas
	if(FrenteCarreta!=NULL){
		for(int i=0; i<ClienteSinCarreta; i++){			
			//Random para seleccionar pila para extraer carreta
			int SelPila  = 1+rand()%(3-1);				
			int NoCarreta;
			int NoClienteE;
			//Meter los valores de un vergazo
			switch(SelPila){
				case 1:
					if(Pila1!=NULL){
						NoCarreta = EliminarCarreta1(Pila1);
						NoClienteE = EliminarClienteCarreta(FrenteCarreta, FinCarreta);				
						InsertarCompras(ComprasInicio, ComprasFin, NoClienteE, NoCarreta);
						cout<<"Cliente "<<NoClienteE<<" esta comprando con la carreta "<<NoCarreta<<"."<<endl;						
						ClientesComprando++;
					}else if(Pila2!=NULL){				
						NoCarreta = EliminarCarreta2(Pila2);
						NoClienteE = EliminarClienteCarreta(FrenteCarreta, FinCarreta);				
						InsertarCompras(ComprasInicio, ComprasFin, NoClienteE, NoCarreta);		
						cout<<"Cliente "<<NoClienteE<<" esta comprando con la carreta "<<NoCarreta<<"."<<endl;
						ClientesComprando++;						
					}				
					break;					
				case 2:
					if(Pila2!=NULL){
						NoCarreta = EliminarCarreta2(Pila2);
						NoClienteE = EliminarClienteCarreta(FrenteCarreta, FinCarreta);				
						InsertarCompras(ComprasInicio, ComprasFin, NoClienteE, NoCarreta);		
						cout<<"Cliente "<<NoClienteE<<" esta comprando con la carreta "<<NoCarreta<<"."<<endl;	
						ClientesComprando++;					
					}else if(Pila1!=NULL){
						NoCarreta = EliminarCarreta1(Pila1);
						NoClienteE = EliminarClienteCarreta(FrenteCarreta, FinCarreta);				
						InsertarCompras(ComprasInicio, ComprasFin, NoClienteE, NoCarreta);
						cout<<"Cliente "<<NoClienteE<<" esta comprando con la carreta "<<NoCarreta<<"."<<endl;
						ClientesComprando++;						
					}				
					break;					
				default:
					cout<<"Pila "<<SelPila<<" no existe."<<endl;						
			}												
			
		}
		ClienteSinCarreta=0;
	}
		
	//Agregar clientes nuevos a la cola de espera o directamente a la lista de compras
	for(int i=0; i<ClientesNews; i++){		
						
			//Random para meter en compras
			int SelPila  = 1+rand()%(3-1);
			int NoCarreta;
			//Meter los valores de un vergazo
			switch(SelPila){
			case 1:
				if(Pila1!=NULL){
					NoCarreta = EliminarCarreta1(Pila1);
					InsertarCompras(ComprasInicio, ComprasFin, TotalCliente, NoCarreta);
					cout<<"Cliente "<<TotalCliente<<" esta comprando con la carreta "<<NoCarreta<<"."<<endl;
					ClientesComprando++;						
				}else if(Pila2!=NULL){				
					NoCarreta = EliminarCarreta2(Pila2);
					InsertarCompras(ComprasInicio, ComprasFin, TotalCliente, NoCarreta);		
					cout<<"Cliente "<<TotalCliente<<" esta comprando con la carreta "<<NoCarreta<<"."<<endl;	
					ClientesComprando++;					
				}else{
					cout<<"Carretas insuficientes, cliente "<<TotalCliente <<" enviado a esperar carreta."<<endl;
					InsertarClienteCarreta(FrenteCarreta,FinCarreta,TotalCliente);
				}				
				break;					
			case 2:
				if(Pila2!=NULL){
					NoCarreta = EliminarCarreta2(Pila2);
					InsertarCompras(ComprasInicio, ComprasFin, TotalCliente, NoCarreta);		
					cout<<"Cliente "<<TotalCliente<<" esta comprando con la carreta "<<NoCarreta<<"."<<endl;
					ClientesComprando++;						
				}else if(Pila1!=NULL){
					NoCarreta = EliminarCarreta1(Pila1);
					InsertarCompras(ComprasInicio, ComprasFin, TotalCliente, NoCarreta);
					cout<<"Cliente "<<TotalCliente<<" esta comprando con la carreta "<<NoCarreta<<"."<<endl;
					ClientesComprando++;						
				}else{
					cout<<"Carretas insuficientes, cliente "<<TotalCliente <<" enviado a esperar carreta."<<endl;
					InsertarClienteCarreta(FrenteCarreta,FinCarreta,TotalCliente);
				}				
				break;					
			default:
				cout<<"Pila "<<SelPila<<" no existe."<<endl;				
		}				
		
		TotalCliente++;		
	}

	//Extrear objeto de compras
	int SelComprador = rand()%101;	
	//int SelComprador = 0;
	//int SelComprador = 3;
	int Comparar = ClientesComprando-1;
	cout<<"Posicion: "<<SelComprador<<" puede avanzar"<<endl;
	//cout<<"Clientes comprando: "<<ClientesComprando<<endl;
	if(SelComprador <= Comparar){
		if(SelComprador == 0){
			EliminarInicioCompra(ComprasInicio,ComprasFin, CarretaExtraer, ClienteExtraer);
		}else if(SelComprador == Comparar){			
			EliminarUltimaCompra(ComprasInicio,ComprasFin, CarretaExtraer, ClienteExtraer);
		}else{					
			EliminarCompra(ComprasInicio, ComprasFin, SelComprador, CarretaExtraer, ClienteExtraer);
		}		
		if(PagosInicio!=NULL){
			InsertarPago(PagosInicio, PagosFin, ClienteExtraer, CarretaExtraer);	
			cout<<"Cliente "<<ClienteExtraer<<" se formo en la cola para pagar con carreta "<<CarretaExtraer<<"."<<endl;
			ClientesdePagos++;
		}else  if(VerificarEstado){
			ModificarCaja(CajasInicio, ClienteExtraer, CarretaExtraer, CajaUsada);
			cout<<"Cliente "<<ClienteExtraer<<" paso a la caja "<<CajaUsada<<" con la carreta "<<CarretaExtraer<<"."<<endl;
		}else{
			InsertarPago(PagosInicio, PagosFin, ClienteExtraer, CarretaExtraer);	
			cout<<"Cliente "<<ClienteExtraer<<" se formo en la cola para pagar con carreta "<<CarretaExtraer<<"."<<endl;
			ClientesdePagos++;
		}
		ClientesComprando--;
	}else{
		cout<<"Hay menos de "<<SelComprador<<" clientes."<<endl;
	}	
	
	//Limpiar cola de pagos
	for(int i=0; i<ClientesPagos;i++){
		if(VerificarEstado(CajasInicio)){
			EliminarPago(PagosInicio, PagosFin, ClienteCaja, CarretaCaja);				
			ModificarCaja(CajasInicio, ClienteCaja, CarretaCaja, CajaUsada);
			cout<<"Cliente "<<ClienteCaja<<" paso a la caja "<<CajaUsada<<" con la carreta "<<CarretaCaja<<"."<<endl;
		}					
	}
	if(PagosInicio!=NULL){
		//Nada
	}else{
		ClientesPagos=0;	
	}		
	
	//Limpiar cajas
	//EvaluarTurno(CajasInicio);
	CarretasLibres = EvaluarTurno(CajasInicio);
	for(int i=0; i<CarretasLibres; i++){
		NumeradorCarreta++;
		int Random = 1+rand()%(3-1);
		if(Random==1){
			cout<<"Carreta "<<NumeradorCarreta<<" se coloco en la pila 1."<<endl;
			InsertarCarreta1(Pila1,NumeradorCarreta);
		}else{
			cout<<"Carreta "<<NumeradorCarreta<<" se coloco en la pila 2."<<endl;
			InsertarCarreta2(Pila2,NumeradorCarreta);
		}
	}

	
	turnos++;
	MenuTurnos();
}

//Metodo para iniciar la simulacion
void IniciarSimulacion(){
	if(CarretasPila!=0 && CajasNum!=0){
		PrimerTurno();
	}else{
		ConfiguracionInicial();
	}
}

//Metodo para configurar las variables
void ConfiguracionInicial(){	
	cout<<"************* Configuracion ***************"<<endl;
	cout<<"*******************************************"<<endl;
	cout<<"Cantidad de carretas por pila: ";
	cin>>CarretasPila;		
	cout<<"Cantidad de cajas: ";
	cin>>CajasNum;
	cout<<"Cantidad de clientes en espera de carretas: ";
	cin>>ClientesCarretas;
	cout<<"Cantidad de clientes comprando: ";
	cin>>ClientesCompras;
	cout<<"Cantidad de clientes en cola de pagos: ";
	cin>>ClientesPagos;
	cout<<"*******************************************"<<endl;
	MenuInicial();	
}

//Metodo para el menu inicial de la aplicacion
void MenuInicial(){
	int Opcion;	
	//Menu Grafico	
	cout<<"********* Sistema de Supermercado *********"<<endl;
	cout<<"*******************************************"<<endl;
	cout<<"1. Iniciar Simulacion"<<endl;
	cout<<"2. Configuracion Inicial"<<endl;
	cout<<"3. Salir"<<endl;
	cout<<"*******************************************"<<endl;
	cout<<"Opcion a seleccionar: ";	
	cin>>Opcion;			
	cout<<"*******************************************"<<endl;
	//Casos para realizar el menu
	switch(Opcion){
		case 1:
			IniciarSimulacion();
			break;
		case 2:
			ConfiguracionInicial();
			break;
		case 3:
			exit(0);
			break;
		default:			
			cout<<"****** Opcion seleccionada no existe ******"<<endl;
			cout<<"*******************************************"<<endl;
			MenuInicial();
	}
}

int main(){			
	//Inicializar los randoms
	srand(time(NULL));
	
	//Llamar al MenuInicial
	MenuInicial();				
	
	return 0;	
}
