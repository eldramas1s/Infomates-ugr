#include <iostream>
#include "../Comportamientos_Jugador/rescatador.hpp"
#include "motorlib/util.h"

Action ComportamientoRescatador::think(Sensores sensores)
{
	Action accion = IDLE;

	switch (sensores.nivel)
	{
	case 0:
		accion = ComportamientoRescatadorNivel_0 (sensores);
		break;
	case 1:
		accion = ComportamientoRescatadorNivel_1 (sensores);
		break;
	case 2:
		accion = ComportamientoRescatadorNivel_2 (sensores);
		break;
	case 3:
		accion = ComportamientoRescatadorNivel_3 (sensores);
		break;
	case 4:
		accion = ComportamientoRescatadorNivel_4 (sensores);
		break;
	}

	return accion;
}

int ComportamientoRescatador::interact(Action accion, int valor)
{
	return 0;
}

Action ComportamientoRescatador::ComportamientoRescatadorNivel_0(Sensores sensores)
{

	SituarSensorEnMapa(mapaResultado, mapaCotas, mapaEntidades, sensores);

	frecuencias[sensores.posF][sensores.posC]++;		// Actualizo la matriz de frecuencias

	Action action;
	
	if(sensores.superficie[0]=='D') {
		zap=true;
	}
	if(sensores.superficie[0]=='X') {
		action=IDLE;
	}
	else if(sensores.choque){
		action=TURN_L;
	}
	else if(giro180_izq){
		action = TURN_L;
		giro180_izq = false;
	}
	else if(giro45izq!=0){
		action = TURN_SR;
		giro45izq--;
	}
	else if(HayAgente(sensores.agentes,false)){
		action = TURN_L;
		giro180_izq = true;
	}
	else{

		// Elegimos la casilla a la que ir
		int pos=Andar(sensores);
		
		switch (pos)
		{	
			case 0:
				action = TURN_L;
			break;
			case 1:
				giro45izq = 1;
				action = TURN_L;
			break;
			case 2:
				action = WALK;
			break;
			case 3:
				action = TURN_SR;
				break;
			case 4: 
				giro45izq = 1;
				action = TURN_L;
				break;
			case 6:
				action = RUN;
				break;
			case 8:
				action = TURN_SR;
			break;
		}
		
	}
	last_action = action;
	return action;
}

Action ComportamientoRescatador::ComportamientoRescatadorNivel_1(Sensores sensores)
{
	SituarSensorEnMapa(mapaResultado, mapaCotas, mapaEntidades,sensores);

	frecuencias[sensores.posF][sensores.posC]++;					// Actualizo la matriz de frecuencias

	ActualizarFrecs(sensores.posF,sensores.posC,sensores.rumbo);	// Actualizo la matriz de frecuencias
	Action action;
	
	if(sensores.superficie[0]=='D') {
		zap=true;
	}
	if(sensores.superficie[0]=='X') {
		action=IDLE;
	}
	else if(sensores.choque){
		action=TURN_L;
	}
	else if(giro180_izq){
		action = TURN_L;
		giro180_izq = false;
	}
	else if(giro45izq!=0){
		action = TURN_SR;
		giro45izq--;
	}
	else if(HayAgente(sensores.agentes,false)){
		action = TURN_L;
		giro180_izq = true;
	}
	else{

		// Elegimos la casilla a la que ir
		int pos=Andar(sensores);
		
		switch (pos)
		{	
			case 0:
				action = TURN_L;
			break;
			case 1:
				giro45izq = 1;
				action = TURN_L;
			break;
			case 2:
				action = WALK;
			break;
			case 3:
				action = TURN_SR;
				break;
			case 4: 
				giro45izq = 1;
				action = TURN_L;
				break;
			case 6:
				action = RUN;
				break;
			case 8:
				action = TURN_SR;
			break;
		}
		
	}
	last_action = action;
	return action;
}

