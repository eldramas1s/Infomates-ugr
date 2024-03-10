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
    static private int MAX_USES; //numero máximo de usos de armas y escudos
    static private float MAX_INTELLIGENCE; //Valor máximo para la inteligencia de jugadores y monstruos
    static private float MAX_STRENGTH; //Valor máximo fuerza jugadores
    static private float RESURRECT_PROB; //probabilidad de ser resucitado en cada turno
    static private int WEAPONS_REWARD; //máximo de armas ganadas por combate ganado
    static private int SHIELDS_REWARD;//máximo de escudos ganados por combate ganado
    static private int HEALTH_REWARD;//maximo de vida recuperada por combate ganado
    static private int MAX_ATTACK;//máxima potencia de las armas
    static private int MAX_SHIELD;//máximo potencia de los escudos
    
    // TODO: Mirar si esto es static
    Random generator;
    
    // Que yo sepa no hay constructor
    public int randomPos(int max){
        return generator.nextInt(max);
    }
    
    public int whoStarts(int nPlayers){
        return generator.nextInt(nPlayers);
    }
    
    public float randomIntelligence(){
        return generator.nextFloat()*MAX_INTELLIGENCE;
    }
    
    public float randomStrength(){
        return generator.nextFloat()*MAX_STRENGTH;
    }
    
    public boolean resurrectPlayer(){
        //Consideramos true como menor para ajustar bien los rangos
        return generator.nextFloat() < RESURRECT_PROB; 
    }
    
    public int weaponsReward(){
        //+1 para ajustar rango
        return generator.nextInt(WEAPONS_REWARD+1);
    }
    
    public int shieldsReward(){
        //+1 para ajustar rango
        return generator.nextInt(SHIELDS_REWARD+1);
    }
    
    public int healthReward(){
        return generator.nextInt(HEALTH_REWARD+1);
    }
    
    public float weaponPower(){
        return generator.nextFloat()*MAX_ATTACK;
    }

    public float shieldPower(){
        return generator.nextFloat()*MAX_SHIELD;
    }

    public int usesLeft(){
        return generator.nextInt(MAX_USES+1);
    }

    public float intensity(float competence){
        return generator.nextFloat() * competence;
    }

    public boolean discardElement(int usesLeft){
        //distribuye de forma uniforme la probabilidad
        return generator.nextFloat() < (MAX_USES-usesLeft)/(float) MAX_USES;
    }
    
}
