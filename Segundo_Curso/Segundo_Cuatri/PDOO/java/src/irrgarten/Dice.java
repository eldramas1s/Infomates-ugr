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
public class Dice { //TODO: cambiar a de clase
    static int MAX_USES = 5; //numero máximo de usos de armas y escudos
    static float MAX_INTELLIGENCE = 10.0f; //Valor máximo para la inteligencia de jugadores y monstruos
    static float MAX_STRENGTH =10.0f; //Valor máximo fuerza jugadores
    static float RESURRECT_PROB=0.3f; //probabilidad de ser resucitado en cada turno
    static int WEAPONS_REWARD=2; //máximo de armas ganadas por combate ganado
    static int SHIELDS_REWARD=3;//máximo de escudos ganados por combate ganado
    static int HEALTH_REWARD=5;//maximo de vida recuperada por combate ganado
    static int MAX_ATTACK=3;//máxima potencia de las armas
    static int MAX_SHIELD=2;//máximo potencia de los escudos
    
    static Random generator;
    
    static public int randomPos(int max){
        return generator.nextInt(max);
    }
    
    static public int whoStarts(int nPlayers){
        return generator.nextInt(nPlayers);
    }
    
    static public float randomIntelligence(){
        return generator.nextFloat()*MAX_INTELLIGENCE;
    }
    
    static public float randomStrength(){
        return generator.nextFloat()*MAX_STRENGTH;
    }
    
    static public boolean resurrectPlayer(){
        //Consideramos true como menor para ajustar bien los rangos
        return generator.nextFloat() < RESURRECT_PROB; 
    }
    
    static public int weaponsReward(){
        //+1 para ajustar rango
        return generator.nextInt(WEAPONS_REWARD+1);
    }
    
    static public int shieldsReward(){
        //+1 para ajustar rango
        return generator.nextInt(SHIELDS_REWARD+1);
    }
    
    static public int healthReward(){
        return generator.nextInt(HEALTH_REWARD+1);
    }
    
    static public float weaponPower(){
        return generator.nextFloat()*MAX_ATTACK;
    }

    static public float shieldPower(){
        return generator.nextFloat()*MAX_SHIELD;
    }

    static public int usesLeft(){
        return generator.nextInt(MAX_USES+1);
    }

    static public float intensity(float competence){
        return generator.nextFloat() * competence;
    }

    static public boolean discardElement(int usesLeft){
        //distribuye de forma uniforme la probabilidad
        return generator.nextFloat() < (MAX_USES-usesLeft)/(float) MAX_USES;
    }
    
}
