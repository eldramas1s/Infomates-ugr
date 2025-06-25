#include "../Comportamientos_Jugador/auxiliar.hpp"
#include <iostream>
#include "motorlib/util.h"


Action ComportamientoAuxiliar::think(Sensores sensores)
{
	Action accion = IDLE;

	switch (sensores.nivel)
	{
	case 0:
		accion = ComportamientoAuxiliarNivel_0 (sensores);
		break;
	case 1:
		accion = ComportamientoAuxiliarNivel_1 (sensores);
		break;
	case 2:
		accion = ComportamientoAuxiliarNivel_2 (sensores);
		break;
	case 3:
		accion = ComportamientoAuxiliarNivel_3 (sensores);
		//accion= ComportamientoAuxiliarNivel_E (sensores);
		break;
	case 4:
		accion = ComportamientoAuxiliarNivel_4 (sensores);
		break;
	}

	return accion;
}

int ComportamientoAuxiliar::interact(Action accion, int valor)
{
	return 0;
}

Action ComportamientoAuxiliar::ComportamientoAuxiliarNivel_0(Sensores sensores)
{
	SituarSensorEnMapa(mapaResultado,mapaCotas,sensores);

	Action action;

	frecuencias[sensores.posF][sensores.posC]++; //Actualizo la matriz de frecuencias

	if(sensores.superficie[0]=='D') zap=true;
	if(sensores.superficie[0]=='X')
		action=IDLE;
	
	else if(giro45izq!=0){
		action = TURN_SR;
		giro45izq--;
	}
	else if(giro180!=0){
		action=TURN_SR;
		giro180--;
	}
	else if(sensores.choque){
		action=TURN_SR;
		giro180=3;
	}
	else if(HayRescatador(sensores.agentes)){
		action = TURN_SR;
		giro180 = 3;
	}
	else{
		//Elegimos la casilla a la que ir
		int pos=Andar(sensores);
		if(pos == 2){
			action = WALK;
		}
		else if(pos == 0)
			action = TURN_SR;
		else {
			action = TURN_SR;
			if(pos == 1){
				giro45izq = 6;
			}
		}

	}
	return action;
}

Action ComportamientoAuxiliar::ComportamientoAuxiliarNivel_1(Sensores sensores)
{
	SituarSensorEnMapa(mapaResultado,mapaCotas,sensores);

	Action action;
	
	ActualizarFrecs(sensores.posF,sensores.posC,sensores.rumbo);	// Actualizamos las frecuencias

	if(sensores.superficie[0]=='D') zap=true;
	if(sensores.superficie[0]=='X' and sensores.nivel==1)
		action=IDLE;
	
	else if(giro45izq!=0){
		action = TURN_SR;
		giro45izq--;
	}
	else if(giro180!=0){
		action=TURN_SR;
		giro180--;
	}
	else if(sensores.choque){
		action=TURN_SR;
		giro180=3;
	}
	else{

		//Elegimos la casilla a la que ir
		int pos=Andar(sensores);
		if(pos == 2){
			action = WALK;
		}
		else if(pos == 0)
			action = TURN_SR;
		else {
			action = TURN_SR;
			if(pos == 1){
				giro45izq = 6;
			}
		}

	}
	return action;
}

Action ComportamientoAuxiliar::ComportamientoAuxiliarNivel_2(Sensores sensores)
{
	return IDLE;
}

Action ComportamientoAuxiliar::ComportamientoAuxiliarNivel_3(Sensores sensores)
{
	Action action = IDLE;

	if(!hayPlan){
		EstadoA inicio, fin;
		inicio.f=sensores.posF;
		inicio.c=sensores.posC;
		inicio.brujula=sensores.rumbo;
		inicio.zapas=zap;

		fin.f=sensores.destinoF;
		fin.c=sensores.destinoC;


		//Obtenemos un plan
		plan = A_star(inicio,fin,mapaResultado,mapaCotas);

		VisualizaPlan(inicio,plan);
		
		hayPlan=plan.size()!=0;
	}
	if(hayPlan and plan.size()>0){
		action = plan.front();
		plan.pop_front();
	}
	if(plan.size()==0)
		hayPlan=false;

	return action;
}