Action ComportamientoRescatador::ComportamientoRescatadorNivel_2(Sensores sensores)
{
	Action action = IDLE;

	if(!hayPlan){
		EstadoR inicio, fin;
		inicio.f=sensores.posF;
		inicio.c=sensores.posC;
		inicio.brujula=sensores.rumbo;
		inicio.zapas=zap;

		fin.f=sensores.destinoF;
		fin.c=sensores.destinoC;

		// Obtenemos un plan
		//plan = Dijkstra(inicio,fin,mapaResultado,mapaCotas);
		plan = R_Star(inicio,fin,mapaResultado,mapaCotas);

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

Action ComportamientoRescatador::ComportamientoRescatadorNivel_3(Sensores sensores)
{
	return IDLE;
}

Action ComportamientoRescatador::ComportamientoRescatadorNivel_4(Sensores sensores)
{
	Action action = IDLE;

	if(sensores.superficie[0]=='D') zap=true;

	//Flags del nivel 4
	static bool react_flag=false,wait_flag=false,low_energy=false;

	//Estructura de almacenaje de casillas base
	static set<pair<int,int>> bases; 
	static vector<vector<unsigned char>> terreno_aux=mapaResultado;

	static EstadoR inicio,fin;
	static float porcentaje=0.0;

	if(sensores.vida>=2900-2*mapaResultado.size()){
		return ComportamientoRescatadorNivel_1(sensores);
	}
	if(sensores.energia>=2500){
		low_energy=false;
	}

	/*La bandera de esperar la llegada del auxiliar esta activa*/
	if(wait_flag){
		action=IDLE;
		if(sensores.destinoF!=fin.f or sensores.destinoC!=fin.c){	//ha cambiado el objetivo
			wait_flag=false;
			action=CALL_OFF;
			hayPlan=false;
		}
		if(sensores.choque){
			wait_flag=false;
			hayPlan=false;
		}
		return action;	
	}

	/*El herido esta grave*/
	if(sensores.gravedad){		
		wait_flag=true;		
		return CALL_ON;
	}

	/*La bandera de comportamiento reactivo esta activa*/
	if(react_flag){
		action=ComportamientoRescatadorNivel_0(sensores);
		if(!sensores.choque and (sensores.agentes[2]!='a'))		//La bandera es falsa porque trabajo en reactivo
			react_flag=false;
		return action;
	}
	
	/* En un principio, todas las banderas estan desactivadas*/
	if(!hayPlan){

		fin.f=sensores.destinoF;
		fin.c=sensores.destinoC;

		terreno_aux=mapaResultado;
		
		MapaMentiroso(terreno_aux,mapaEntidades,sensores.posF,sensores.posC,fin.f,fin.c);

		inicio.f=sensores.posF;
		inicio.c=sensores.posC;
		inicio.brujula=sensores.rumbo;
		inicio.zapas=zap;

		

		if(low_energy){
			if(bases.size()==0){
				action=ComportamientoRescatadorNivel_1(sensores);
				GetBasesR(bases,sensores.posF,sensores.posC,terreno_aux);
			}
			else{
				if(sensores.superficie[0]!='X'){
					plan=Dijkstra_mod(inicio,bases,terreno_aux,mapaCotas);				}
				else{
					return IDLE;
				}
			}
		}	
		else{
			plan=R_Star(inicio,fin,terreno_aux,mapaCotas);
		}

		VisualizaPlan(inicio,plan);
		
		hayPlan=plan.size()>0;
	}
	if(hayPlan and plan.size()>0){

		SituarSensorEnMapa(mapaResultado,mapaCotas,mapaEntidades,sensores);

		if(porcentaje<0.8){
			porcentaje=porcentajeR(mapaResultado);
			GetBasesR(bases,sensores.posF,sensores.posC,terreno_aux);
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
				action=ComportamientoRescatadorNivel_1(sensores);
			}
			if(cause==3){	
				low_energy=true;
			}
		}
	}
	else if(hayPlan and plan.size()==0){ 
		if(low_energy){
			action=IDLE;
			if(sensores.choque){
				low_energy=true;
				hayPlan=false;
			}
		}
		else{
			hayPlan=false;
		}		
	}

	return action;
}


/****************************************************************************************** */
// NIVELES 0 Y 1
/****************************************************************************************** */

/************************************/
// Funciones importantes
/************************************/

int ComportamientoRescatador::LessFreq(const Sensores & sensores){
	vector<pair<int,int>> casillas_camino;
	int f=sensores.posF;
	int c=sensores.posC;
	int result=0;

	GetPaths(f,c,sensores,casillas_camino);	//Tengo los pares que son casillas deseadas y viables por alrtura.

	pair <int,int> pos=make_pair(0,0);
	int min_frec=9999;

	if(casillas_camino.size()==0){
		return 0;
	}

	int x,y;
	for(auto it=casillas_camino.begin(); it!=casillas_camino.end(); it++){
		x=it->first;
		y=it->second;
		if(frecuencias[f+x][c+y]<min_frec){
			min_frec=frecuencias[f+x][c+y];
			pos=*it;
		}
	}

	result=GetPos(pos.first,pos.second,sensores.rumbo);
	return result;
}

void ComportamientoRescatador::GetPaths(int f, int c, const Sensores & sensores, vector<pair<int,int>> & camino){
	
	int k=1;
	static vector<unsigned char> v;

	static vector<unsigned char> no_transitables={'P','M','B'};
	
	switch(sensores.nivel){
		case 0:
			v={'C','X','D'};
		break;
		case 1:
			v={'C','S'};
		break;
		case 4:
			v={'C','S','D','T','A','X'};
		break;
	}

	

	switch (sensores.rumbo){
		case sur:
			k=-1;
		case norte:
			if(CasillaDeseada(sensores,2,v)) camino.push_back(make_pair(-k,0));
			if(CasillaDeseada(sensores,6,v) and !IsIn(no_transitables,sensores.superficie[2])) camino.push_back(make_pair(-2*k,0));
			if(CasillaDeseada(sensores,4,v) and !IsIn(no_transitables,sensores.superficie[1])) camino.push_back(make_pair(-2*k,-2*k));
			if(CasillaDeseada(sensores,8,v) and !IsIn(no_transitables,sensores.superficie[3])) camino.push_back(make_pair(-2*k,2*k));
			if(CasillaDeseada(sensores,1,v)) camino.push_back(make_pair(-k,-k));
			if(CasillaDeseada(sensores,3,v)) camino.push_back(make_pair(-k,k));
		break;	
		case oeste:
			k=-1;
		case este:
			if(CasillaDeseada(sensores,2,v)) camino.push_back(make_pair(0,k));
			if(CasillaDeseada(sensores,6,v) and !IsIn(no_transitables,sensores.superficie[2])) camino.push_back(make_pair(0,2*k));
			
			if(CasillaDeseada(sensores,4,v) and !IsIn(no_transitables,sensores.superficie[1])) camino.push_back(make_pair(-2*k,2*k));
			if(CasillaDeseada(sensores,8,v) and !IsIn(no_transitables,sensores.superficie[3])) camino.push_back(make_pair(2*k,2*k));
			if(CasillaDeseada(sensores,1,v)) camino.push_back(make_pair(-k,k));
			if(CasillaDeseada(sensores,3,v)) camino.push_back(make_pair(k,k));
		break;
		case suroeste:
			k=-1;
		case noreste:
		
			if(CasillaDeseada(sensores,2,v)) camino.push_back(make_pair(-k,k));
			if(CasillaDeseada(sensores,6,v) and !IsIn(no_transitables,sensores.superficie[2])) camino.push_back(make_pair(-2*k,2*k));
			
			if(CasillaDeseada(sensores,4,v) and !IsIn(no_transitables,sensores.superficie[1])) camino.push_back(make_pair(-2*k,0));
			if(CasillaDeseada(sensores,8,v) and !IsIn(no_transitables,sensores.superficie[3])) camino.push_back(make_pair(0,2*k));
			if(CasillaDeseada(sensores,1,v)) camino.push_back(make_pair(-k,0));
			if(CasillaDeseada(sensores,3,v)) camino.push_back(make_pair(0,k));
		break;
		case noroeste:
			k=-1;
		case sureste:
			
			if(CasillaDeseada(sensores,2,v)) camino.push_back(make_pair(k,k));
			if(CasillaDeseada(sensores,6,v) and !IsIn(no_transitables,sensores.superficie[2])) camino.push_back(make_pair(2*k,2*k));
			
			if(CasillaDeseada(sensores,4,v) and !IsIn(no_transitables,sensores.superficie[1])) camino.push_back(make_pair(0,2*k));
			if(CasillaDeseada(sensores,8,v) and !IsIn(no_transitables,sensores.superficie[3])) camino.push_back(make_pair(2*k,0));
			if(CasillaDeseada(sensores,1,v)) camino.push_back(make_pair(0,k));
			if(CasillaDeseada(sensores,3,v)) camino.push_back(make_pair(k,0));
		break;
	}


}

int ComportamientoRescatador::GetPos(int fila,int col, Orientacion rumbo){
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
	}
	return pos;
}

