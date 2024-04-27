/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package irrgarten;

/**
 *
 * @author el_dramas
 */
public abstract class LabyrinthCharacter {
    
    static private final int INVALID_POS = -1;
    
    private String name;
    private float intelligence;
    private float strength;
    private float health;
    private int row;
    private int col;
    
    public LabyrinthCharacter(String name,float intelligence,float strength, float health){
        this.name = name;
        this.intelligence = intelligence;
        this.strength = strength;
        this.health = health;
        
        //TODO: Preguntar si es así.
        this.row = INVALID_POS;
        this.col = INVALID_POS; 
    }
    
    public LabyrinthCharacter(LabyrinthCharacter other){
        
    }
    
    boolean dead(){
        return this.health <= 0;
    }
    
    public int getRow(){
        return this.row;
    }
    
    public int getCol(){
        return this.col;
    }
    
    protected float getIntelligence(){
        return this.intelligence;
    }
    
    protected float getStrength(){
        return this.strength;
    }
    
    protected float getHealth(){
        return this.health;
    }
    
    protected void setHealth(float health){
        this.health = health;
    }
    
    public void setPos(int row, int col){
        this.row = row;
        this.col = col;
    }
    
    public String toString(){
        return "[" + name + ", " + health +" HP," + strength + " SP, " +  intelligence + " IP, " + "(" + row + ", " +col + ")]";
    }
    
    protected void gotWounded(){
        this.health--;
    }
    
    public abstract float attack();
    
    public abstract boolean defend(float attack);
}