Action ComportamientoAuxiliar::ComportamientoAuxiliarNivel_4(Sensores sensores)
{
	
	Action action = IDLE;

	if(sensores.superficie[0]=='D') zap=true;


	//Flags del nivel 4
	static bool react_flag=false,wait_flag=false,low_energy=false,charging = false;;

	//Estructura de almacenaje de casillas base y mapa auxiliar
	static set<pair<int,int>> bases; 

	static EstadoA inicio,fin;
	static int porcentaje=0;
	
	/*La bandera de comportamiento reactivo esta activa*/
	if(react_flag){
		action=ComportamientoAuxiliarNivel_0(sensores);
		if(!HayAgente(sensores.agentes,false))			//La bandera es falsa porque trabajo en reactivo
			react_flag=false;
		return action;
	}

	/*La bandera de esperar recargando esta activa*/
	if(wait_flag){
		if(sensores.venpaca)
			wait_flag=false;
		return IDLE;
	}
	else if(charging){	// Si estoy cargando paro la carga
		action = IDLE;
		if(sensores.choque or sensores.venpaca)
			charging = false;
	}
	else{
		action = ComportamientoAuxiliarNivel_1(sensores);
	}
	/* En un principio, todas las banderas estan desactivadas*/
	if(!hayPlan){
		inicio.f=sensores.posF;
		inicio.c=sensores.posC;
		inicio.brujula=sensores.rumbo;
		inicio.zapas=zap;

		fin.f=sensores.destinoF;
		fin.c=sensores.destinoC;

		if(sensores.venpaca){
			plan = A_star(inicio,fin,mapaResultado,mapaCotas);
		}
		else{
			if(bases.size()!=0 and sensores.superficie[0]!='X'){
				plan = Dijkstra_mod(inicio,bases,mapaResultado,mapaCotas);
			}
			else{
				if(sensores.superficie[0]!='X'){
					action = ComportamientoAuxiliarNivel_1(sensores);
					GetBasesA(bases,sensores.posF,sensores.posC,mapaResultado);
				}
				else{
					return IDLE;
				}
			}
		}
		
		VisualizaPlan(inicio,plan);
		
		hayPlan=plan.size()>0;
	}
	if(hayPlan and plan.size()>0){
		
		SituarSensorEnMapa(mapaResultado,mapaCotas,sensores);

		
		if(porcentaje<0.8){
			porcentaje=porcentajeA(mapaResultado);
			GetBasesA(bases,sensores.posF,sensores.posC,mapaResultado);
		}

		if(VeoDestino(sensores.posF,sensores.posC,sensores.rumbo,sensores.destinoF,sensores.destinoC) and sensores.venpaca){
			return IDLE;
		}

		action = plan.front();
		plan.pop_front();

		int cause = FallaPlan(sensores,action,mapaResultado,mapaCotas,low_energy,1000);

		if(cause != 0 or sensores.choque){
			plan.clear();
			hayPlan=false;
			action=IDLE;
			if(cause==2){
				react_flag=true;
				action=ComportamientoAuxiliarNivel_0(sensores);
			}
			if(cause==3){	
				low_energy=true;
			}
			
		}
	}
	else if(hayPlan and plan.size()==0){ 
		if(low_energy){
			action=IDLE;
			wait_flag=true;
		}
		else{
			hayPlan=false;
		}		
	}

	return action;
}

Action ComportamientoAuxiliar::ComportamientoAuxiliarNivel_E(Sensores sensores)
{
	Action action=IDLE;
	if(!hayPlan){
		EstadoA inicio, fin;
		inicio.f = sensores.posF;
		inicio.c = sensores.posC;
		inicio.brujula = sensores.rumbo;
		inicio.zapas = zap;
		fin.f = sensores.destinoF;
		fin.c = sensores.destinoC;
		//plan = AnchuraAuxiliar(inicio, fin, mapaResultado, mapaCotas);
		VisualizaPlan(inicio,plan);
		hayPlan = plan.size() != 0 ;
	}
	if(hayPlan and plan.size()>0){
		action=plan.front();
		//plan.pop_front();
	}
	if(plan.size()==0){
		hayPlan=false;
	}
	return action;
}

/****************************************************************************************** */
// NIVELES 0 y 1
/****************************************************************************************** */

/***************************************/
//Funciones importantes
/***************************************/