int ComportamientoRescatador::Andar(const Sensores & sensores){
	static vector<unsigned char> no_transitables={'P','M','B'};

	if(!(*this).zap){
		if(sensores.superficie[1]=='D' and ViablePorAlturaR((sensores.cota[1]-sensores.cota[0]))) return 1;
		else if (sensores.superficie[2]=='D' and ViablePorAlturaR((sensores.cota[2]-sensores.cota[0]))) return 2;
		else if (sensores.superficie[3]=='D' and ViablePorAlturaR((sensores.cota[3]-sensores.cota[0]))) return 3;
		else if	(sensores.superficie[4]=='D' and !IsIn(no_transitables,sensores.superficie[1]) and ViablePorAlturaR((sensores.cota[4]-sensores.cota[0]))) return 4;
		else if (sensores.superficie[6]=='D' and !IsIn(no_transitables,sensores.superficie[2]) and ViablePorAlturaR((sensores.cota[6]-sensores.cota[0]))) return 6;
		else if (sensores.superficie[8]=='D' and !IsIn(no_transitables,sensores.superficie[3]) and ViablePorAlturaR((sensores.cota[8]-sensores.cota[0]))) return 8;
	}

	int pos=LessFreq(sensores);
	return pos;
}

/************************************/
// Funciones auxiliares
/************************************/

