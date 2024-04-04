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
    
    public Monster (String name, float intelligence, float strength){
        this.name = name;
        this.intelligence = intelligence;
        this.strength = strength;
        this.col = INVALID_POS;
        this.row = INVALID_POS;
        this.health = INITIAL_HEALTH;
    }
    
    public boolean dead(){
        return this.health <= 0;
    } 
    
    public float attack(){
        if (this.dead())
            return 0;
        else return Dice.intensity(strength);
    }
    
    public boolean defend(float receivedAttack){
        Boolean isDead = dead();
        if(isDead){
            float defensiveEnergy = Dice.intensity(intelligence);
            if(defensiveEnergy < receivedAttack){
                gotWounded();
                isDead = dead();
            }
        }
        return isDead;
    }
    
    public void setPos(int row, int col){
        this.row = row;
        this.col = col;
    }
    
    public String toString(){
        return "M[" + name + ", " + intelligence + ", " + strength + ", " + health + ", ("+ row + ", " + col + " )]";
    }
    
    private void gotWounded(){
        health --;
    }
}