int ComportamientoAuxiliar::GetPos(int fila,int col, Orientacion rumbo){
	int pos=0;
	int k=1;
	switch (rumbo)
	{
		case sur:
			k=-1;
		case norte:
			if(fila==0) pos=0;
			else if(fila==-k){
				if(col==-k) pos=1;
				else if(col==0) pos=2;
				else if(col==k) pos=3;
			}
			else if(fila==-2*k){
				if(col==-2*k) pos=4;
				else if(col==-k) pos=5;
				else if(col==0) pos=6;
				else if(col==k) pos=7;
				else if(col==2*k) pos=8;
			}
			else if(fila==-3*k){
				if(col==-3*k) pos=9;
				else if(col==-2*k) pos=10;
				else if(col==-k) pos=11;
				else if(col==0) pos=12;
				else if(col==k) pos=13;
				else if(col==2*k) pos=14;
				else if(col==3*k) pos=15;
			}
		break;
		case oeste:
			k=-1;
		case este:
			if(col==0) pos=0;
			else if(col==k){
				if(fila==-k) pos=1;
				else if(fila==0) pos=2;
				else if(fila==k) pos=3;
			}
			else if(col==2*k){
				if(fila==-2*k) pos=4;
				else if(fila==-k) pos=5;
				else if(fila==0) pos=6;
				else if(fila==k) pos=7;
				else if(fila==2*k) pos=8;
			}
			else if(col==3*k){
				if(fila==-3*k) pos=9;
				else if(fila==-2*k) pos=10;
				else if(fila==-k) pos=11;
				else if(fila==0) pos=12;
				else if(fila==k) pos=13;
				else if(fila==2*k) pos=14;
				else if(fila==3*k) pos=15;
			}
		break;
		case suroeste:
			k=-1;
		case noreste:
			if(fila==0){
				if(col==k) pos=3;
				else if(col==2*k) pos=8;
				else if(col==3*k) pos=15;
			}
			else if(fila==-k){
				if(col==0) pos=1;
				else if(col==k) pos=2;
				else if(col==2*k) pos=7;
				else if(col==3*k) pos=14;
			}
			else if(fila==-2*k){
				if(col==0) pos=4;
				else if(col==k) pos=5;
				else if(col==2*k) pos=6;
				else if(col==3*k) pos=13;
			}
			else if(fila==-3*k){
				if(col==0) pos=9;
				else if(col==k) pos=10;
				else if(col==2*k) pos=11;
				else if(col==3*k) pos=12;
			}
			 
		break;
		case noroeste:
			k=-1;
		case sureste:
			if(fila==0){
				if(col==k) pos=1;
				else if(col==2*k) pos=4;
				else if(col==3*k) pos=9;
			}
			else if(fila==k){
				if(col==0) pos=3;
				else if(col==k) pos=2;
				else if(col==2*k) pos=5;
				else if(col==3*k) pos=10;
			}
			else if(fila==2*k){
				if(col==0) pos=8;
				else if(col==k) pos=7;
				else if(col==2*k) pos=6;
				else if(col==3*k) pos=11;
			}
			else if(fila==3*k){
				if(col==0) pos=15;
				else if(col==k) pos=14;
				else if(col==2*k) pos=13;
				else if(col==3*k) pos=12;
			}
		break;
		default:
			pos=-1;
		break;
	}
	return pos;
}

void ComportamientoAuxiliar::GetPaths(int f, int c, const Sensores & sensores, vector<pair<int,int>> & camino){
	
	int k=1;
	static vector<unsigned char> v;


	switch(sensores.nivel){
		case 0:
			v={'C','X','D'};
		break;
		case 1:
			v={'C','S','D'};
		break;
		case 4:
			v={'C','S','T','X'};
			if(sensores.superficie[0]=='C' or sensores.superficie[0]=='S'){
				v.clear();
				v={'C','S','D'};
			}
		break;
	}

	

	switch (sensores.rumbo){
		case sur:
			k=-1;
		case norte:
		
			if(CasillaDeseada(sensores,2,v)) camino.push_back(make_pair(-k,0));
			if(CasillaDeseada(sensores,1,v)) camino.push_back(make_pair(-k,-k));
			if(CasillaDeseada(sensores,3,v)) camino.push_back(make_pair(-k,k));

		break;	
		case oeste:
			k=-1;
		case este:
			if(CasillaDeseada(sensores,2,v)) camino.push_back(make_pair(0,k));
			if(CasillaDeseada(sensores,1,v)) camino.push_back(make_pair(-k,k));
			if(CasillaDeseada(sensores,3,v)) camino.push_back(make_pair(k,k));

		break;
		case suroeste:
			k=-1;
		case noreste:
			if(CasillaDeseada(sensores,2,v)) camino.push_back(make_pair(-k,k));
			if(CasillaDeseada(sensores,1,v)) camino.push_back(make_pair(-k,0));
			if(CasillaDeseada(sensores,3,v)) camino.push_back(make_pair(0,k));

		break;
		case noroeste:
			k=-1;
		case sureste:
			if(CasillaDeseada(sensores,2,v)) camino.push_back(make_pair(k,k));
			if(CasillaDeseada(sensores,1,v)) camino.push_back(make_pair(0,k));
			if(CasillaDeseada(sensores,3,v)) camino.push_back(make_pair(k,0));

		break;
	}

}