void ComportamientoRescatador::ActualizarFrecs(int f, int c, Orientacion rumbo){
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

int ComportamientoRescatador::selector(char casilla){
	int val;
	switch(casilla){
		case 'C':
		case 'S':
			val=1;
		break;
		break;
		case 'X':
			val=0;
		break;
		case 'T':
			val=5;
		break;
		case 'D':
			if(!zap)
				val=0;
			else
				val=5;
		break;
		case 'M':
		case 'P':
			val=6;
		break;
		case 'A':
			val=4;
		break;
		case 'B':
			val=5;
		break;
		default:
			val=0;
		break;
	}
	return val;
}

bool ComportamientoRescatador::ViablePorAlturaR(int dif)
{
	if(abs(dif)<=1 or (zap and abs(dif)<=2))
		return true;
	else 
		return false;
}

bool ComportamientoRescatador::HayAgente(const vector<unsigned char> & ags,bool flag)
{
	bool cond=ags[2]!='_' or ags[6]!='_';
	if(!flag) cond=cond or ags[12]!='_';
	return cond;
}

bool ComportamientoRescatador::CasillaDeseada(const Sensores &sensores, int casilla, const vector<unsigned char> & deseadas)
{
	if(IsIn(deseadas,sensores.superficie[casilla]) and ViablePorAlturaR(sensores.cota[casilla]-sensores.cota[0]) ){
		return true;
	}
	else
		return false;
}

void ComportamientoRescatador::SituarSensorEnMapa(vector<vector<unsigned char>> &m, vector<vector<unsigned char>> &a, vector<vector<unsigned char>>& e, Sensores sensores)
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
					e[fila+param*i][col-param*j]=sensores.agentes[counter];
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
					e[fila-param*j][col-param*i]=sensores.agentes[counter];
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

			e[fila+param][col]=sensores.agentes[1];
			e[fila+2*param][col]=sensores.agentes[4];
			e[fila+3*param][col]=sensores.agentes[9];
			e[fila][col-param]=sensores.agentes[3];
			e[fila+param][col-param]=sensores.agentes[2];
			e[fila+2*param][col-param]=sensores.agentes[5];
			e[fila+3*param][col-param]=sensores.agentes[10];
			e[fila][col-2*param]=sensores.agentes[8];
			e[fila+param][col-2*param]=sensores.agentes[7];
			e[fila+2*param][col-2*param]=sensores.agentes[6];
			e[fila+3*param][col-2*param]=sensores.agentes[11];
			e[fila][col-3*param]=sensores.agentes[15];
			e[fila+param][col-3*param]=sensores.agentes[14];
			e[fila+2*param][col-3*param]=sensores.agentes[13];
			e[fila+3*param][col-3*param]=sensores.agentes[12];

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

			e[fila][col-param]=sensores.agentes[1];
			e[fila][col-2*param]=sensores.agentes[4];
			e[fila][col-3*param]=sensores.agentes[9];
			e[fila-param][col]=sensores.agentes[3];	
			e[fila-param][col-param]=sensores.agentes[2];
			e[fila-param][col-2*param]=sensores.agentes[5];
			e[fila-param][col-3*param]=sensores.agentes[10];
			e[fila-2*param][col]=sensores.agentes[8];
			e[fila-2*param][col-param]=sensores.agentes[7];
			e[fila-2*param][col-2*param]=sensores.agentes[6];
			e[fila-2*param][col-3*param]=sensores.agentes[11];
			e[fila-3*param][col]=sensores.agentes[15];
			e[fila-3*param][col-param]=sensores.agentes[14];
			e[fila-3*param][col-2*param]=sensores.agentes[13];
			e[fila-3*param][col-3*param]=sensores.agentes[12];
		break;
	}
	
}


