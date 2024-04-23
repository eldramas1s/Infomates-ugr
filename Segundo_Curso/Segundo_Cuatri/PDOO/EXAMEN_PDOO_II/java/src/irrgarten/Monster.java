/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package irrgarten;

/**
 *
 * @author el_dramas
 */
public class Monster {
    
    static private final int INVALID_POS = -1;
    
    
    static private int INITIAL_HEALTH = 5; 
    private String name;
    private float intelligence;
    private float strength;
    private float health;
    private int row;
    private int col;
    
    /** 
     * Crea un monstruo
     * @param name Su nombre
     * @param intelligence Su defensa / inteligencia
     * @param strength su fuerza
     */
    public Monster (String name, float intelligence, float strength){
        this.name = name;
        this.intelligence = intelligence;
        this.strength = strength;
        this.col = INVALID_POS;
        this.row = INVALID_POS;
        this.health = INITIAL_HEALTH;
    }
    
    /**
     * Comprueba si un monstruo esta muerto
     * @return True si el monstruo esta muerto
     */
    public boolean dead(){
        return this.health <= 0;
    } 
    
    /**
     * Maneja un ataque
     * @return el valor del ataque
     */
    public float attack(){
        if (this.dead())
            return 0;
        else return Dice.intensity(strength);
    }
    
    /**
     * Maneja la defensa
     * @param receivedAttack la fuerza del ataque recibido
     * @return True si muere con el ataque
     */
    public boolean defend(float receivedAttack){
        Boolean isDead = dead();
        if(!isDead){
            float defensiveEnergy = Dice.intensity(intelligence);
            if(defensiveEnergy < receivedAttack){
                gotWounded();
                isDead = dead();
            }
        }
        return isDead;
    }
    
    /**
     * Guarda la posicion del monstruo
     * @param row La fila
     * @param col La columna
     */
    public void setPos(int row, int col){
        this.row = row;
        this.col = col;
    }
    
    public String toString(){
        return "M[" + name + ", " + health +" HP," + strength + " SP, " +  intelligence + " IP, " + "(" + row + ", " +col + ")]"; 
    }
    
    /**
     * Maneja el daño a un monstruo
     */
    private void gotWounded(){
        health--;
    }
}