int ComportamientoAuxiliar::LessFreq(const Sensores & sensores){
	vector<pair<int,int>> casillas_camino;
	casillas_camino.clear();
	int f=sensores.posF;
	int c=sensores.posC;
	
	GetPaths(f,c,sensores,casillas_camino);	//Tengo los pares que son casillas deseadas y viables por alrtura.

	pair <int,int> pos=make_pair(0,0);
	int min_frec=frecuencias[f][c];

	if(casillas_camino.size()==0){
		return 0;
	}

	casillas_camino.push_back(make_pair(0,0)); 

	int x,y;
	for(auto it=casillas_camino.begin(); it!=casillas_camino.end(); it++){
		x=it->first;
		y=it->second;
		if(frecuencias[f+x][c+y]<min_frec){
			min_frec=frecuencias[f+x][c+y];
			pos=*it;
		}
	}

	return GetPos(pos.first,pos.second,sensores.rumbo);
}

int ComportamientoAuxiliar::Andar(const Sensores & sensores){

	if(!(*this).zap){
		if(sensores.superficie[1]=='D' and ViablePorAlturaA(sensores.cota[1]-sensores.cota[0])) return 1;
		else if (sensores.superficie[2]=='D' and ViablePorAlturaA(sensores.cota[2]-sensores.cota[0])) return 2;
		else if (sensores.superficie[3]=='D' and ViablePorAlturaA(sensores.cota[3]-sensores.cota[0])) return 3;
	}

	int pos=LessFreq(sensores);
	return pos;
}

void ComportamientoAuxiliar::SituarSensorEnMapa(vector<vector<unsigned char>> &m, vector<vector<unsigned char>> &a, Sensores sensores)
{
	int fila=sensores.posF;
	int col=sensores.posC;
	m[fila][col]=sensores.superficie[0];
	a[fila][col]=sensores.cota[0];

	int param=-1;
	int counter=1;

	switch (sensores.rumbo)
	{
		case sur:
			param = 1;
		case norte:
			for(int i=1;i<=3;i++){
				for(int j=-i; j<=i; j++){
					m[fila+param*i][col-param*j]=sensores.superficie[counter];
					a[fila+param*i][col-param*j]=sensores.cota[counter];
					counter++;
				}
			}
		break;
		case oeste:
			param=1;
		case este:
			
			for(int i=1;i<=3;i++){
				for(int j=-i; j<=i; j++){
					m[fila-param*j][col-param*i]=sensores.superficie[counter];
					a[fila-param*j][col-param*i]=sensores.cota[counter];
					counter++;
				}
			}
		break;
		case suroeste:
			param=1;
		case noreste:
			m[fila+param][col]=sensores.superficie[1];
			m[fila+2*param][col]=sensores.superficie[4];
			m[fila+3*param][col]=sensores.superficie[9];
			m[fila][col-param]=sensores.superficie[3];
			m[fila+param][col-param]=sensores.superficie[2];
			m[fila+2*param][col-param]=sensores.superficie[5];
			m[fila+3*param][col-param]=sensores.superficie[10];
			m[fila][col-2*param]=sensores.superficie[8];
			m[fila+param][col-2*param]=sensores.superficie[7];
			m[fila+2*param][col-2*param]=sensores.superficie[6];
			m[fila+3*param][col-2*param]=sensores.superficie[11];
			m[fila][col-3*param]=sensores.superficie[15];
			m[fila+param][col-3*param]=sensores.superficie[14];
			m[fila+2*param][col-3*param]=sensores.superficie[13];
			m[fila+3*param][col-3*param]=sensores.superficie[12];

			a[fila+param][col]=sensores.cota[1];
			a[fila+2*param][col]=sensores.cota[4];
			a[fila+3*param][col]=sensores.cota[9];
			a[fila][col-param]=sensores.cota[3];
			a[fila+param][col-param]=sensores.cota[2];
			a[fila+2*param][col-param]=sensores.cota[5];
			a[fila+3*param][col-param]=sensores.cota[10];
			a[fila][col-2*param]=sensores.cota[8];
			a[fila+param][col-2*param]=sensores.cota[7];
			a[fila+2*param][col-2*param]=sensores.cota[6];
			a[fila+3*param][col-2*param]=sensores.cota[11];
			a[fila][col-3*param]=sensores.cota[15];
			a[fila+param][col-3*param]=sensores.cota[14];
			a[fila+2*param][col-3*param]=sensores.cota[13];
			a[fila+3*param][col-3*param]=sensores.cota[12];
			
		break;
		case noroeste:
			param=1;
		case sureste:
			m[fila][col-param]=sensores.superficie[1];
			m[fila][col-2*param]=sensores.superficie[4];
			m[fila][col-3*param]=sensores.superficie[9];
			m[fila-param][col]=sensores.superficie[3];
			m[fila-param][col-param]=sensores.superficie[2];
			m[fila-param][col-2*param]=sensores.superficie[5];
			m[fila-param][col-3*param]=sensores.superficie[10];
			m[fila-2*param][col]=sensores.superficie[8];
			m[fila-2*param][col-param]=sensores.superficie[7];
			m[fila-2*param][col-2*param]=sensores.superficie[6];
			m[fila-2*param][col-3*param]=sensores.superficie[11];
			m[fila-3*param][col]=sensores.superficie[15];
			m[fila-3*param][col-param]=sensores.superficie[14];
			m[fila-3*param][col-2*param]=sensores.superficie[13];
			m[fila-3*param][col-3*param]=sensores.superficie[12];

			a[fila][col-param]=sensores.cota[1];
			a[fila][col-2*param]=sensores.cota[4];
			a[fila][col-3*param]=sensores.cota[9];
			a[fila-param][col]=sensores.cota[3];	
			a[fila-param][col-param]=sensores.cota[2];
			a[fila-param][col-2*param]=sensores.cota[5];
			a[fila-param][col-3*param]=sensores.cota[10];
			a[fila-2*param][col]=sensores.cota[8];
			a[fila-2*param][col-param]=sensores.cota[7];
			a[fila-2*param][col-2*param]=sensores.cota[6];
			a[fila-2*param][col-3*param]=sensores.cota[11];
			a[fila-3*param][col]=sensores.cota[15];
			a[fila-3*param][col-param]=sensores.cota[14];
			a[fila-3*param][col-2*param]=sensores.cota[13];
			a[fila-3*param][col-3*param]=sensores.cota[12];
		break;
	}
	
}