/****************************************************************************************** */
// NIVELES 2 Y 3
/****************************************************************************************** */

list<Action> ComportamientoRescatador::Dijkstra(const EstadoR &inicio, const EstadoR &final, const vector<vector<unsigned char>> &terreno, const vector<vector<unsigned char>> &altura){
	NodoR current_node;
	set<NodoR> explored;											// Lista de cerrados
	priority_queue<NodoR,vector<NodoR>,ComparadorR> frontier;		// Lista de abiertos

	list<Action> path;

	current_node.estado=inicio;
	current_node.coste=0;
	current_node.heuristica=0;

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
			
			NodoR child_WALK=current_node;
			child_WALK.estado=applyR(WALK,current_node.estado,terreno,altura);
			child_WALK.coste=current_node.coste+whatCost(current_node.estado.f,current_node.estado.c,child_WALK.estado.f,child_WALK.estado.c,WALK, terreno, altura);
			child_WALK.secuencia.push_back(WALK);
			child_WALK.heuristica=0;

			if(explored.count(child_WALK)==0){
				frontier.push(child_WALK);
			}
			
			if(CanRun(current_node,terreno)){
				NodoR child_RUN=current_node;
				child_RUN.estado=applyR(RUN,current_node.estado,terreno,altura);
				child_RUN.coste=current_node.coste+whatCost(current_node.estado.f,current_node.estado.c,child_RUN.estado.f,child_RUN.estado.c,RUN, terreno, altura);
				child_RUN.secuencia.push_back(RUN);
				child_RUN.heuristica=0;

				if(explored.count(child_RUN)==0){
					frontier.push(child_RUN);
				}
			}
			

			NodoR child_TURN_L=current_node;
			child_TURN_L.estado=applyR(TURN_L,current_node.estado,terreno,altura);
			child_TURN_L.coste=current_node.coste+whatCost(current_node.estado.f,current_node.estado.c,child_TURN_L.estado.f,child_TURN_L.estado.c,TURN_L, terreno, altura);
			child_TURN_L.secuencia.push_back(TURN_L);
			child_TURN_L.heuristica=0;

			if(explored.count(child_TURN_L)==0){
				frontier.push(child_TURN_L);
			}

			NodoR child_TURN_SR=current_node;
			child_TURN_SR.estado=applyR(TURN_SR,current_node.estado,terreno,altura);
			child_TURN_SR.coste=current_node.coste+whatCost(current_node.estado.f,current_node.estado.c,child_TURN_SR.estado.f,child_TURN_SR.estado.c,TURN_SR, terreno, altura);
			child_TURN_SR.secuencia.push_back(TURN_SR);
			child_TURN_SR.heuristica=0;

			if(explored.count(child_TURN_SR)==0){
				frontier.push(child_TURN_SR);
			}
		}
	
		SolutionFound=(current_node.estado.f==final.f and current_node.estado.c==final.c);
	}

	if(SolutionFound){
		for(int i=0; i<current_node.secuencia.size(); i++){
			path.push_back(current_node.secuencia[i]);
		}
	}
	
	return path;

}

