#include "agent_robot.h"
#include "environment.h"
#include <iostream>
#include <cstdlib>
#include <vector>
#include <utility>

using namespace std;

/*
Sensores:
	- BUMPER: sector de choque (bool)
	- Infrarrojos: se activa cuando esta en la frontera (bool)
	- Brujula: indica la orientacion (0,1,2,3)

Acciones:
	- Avanzar
	- Retroceder
	- Izquierda
	- Derecha
	- Nada
	- Empujar
Variables de estado:(a)
	- contador
	- estoy_contando(bool)[F]
	- estoy_girando (bool)[F] en cada instante se hace un unico movimiento.
Reglas:
	- Si no estoy contando y no estoy girando y no infrarrojos -> avanza
	- Si infrarrojos y no estoy contando y no estoy girando -> Derecha/izquierda y estoy girando = true.
	- Si estoy girando -> Derecha/izquierda y estoy_girando=false y estoy_contando = true y contador++.
	- Si no estoy girando y no infrarrojos y estoy contando -> avanza y contador++.
	- Si estoy contando y no estoy girando y si infrarrojos -> IDLE
¡Es importante tener en cuenta la eficiencia!

Apartado a)
-----------
Variables de estado y reglas. Buscamos un borde, cuando llegue al borde me doy la vuelta y me voy al otro borde y cuento.

Apartado b)
-----------
Variables de estado:
	- fase de giro (0,1,2) [0]
	- girar_izq (bool)[T]
Reglas: 
	- Si bumper -> idle
	- Si no infrarrojos y fase de giro = 0 -> avanzar
	- Si infrarrojos y fase de giro = 0 y girar_izq -> izquierda y fase de giro = 1
	- Si no infrarrojos y fase de giro = 1 -> avanzar y fase de giro = 2
	- Si fase de giro = 2 y girar_izq -> izquierda y fase de giro = 0 y girar_izq = false
	- Si infrarrojos y fase de giro = 0 y no girar_izq -> derecha y fase de giro = 1
	- Si fase de giro = 2 y  no girar_izq -> dcha y fase de giro = 0 y girar_izq = true
	- Si infrarrojos y fase de giro = 1 y no giro izquierda -> derecha y fase de giro = 0
	- Si infrarrojos y fase de giro = 1 y giro izquierda -> izquierda y fase de giro = 0
*/

// -----------------------------------------------------------
Agent::ActionType Agent::Think()
{
	int accion = 0;
	
	/* ESCRIBA AQUI SUS REGLAS */

	return static_cast<ActionType> (accion);

}
// -----------------------------------------------------------
void Agent::Perceive(const Environment &env)
{
	CNY70_ = env.isFrontier();
	BUMPER_ = env.isBump();
}
// -----------------------------------------------------------
string ActionStr(Agent::ActionType accion)
{
	switch (accion)
	{
	case Agent::actFORWARD: return "FORWARD";
	case Agent::actTURN_L: return "TURN LEFT";
	case Agent::actTURN_R: return "TURN RIGHT";
	case Agent::actBACKWARD: return "BACKWARD";
	case Agent::actPUSH: return "PUSH";
	case Agent::actIDLE: return "IDLE";
	default: return "???";
	}
}