/***************************************/
//Funciones auxiliares
/***************************************/

void ComportamientoAuxiliar::ActualizarFrecs(int f, int c, Orientacion rumbo){

	int k=1;
	switch (rumbo)
	{
		case sur:
			k=-1;
		case norte:
			for(int i=0; i<=3; i++){
				for(int j=-i; j<=i; j++){
					frecuencias[f-k*i][c+j]+=selector(mapaResultado[f-k*i][c+j]);
				}
			}
		break;
		case oeste:
			k=-1;
		case este:
			for(int i=0; i<=3; i++){
				for(int j=-i; j<=k; j++){
					frecuencias[f+j][c+k*i]+=selector(mapaResultado[f+j][c+k*i]);
				}
			}
		break;
		case suroeste:
			k=-1;
		case noreste:
			for(int i=0; i<=3; i++){
				for(int j=0; j<=3;j++){
					frecuencias[f-k*i][c+k*j]+=selector(mapaResultado[f-k*i][c+k*j]);
				}
			}
		break;
		case noroeste:
			k=-1;
		case sureste:
			for(int i=0; i<=3; i++){
				for(int j=0; j<=3;j++){
					frecuencias[f+k*i][c+k*j]+=selector(mapaResultado[f+k*i][c+k*j]);
				}
			}
		break;
	}
}

int ComportamientoAuxiliar::selector(char casilla){
	int val;

	switch(casilla){
		case 'C':
		case 'S':
		case 'X':
			val=2; 
		break;
		case 'T':
		case 'B':
			val=3;
		break;
		case 'D':
			if(!zap)
				val=0;
			else
				val=5;
		break;
		case 'M':
			val=6;
		break;
		case 'P':
			val=6;
		break;
		case 'A':
			val=4;
		break;
		default:
			val=0;
		break;
	}

	return val;
}

bool ComportamientoAuxiliar::ViablePorAlturaA(int dif)
{
	return abs(dif)<=1;
}

bool ComportamientoAuxiliar::CasillaDeseada(const Sensores &sensores, int casilla, const vector<unsigned char> & deseadas)
{
	if(IsIn(deseadas,sensores.superficie[casilla]) and ViablePorAlturaA(sensores.cota[casilla]-sensores.cota[0]))
		return true;
	else
		return false;
}

bool ComportamientoAuxiliar::HayRescatador(const vector<unsigned char> & ags){
	return ags[2]=='r' or ags[6]=='r' or ags[12]=='r';
}

/****************************************************************************************** */
// NIVEL 3
/****************************************************************************************** */
int ComportamientoAuxiliar::whatCost(int my_f, int my_c, int new_f, int new_c, Action accion, const vector<vector<unsigned char>> &terreno, const vector<vector<unsigned char>> &altura){
	int cost=0;
	int my_height=altura[my_f][my_c];
	int new_height=altura[new_f][new_c];
	int dif=my_height-new_height;

	int sign=(dif>0)?-1:1;

	if(dif==0) sign=0;

	switch(accion){
		case WALK:
			switch (terreno[my_f][my_c]){
				case 'A':
					cost=100+sign*10;
				break;
				case 'T':
					cost=20+sign*5;
				break;
				case 'S':
					cost=2+sign;
				break;
				default:
					cost = 1;
				break;
			}
		break;
		case TURN_SR:
			switch(terreno[my_f][my_c]){
				case 'A':
					cost=16;
				break;
				case 'T':
					cost=3;
				break;
				default:
					cost=1;
				break;
			}
		break;
		default:
			cost=0;
		break;
	}
	return cost;
}