void ComportamientoRescatador::VisualizaPlan(const EstadoR &st, const list<Action> &plan)
{
	AnularMatrizR(mapaConPlan);
	EstadoR cst = st;
	auto it = plan.begin();
	while (it != plan.end())
	{
		switch (*it)
		{
			case RUN:
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
				mapaConPlan[cst.f][cst.c] = 3;
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
				mapaConPlan[cst.f][cst.c] = 1;
			break;
			case TURN_SR:
				cst.brujula = (cst.brujula + 1) % 8;
			break;
			case TURN_L:
				cst.brujula = (cst.brujula + 6) % 8;
			break;
		}
		it++;
	}
}

bool ComportamientoRescatador::CanRun(const NodoR &st, const vector<vector<unsigned char>> &terreno){
	const static vector<unsigned char> no_transitables={'P','M','B'};
	switch(st.estado.brujula){
		case norte:
			return !IsIn(no_transitables,terreno[st.estado.f-1][st.estado.c]);
		break;
		case noreste:
			return !IsIn(no_transitables,terreno[st.estado.f-1][st.estado.c+1]);
		break;
		case este:
			return !IsIn(no_transitables,terreno[st.estado.f][st.estado.c+1]);
		break;
		case sureste:
			return !IsIn(no_transitables,terreno[st.estado.f+1][st.estado.c+1]);
		break;
		case sur:
			return !IsIn(no_transitables,terreno[st.estado.f+1][st.estado.c]);
		break;
		case suroeste:
			return !IsIn(no_transitables,terreno[st.estado.f+1][st.estado.c-1]);
		break;
		case oeste:
			return !IsIn(no_transitables,terreno[st.estado.f][st.estado.c-1]);	
		break;
		case noroeste:
			return !IsIn(no_transitables,terreno[st.estado.f-1][st.estado.c-1]);
		break;
		default:
			return false;
		break;
	}
}

EstadoR ComportamientoRescatador::applyR(Action accion, const EstadoR & st, const vector<vector<unsigned char>> &terreno, const vector<vector<unsigned char>> &altura){
	EstadoR next=st;
	switch(accion){
		case WALK:
			if(CasillaAccesibleRescatador(accion,st,terreno,altura)){
				next=afterWalk(st);
			}
		break;
		case RUN:
			if(CasillaAccesibleRescatador(accion,st,terreno,altura)){
				next=afterRun(st);
			}
		break;
		case TURN_L:
			next.brujula=(st.brujula+6)%8;
		break;
		case TURN_SR:
			next.brujula=(st.brujula+1)%8;
		break;
	}
	return next;
}

bool ComportamientoRescatador::CasillaAccesibleRescatador(Action accion, const EstadoR &st, const vector<vector<unsigned char>> &terreno, const vector<vector<unsigned char>> &altura){
	EstadoR next;

	switch(accion){
		case WALK:
			next=afterWalk(st);
		break;
		case RUN:
			next=afterRun(st);
		break;
	}

	bool check1=false, check2 =false;

	if(next.f>=3 and next.c>=3 and next.f<=terreno.size()-3 and next.c<=terreno.size()-3){		//Esta condición depende de que el mapa sea cuadrado
		check1=terreno[next.f][next.c]!='B' and terreno[next.f][next.c]!='M' and terreno[next.f][next.c]!='P';
		int dif=abs(altura[next.f][next.c]-altura[st.f][st.c]);
		check2=dif<=1 or (dif==2 and st.zapas);
		if(terreno[next.f][next.c]=='?') return true;
		return check1 and check2;
	}
	else{
		return false;
	}
}

EstadoR ComportamientoRescatador::afterRun(const EstadoR &st){

	EstadoR next=st;
	switch (st.brujula)
	{
		case norte:
			next.f-=2;
		break;
		case noreste:
			next.f-=2;
			next.c+=2;
		break;
		case este:
			next.c+=2;
		break;
		case sureste:
			next.f+=2;
			next.c+=2;
		break;
		case sur:
			next.f+=2;
		break;
		case suroeste:
			next.f+=2;
			next.c-=2;
		break;
		case oeste:
			next.c-=2;
		break;
		case noroeste:
			next.f-=2;
			next.c-=2;
		break;
	}
	return next;
}

EstadoR ComportamientoRescatador::afterWalk(const EstadoR &st){
	EstadoR next=st;
	switch(st.brujula)
	{
		case norte:
			next.f--;
		break;
		case noreste:
			next.f--;
			next.c++;
		break;
		case este:
			next.c++;
		break;
		case sureste:
			next.f++;
			next.c++;
		break;
		case sur:
			next.f++;
		break;
		case suroeste:
			next.f++;
			next.c--;
		break;
		case oeste:
			next.c--;
		break;
		case noroeste:
			next.f--;
			next.c--;
		break;
	}
	return next;
}

