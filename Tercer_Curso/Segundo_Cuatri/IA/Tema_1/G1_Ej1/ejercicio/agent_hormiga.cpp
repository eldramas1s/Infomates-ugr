#include "agent_hormiga.h"
#include "environment.h"
#include <iostream>
#include <cstdlib>
#include <vector>
#include <utility>

using namespace std;

/*
# Apartado a
- Sensores: feromona(true/false)
- Acciones: Avanzar, girar izquierda, girar derecha
- Reglas: (Transformar los sensores en acciones)
	- Si percibo foromonas delante -> avanzo
	- Si no percibo feromonas delante -> giro(izquierda o derecha pero determinista)
  
# Apartado b

- Variables de estado: Si queremos mejorar el agente podemos usarlas -> podemos evitar que haya comportamientos ciclicos de la hormiga
(parte b) -> He_girado_dcha(t/f) -> de primeras lo ponemos a que no
- Reglas 
	- Si no feromona y no he_girado_dcha -> actTURN_R y He_girado_dch=true
	- Si no tengo feromonas y he girado a la derecha -> actTURN_L
	- Si tengo feromona -> avanzo y he_girado_dcha = false

El ultimo caso no funciona al completo cuando hay bifurcaciones. Para solucionarlo hay que meter una variable de estado que permita recordar.	

EJERCICIO 2
-------------

Sensor -> grillo_quieto(comproeba si el grillo se mueve)
	   -> Posicion de la avispa
	   -> grillo_cerca

Acciones -> Cargar grillo
		 -> atrapar al grillo
		 -> Ir por el grillo
		 -> inspeccionar
Variables de estado:
		 -> memoria de la avispa
*/

// -----------------------------------------------------------
Agent::ActionType Agent::Think()
{
	int accion = 0;
	
	/* ESCRIBA AQUI LAS REGLAS */
	
	return static_cast<ActionType> (accion);

}
// -----------------------------------------------------------
void Agent::Perceive(const Environment &env)
{
	FEROMONA_ = env.isFeromona();
}
// -----------------------------------------------------------
string ActionStr(Agent::ActionType accion)
{
	switch (accion)
	{
	case Agent::actFORWARD: return "FORWARD";
	case Agent::actTURN_L: return "TURN LEFT";
	case Agent::actTURN_R: return "TURN RIGHT";
	case Agent::actIDLE: return "IDLE";
	default: return "????";
	}
}