list<Action> ComportamientoAuxiliar::A_star(const EstadoA &inicio, const EstadoA &final, const vector<vector<unsigned char>> &terreno, const vector<vector<unsigned char>> &altura){
	NodoA current_node;
	set<NodoA> explored;											// Lista de cerrados
	priority_queue<NodoA,vector<NodoA>,ComparadorA> frontier;		// Lista de abiertos

	list<Action> path;

	current_node.estado=inicio;
	current_node.coste=0;
	current_node.heuristica=Heuristica(current_node.estado.f,current_node.estado.c,final.f,final.c);

	frontier.push(current_node);
	bool SolutionFound=(current_node.estado.f==final.f and current_node.estado.c==final.c);

	while(!SolutionFound and !frontier.empty()){
		current_node=frontier.top();
		frontier.pop();

		if(terreno[current_node.estado.f][current_node.estado.c]=='D'){
			current_node.estado.zapas=true;
		}

		if(explored.count(current_node)==0){
			explored.insert(current_node);
			
			NodoA child_WALK=current_node;
			child_WALK.estado=applyA(WALK,current_node.estado,terreno,altura);
			child_WALK.coste=current_node.coste+whatCost(current_node.estado.f,current_node.estado.c,child_WALK.estado.f,child_WALK.estado.c,WALK, terreno, altura);
			child_WALK.secuencia.push_back(WALK);
			child_WALK.heuristica=Heuristica(child_WALK.estado.f,child_WALK.estado.c,final.f,final.c);

			if(explored.count(child_WALK)==0){
				frontier.push(child_WALK);
			}

			NodoA child_TURN_SR=current_node;
			child_TURN_SR.estado=applyA(TURN_SR,current_node.estado,terreno,altura);
			child_TURN_SR.coste=current_node.coste+whatCost(current_node.estado.f,current_node.estado.c,child_TURN_SR.estado.f,child_TURN_SR.estado.c,TURN_SR, terreno, altura);
			child_TURN_SR.secuencia.push_back(TURN_SR);
			child_TURN_SR.heuristica=Heuristica(child_TURN_SR.estado.f,child_TURN_SR.estado.c,final.f,final.c);

			if(explored.count(child_TURN_SR)==0){
				frontier.push(child_TURN_SR);
			}
		}
	
		SolutionFound=(current_node.estado.f==final.f and current_node.estado.c==final.c);
	}

	if(SolutionFound){
		for (int i=0; i<current_node.secuencia.size();i++){
			path.push_back(current_node.secuencia[i]);
		}
	}
	
	return path;
}

EstadoA ComportamientoAuxiliar::applyA(Action accion, const EstadoA & st, const vector<vector<unsigned char>> &terreno, const vector<vector<unsigned char>> &altura){

	EstadoA next = st;
	switch(accion){
		case WALK:
		if (CasillaAccesibleAuxiliar(st,terreno,altura)){
			next = NextCasillaAuxiliar(st);
		}
		break;
		case TURN_SR:
		next.brujula = (next.brujula+1)%8;
		break;
	}
	return next;
}

bool ComportamientoAuxiliar::CasillaAccesibleAuxiliar(const EstadoA &st, const vector<vector<unsigned char>> &terreno, const vector<vector<unsigned char>> &altura){
    
    EstadoA next = NextCasillaAuxiliar(st);

    bool check1 = false, check2 = false, check3 = false;
    
	if(next.f>=3 and next.c>=3 and next.f<=terreno.size()-3 and next.c<=terreno.size()-3){		//Esta condición depende de que el mapa sea cuadrado
		check1 = terreno[next.f][next.c] != 'P' and terreno[next.f][next.c] != 'M';
		check2 = terreno[next.f][next.c] != 'B' or (terreno[next.f][next.c] == 'B' and
		st.zapas);
		check3 = abs(altura[next.f][next.c] - altura[st.f][st.c]) <= 1;
		
		if(terreno[next.f][next.c]=='?') return true;

		return check1 and check2 and check3;
	}
	else{
		return false;
	}
}

EstadoA ComportamientoAuxiliar::NextCasillaAuxiliar(const EstadoA &st){
    EstadoA siguiente = st;
    switch (st.brujula)
    {
      case norte:
        siguiente.f = st.f - 1;
      break;
      case noreste:
        siguiente.f = st.f - 1;
        siguiente.c = st.c + 1;
      break;
      case este:
        siguiente.c = st.c + 1;
      break;
      case sureste:
        siguiente.f = st.f + 1;
        siguiente.c = st.c + 1;
      break;
      case sur:
        siguiente.f = st.f + 1;
      break;
      case suroeste:
        siguiente.f = st.f + 1;
        siguiente.c = st.c - 1;
      break;
      case oeste:
        siguiente.c = st.c - 1;
      break;
      case noroeste:
        siguiente.f = st.f - 1;
        siguiente.c = st.c - 1;
      break;
      }
    return siguiente;
}