int ComportamientoRescatador::whatCost(int my_f, int my_c, int new_f, int new_c, Action accion, const vector<vector<unsigned char>> &terreno, const vector<vector<unsigned char>> &altura){
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
		case RUN:
			switch(terreno[my_f][my_c]){
				case 'A':
					cost=150+sign*15;
				break;
				case 'T':
					cost=35+sign*5;
				break;
				case 'S':
					cost=3+sign*2;
				break;
				default:
					cost = 1;
				break;
			}
		break;
		case TURN_L:
			switch(terreno[my_f][my_c]){
				case 'A':
					cost=30;
				break;
				case 'T':
					cost=5;
				break;
				default:
					cost=1;
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

/********************************************/
//NIVEL 4
/********************************************/

list<Action> ComportamientoRescatador::R_Star(const EstadoR &inicio, const EstadoR &final, const vector<vector<unsigned char>> &terreno, const vector<vector<unsigned char>> &altura){
	NodoR current_node;
	set<NodoR> explored;											// Lista de cerrados
	priority_queue<NodoR,vector<NodoR>,ComparadorR> frontier;		// Lista de abiertos

	list<Action> path;

	current_node.estado=inicio;
	current_node.coste=0;
	current_node.heuristica=R_Heuristica(current_node.estado.f,current_node.estado.c,final.f,final.c);

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
			
			NodoR child_WALK=current_node;
			child_WALK.estado=applyR(WALK,current_node.estado,terreno,altura);
			child_WALK.coste=current_node.coste+whatCost(current_node.estado.f,current_node.estado.c,child_WALK.estado.f,child_WALK.estado.c,WALK, terreno, altura);
			child_WALK.secuencia.push_back(WALK);
			child_WALK.heuristica=R_Heuristica(child_WALK.estado.f,child_WALK.estado.c,final.f,final.c);

			if(explored.count(child_WALK)==0){
				frontier.push(child_WALK);
			}
			
			if(CanRun(current_node,terreno)){
				NodoR child_RUN=current_node;
				child_RUN.estado=applyR(RUN,current_node.estado,terreno,altura);
				child_RUN.coste=current_node.coste+whatCost(current_node.estado.f,current_node.estado.c,child_RUN.estado.f,child_RUN.estado.c,RUN, terreno, altura);
				child_RUN.secuencia.push_back(RUN);
				child_RUN.heuristica=R_Heuristica(child_RUN.estado.f,child_RUN.estado.c,final.f,final.c);

				if(explored.count(child_RUN)==0){
					frontier.push(child_RUN);
				}
			}
			

			NodoR child_TURN_L=current_node;
			child_TURN_L.estado=applyR(TURN_L,current_node.estado,terreno,altura);
			child_TURN_L.coste=current_node.coste+whatCost(current_node.estado.f,current_node.estado.c,child_TURN_L.estado.f,child_TURN_L.estado.c,TURN_L, terreno, altura);
			child_TURN_L.secuencia.push_back(TURN_L);
			child_TURN_L.heuristica=R_Heuristica(child_TURN_L.estado.f,child_TURN_L.estado.c,final.f,final.c);

			if(explored.count(child_TURN_L)==0){
				frontier.push(child_TURN_L);
			}

			NodoR child_TURN_SR=current_node;
			child_TURN_SR.estado=applyR(TURN_SR,current_node.estado,terreno,altura);
			child_TURN_SR.coste=current_node.coste+whatCost(current_node.estado.f,current_node.estado.c,child_TURN_SR.estado.f,child_TURN_SR.estado.c,TURN_SR, terreno, altura);
			child_TURN_SR.secuencia.push_back(TURN_SR);
			child_TURN_SR.heuristica=R_Heuristica(child_TURN_SR.estado.f,child_TURN_SR.estado.c,final.f,final.c);

			if(explored.count(child_TURN_SR)==0){
				frontier.push(child_TURN_SR);
			}
		}
	
		SolutionFound=(current_node.estado.f==final.f and current_node.estado.c==final.c);
	}

	if(SolutionFound){
		for(int i=0; i<current_node.secuencia.size(); i++){
			path.push_back(current_node.secuencia[i]);
		}
	}
	
	return path;
}

