package irrgarten;

/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */

import java.util.Random;


/**
 *
 * @author airam
 */
public class Dice { 
    
    
    
    /**
     *  Numero máximo de usos de armas y escudos
     */
    static private int MAX_USES = 5; 
    /**
     *  Valor máximo para la inteligencia de jugadores y monstruos
     */
    static private float MAX_INTELLIGENCE = 10.0f; 
    /**
     *  Valor máximo fuerza jugadores
     */
    static private float MAX_STRENGTH =10.0f; 
    /**
     *  Probabilidad de ser resucitado en cada turno
     */
    static private float RESURRECT_PROB=0.3f; 
    /**
     *  Máximo de armas ganadas por combate ganado
     */
    static private int WEAPONS_REWARD=2; 
    /**
     *  Máximo de escudos ganados por combate ganado
     */
    static private int SHIELDS_REWARD=3;
    /**
     *  Maximo de vida recuperada por combate ganado
     */
    static private int HEALTH_REWARD=5;
    /**
     *  Máxima potencia de las armas
     */
    static private int MAX_ATTACK=3;
    /**
     *  Máximo potencia de los escudos
     */
    static private int MAX_SHIELD=2;
    
    /**
     *  Generador de números aleatorios
     */
    static Random generator;


    /**
     * Genera la posición relativa a la fila o columna inicial
     * @param max Cota superior del rango de valores a devolver, no inclusive.
     * @return El índice de la fila o columna
     */
    static public int randomPos(int max){
        return generator.nextInt(max);
    }
    
    /**
     * Decide qué jugador tendrá el primer turno
     * @param nPlayers Número de jugadores seleccionables
     * @return El índice del jugador elegido 
     */
    static public int whoStarts(int nPlayers){
        return generator.nextInt(nPlayers);
    }
    
    /**
     * Genera un valor aleatorio de inteligencia en el intervalo [0,MAX_INTELLIGENCE[
     * @return valor de inteligencia
     */
    static public float randomIntelligence(){
        return generator.nextFloat()*MAX_INTELLIGENCE;
    }
    
    /**
     * Genera un valor aleatorio de fuerza en el intervalo [0,MAX_STRENGTH[
     * @return valor de fuerza
     */
    static public float randomStrength(){
        return generator.nextFloat()*MAX_STRENGTH;
    }
    
    /**
     * Decide si un jugador fallecido debe resucitar en el turno actual
     * @return true si debe resucitar, false en caso contrario
     */
    static public boolean resurrectPlayer(){
        //Consideramos true como menor para ajustar bien los rangos
        return generator.nextFloat() < RESURRECT_PROB; 
    }
    
    /**
     * Decide la cantidad de armas ganadas tras un combate
     * @return el número de armas en el rango [0,WEAPONS_REWARD]
     */
    static public int weaponsReward(){
        //+1 para ajustar rango
        return generator.nextInt(WEAPONS_REWARD+1);
    }
    
    /**
     * Decide la cantidad de escudos ganadas tras un combate
     * @return el número de escudos en el rango [0,SHIELDS_REWARD]
     */
    static public int shieldsReward(){
        //+1 para ajustar rango
        return generator.nextInt(SHIELDS_REWARD+1);
    }
    
    /**
     * Decide la cantidad de vida recuperada tras un combate
     * @return La vida recuperada en el rango [0,HEALTH_REWARD]
     */
    static public int healthReward(){
        return generator.nextInt(HEALTH_REWARD+1);
    }
    
    //TODO: cuando sepas que hace expandir comentario
    /**
     * Decide el poder de un arma 
     * @return El poder del arma
     */
    static public float weaponPower(){
        return generator.nextFloat()*MAX_ATTACK;
    }

    /**
     * Decide la defensa de un escudo 
     * @return La defensa del arma
     */
    static public float shieldPower(){
        return generator.nextFloat()*MAX_SHIELD;
    }

    /**
     * Decide los usos restantes que tendrá un arma o escudo
     * @return Los usos restantes
     */
    static public int usesLeft(){
        return generator.nextInt(MAX_USES+1);
    }

    /**
     * Devuelve la cantidad de competencia aplicada con un valor aleatorio 
     * en el rango [0,competence[
     * @param competence La competencia
     * @return La competencia generada
     */
    static public float intensity(float competence){
        return generator.nextFloat() * competence;
    }

    /**
     * Decide si desechar un arma según el número de usos restantes
     * @param usesLeft Número de usos del objeto
     * @return True si decide tirar el arma, false en el caso contrario
     */
    static public boolean discardElement(int usesLeft){
        //distribuye de forma uniforme la probabilidad
        return generator.nextFloat() < (MAX_USES-usesLeft)/(float) MAX_USES;
    }
    
}