/****************************************************************************************** */
// NIVEL ESPECIAL
/****************************************************************************************** */

list<Action> ComportamientoAuxiliar::AnchuraAuxiliar(const EstadoA &inicio, const EstadoA &final, const vector<vector<unsigned char>> &terreno, const vector<vector<unsigned char>> &altura){
	
	NodoA current_node;
	list<NodoA> frontier;
	list<NodoA> explored;
	list<Action> path;

	current_node.estado=inicio;

	frontier.push_back(current_node);
	bool SolutionFound = (current_node.estado.f==final.f and current_node.estado.c==final.c);
	while(!SolutionFound and !frontier.empty()){
		frontier.pop_front();
		explored.push_back(current_node);

		if(terreno[current_node.estado.f][current_node.estado.c]=='D'){
			current_node.estado.zapas=true;
		}
		
		NodoA child_WALK = current_node;

		child_WALK.estado = applyA(WALK,current_node.estado, terreno, altura);
		if(child_WALK.estado.f==final.f and child_WALK.estado.c==final.c){
			child_WALK.secuencia.push_back(WALK);
			current_node=child_WALK;
			SolutionFound=true;
		}
		else if( !Find(child_WALK, frontier) and !Find(child_WALK, explored)){
			child_WALK.secuencia.push_back(WALK);
			frontier.push_back(child_WALK);
		}

		if(!SolutionFound){
			NodoA child_TURN_SR = current_node;
			child_TURN_SR.estado=applyA(TURN_SR,current_node.estado, terreno, altura);
			if( !Find(child_TURN_SR, frontier) and !Find(child_TURN_SR, explored)){
				child_TURN_SR.secuencia.push_back(TURN_SR);
				frontier.push_back(child_TURN_SR);
			}
		}

		if(!SolutionFound and !frontier.empty()){
			current_node = frontier.front();
			SolutionFound = (current_node.estado.f==final.f and current_node.estado.c==final.c);
		}
	}

	//if(SolutionFound) path=current_node.secuencia;
	
	return path;
}

void AnularMatrizA(vector<vector<unsigned char>> &m)
{
	for (int i = 0; i < m.size(); i++)
	{
		for (int j = 0; j < m[0].size(); j++)
		{
			m[i][j] = 0;
		}
	}
}

void ComportamientoAuxiliar::VisualizaPlan(const EstadoA &st, const list<Action> &plan)
{
	AnularMatrizA(mapaConPlan);
	EstadoA cst = st;
	auto it = plan.begin();
	while (it != plan.end())
	{
		switch (*it)
		{
		case WALK:
			switch (cst.brujula)
			{
				case 0:
					cst.f--;
				break;
				case 1:
					cst.f--;
					cst.c++;
				break;
				case 2:
					cst.c++;
				break;
				case 3:
					cst.f++;
					cst.c++;
				break;
				case 4:
					cst.f++;
				break;
				case 5:
					cst.f++;
					cst.c--;
				break;
				case 6:
					cst.c--;
				break;
				case 7:
					cst.f--;
					cst.c--;
				break;
			}
			mapaConPlan[cst.f][cst.c] = 2;
		break;
		case TURN_SR:
			cst.brujula = (cst.brujula + 1) % 8;
		break;
		}
		it++;
	}
}

/****************************************************************************************** */
// NIVEL 4
/****************************************************************************************** */

bool ComportamientoAuxiliar::HayAgente(const vector<unsigned char> & ags,bool flag)
{
	bool cond=ags[2]!='_' or ags[6]!='_';
	if(!flag) cond=cond or ags[12]!='_';
	return cond;
}

int ComportamientoAuxiliar::FallaPlan(Sensores sensores,Action next_action, const vector<vector<unsigned char>> &terreno, const vector<vector<unsigned char>> &altura, bool energy_reload, int umbral_energia){

	EstadoA actual;
	actual.brujula=sensores.rumbo;
	actual.c=sensores.posC;
	actual.f=sensores.posF;
	actual.zapas=zap;

	if(HayAgente(sensores.agentes,true))
		return 2;
	if(sensores.energia<=umbral_energia and !energy_reload)
		return 3;
	if(next_action==RUN or next_action==WALK)
		if(!CasillaAccesibleAuxiliar(actual,terreno,altura)) return 1;
	return 0;
}

void ComportamientoAuxiliar::GetBasesA(set<pair<int,int>> &bases, int f, int c, const vector<vector<unsigned char>> &terreno,int k){
	if(k>3) k=3;

	for(int i=-k; i<k; i++){
		for(int j=-k; j<k; j++){
			if(terreno[f+i][c+j]=='X')				//Guardo las casillas sí o sí aunque si está repetida no se añade de nuevo
				bases.insert(make_pair(f+i,c+j));
		}
	}
}