int ComportamientoRescatador::FallaPlan(Sensores sensores,Action next_action, const vector<vector<unsigned char>> &terreno, const vector<vector<unsigned char>> &altura, bool energy_reload,int umbral_energia){

	EstadoR actual;
	actual.brujula=sensores.rumbo;
	actual.c=sensores.posC;
	actual.f=sensores.posF;
	actual.zapas=zap;

	if(sensores.choque or (sensores.agentes[2]=='a'))
		return 2;
	if(sensores.energia<=umbral_energia and !energy_reload)
		return 3;
	if(next_action==RUN or next_action==WALK)
		if(!CasillaAccesibleRescatador(next_action,actual,terreno,altura)) return 1;
	return 0;
}

void ComportamientoRescatador::GetBasesR(set<pair<int,int>> &bases, int f, int c, const vector<vector<unsigned char>> &terreno,int k){
	if(k>3) k=3;									//Evito segmentation fault

	for(int i=-k; i<k; i++){
		for(int j=-k; j<k; j++){
			if(terreno[f+i][c+j]=='X')				//Guardo las casillas sí o sí aunque si está repetida no se añade de nuevo
				bases.insert(make_pair(f+i,c+j));
		}
	}
}

list<Action> ComportamientoRescatador::Dijkstra_mod(const EstadoR &inicio, const set<pair<int,int>> & bases, const vector<vector<unsigned char>> &terreno, const vector<vector<unsigned char>> &altura){
	NodoR current_node;
	set<NodoR> explored;											// Lista de cerrados
	priority_queue<NodoR,vector<NodoR>,ComparadorR> frontier;		// Lista de abiertos

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
			
			NodoR child_WALK=current_node;
			child_WALK.estado=applyR(WALK,current_node.estado,terreno,altura);
			child_WALK.coste=current_node.coste+whatCost(current_node.estado.f,current_node.estado.c,child_WALK.estado.f,child_WALK.estado.c,WALK, terreno, altura);
			child_WALK.secuencia.push_back(WALK);
			child_WALK.heuristica=0;

			if(explored.count(child_WALK)==0){
				frontier.push(child_WALK);
			}
			
			if(CanRun(current_node,terreno)){
				NodoR child_RUN=current_node;
				child_RUN.estado=applyR(RUN,current_node.estado,terreno,altura);
				child_RUN.coste=current_node.coste+whatCost(current_node.estado.f,current_node.estado.c,child_RUN.estado.f,child_RUN.estado.c,RUN, terreno, altura);
				child_RUN.secuencia.push_back(RUN);
				child_RUN.heuristica=0;

				if(explored.count(child_RUN)==0){
					frontier.push(child_RUN);
				}
			}
			

			NodoR child_TURN_L=current_node;
			child_TURN_L.estado=applyR(TURN_L,current_node.estado,terreno,altura);
			child_TURN_L.coste=current_node.coste+whatCost(current_node.estado.f,current_node.estado.c,child_TURN_L.estado.f,child_TURN_L.estado.c,TURN_L, terreno, altura);
			child_TURN_L.secuencia.push_back(TURN_L);
			child_TURN_L.heuristica=0;

			if(explored.count(child_TURN_L)==0){
				frontier.push(child_TURN_L);
			}

			NodoR child_TURN_SR=current_node;
			child_TURN_SR.estado=applyR(TURN_SR,current_node.estado,terreno,altura);
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

float ComportamientoRescatador::porcentajeR(const vector<vector<unsigned char>> &terreno){
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

void ComportamientoRescatador::MapaMentiroso(vector<vector<unsigned char>> &terreno, const vector<vector<unsigned char>> &entities,int f, int c, int destf, int destc, int k){
	//Actualizo el mapa con la información de los sensores
	for (int i = -k; i <= k; i++) {
		for (int j = -k; j <= k; j++) {
			int fila = f + i;
			int col = c + j;

			// Verifico que la posición esté dentro de los límites del mapa
			if (fila >= 0 && fila < entities.size() and col >= 0 and col < entities[0].size() ) {
				if (entities[fila][col] == 'a' and !(fila == destf and col == destc)) {
					terreno[fila][col] = 'P';
				}
			}
		}
	}
}