list<Action> ComportamientoAuxiliar::Dijkstra_mod(const EstadoA &inicio, const set<pair<int,int>> & bases, const vector<vector<unsigned char>> &terreno, const vector<vector<unsigned char>> &altura){
	NodoA current_node;
	set<NodoA> explored;											// Lista de cerrados
	priority_queue<NodoA,vector<NodoA>,ComparadorA> frontier;		// Lista de abiertos

	list<Action> path;

	current_node.estado=inicio;
	current_node.coste=0;
	current_node.heuristica=0;

	frontier.push(current_node);

	while(!frontier.empty() and !bases.count(make_pair(current_node.estado.f,current_node.estado.c))){

		current_node=frontier.top();
		frontier.pop();


		if(terreno[current_node.estado.f][current_node.estado.c]=='D'){
			current_node.estado.zapas=true;
		}

		if(explored.count(current_node)==0){
			explored.insert(current_node);
			
			NodoA child_WALK=current_node;
			child_WALK.estado=applyA(WALK,current_node.estado,terreno,altura);
			child_WALK.coste=current_node.coste+whatCost(current_node.estado.f,current_node.estado.c,child_WALK.estado.f,child_WALK.estado.c,WALK, terreno, altura);
			child_WALK.secuencia.push_back(WALK);
			child_WALK.heuristica=0;

			if(explored.count(child_WALK)==0){
				frontier.push(child_WALK);
			}

			NodoA child_TURN_SR=current_node;
			child_TURN_SR.estado=applyA(TURN_SR,current_node.estado,terreno,altura);
			child_TURN_SR.coste=current_node.coste+whatCost(current_node.estado.f,current_node.estado.c,child_TURN_SR.estado.f,child_TURN_SR.estado.c,TURN_SR, terreno, altura);
			child_TURN_SR.secuencia.push_back(TURN_SR);
			child_TURN_SR.heuristica=0;

			if(explored.count(child_TURN_SR)==0){
				frontier.push(child_TURN_SR);
			}
		}
	}

	if(bases.count(make_pair(current_node.estado.f,current_node.estado.c))){		//Si he llegado a alguna
		for(int i=0; i<current_node.secuencia.size(); i++){
			path.push_back(current_node.secuencia[i]);
		}
	}
	
	return path;
}

float ComportamientoAuxiliar::porcentajeA(const vector<vector<unsigned char>> &terreno){
	int conocidas = 0;
    for (int i = 0; i < terreno.size(); i++) {
        for (int j = 0; j < terreno[0].size(); j++) {
            if (terreno[i][j] != '?')
                conocidas++;
        }
    }

    int total = terreno.size() * terreno[0].size();
    return total > 0 ? static_cast<float>(conocidas) / total : 0.0f;
}

bool ComportamientoAuxiliar::VeoDestino(int f, int c, Orientacion rumbo, int destf, int destc){

	int k=1;

	switch(rumbo){
		case sur:
			k=-1;
		case norte:
			if(destf==f and destc==c) return true;
			else if(destf==f-k and (destc==c-k or destc==c or destc==c+k)){
				return true;
			}
			else if(destf==f-2*k and (destc==c-2*k or destc==c-k or destc==c or destc==c+k or destc==c+2*k)){
				return true;
			}
			else if((destf==f-3*k) and (destc==c-3*k or destc==c-2*k or destc==c-k or destc==c or destc==c+k or destc==c+2*k or destc==c+3*k)){
				return true;
			}
		break;
		case oeste:
			k=-1;
		case este:
			if(destc==c and destf==f) return true;
			else if(destc==c+k and (destf==f-k or destf==f or destf==f+k)){
				return true;
			}
			else if(destc==c+2*k and (destf==f-2*k or destf==f-k or destf==f or destf==f+k or destf==f+2*k)){
				return true;
			}
			else if((destc==c+3*k) and (destf==f-3*k or destf==f-2*k or destf==f-k or destf==f or destf==f+k or destf==f+2*k or destf==f+3*k)){
				return true;
			}
		break;
		case suroeste:
			if((destf>=f and destf<=f+3) and (destc<=c and destc>=c-3)) return true;
		break;
		case noreste:
			if((destf<=f and destf>=f-3) and (destc>=c and destc<=c+3)) return true;
		break;
		case noroeste:
			if((destf<=f and destf>=f-3) and (destc<=c and destc>=c-3)) return true;
		break;
		case sureste:
			if((destf>=f and destf<=f+3) and (destc>=c and destc<=c+3)) return true;
		break;
	}
	return false;
}