/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package irrgarten;

/**
 *
 * @author el_dramas
 */
public class Monster extends LabyrinthCharacter {
    
    static private final int INITIAL_HEALTH = 5; 
    
    /** 
     * Crea un monstruo
     * @param name Su nombre
     * @param intelligence Su defensa / inteligencia
     * @param strength su fuerza
     */
    public Monster (String name, float intelligence, float strength){
        super (name,intelligence,strength,INITIAL_HEALTH);
    }
    
    /**
     * Comprueba si un monstruo esta muerto
     * @return True si el monstruo esta muerto
     */
    //@Override
    /*public boolean dead(){
        return super.dead();
    } 
    
    /**
     * Maneja un ataque
     * @return el valor del ataque
     */
    @Override
    public float attack(){
        if (this.dead())
            return 0;
        else return Dice.intensity(super.getStrength());
    }
    
    /**
     * Maneja la defensa
     * @param receivedAttack la fuerza del ataque recibido
     * @return True si muere con el ataque
     */
    @Override
    public boolean defend(float receivedAttack){
        Boolean isDead = dead();
        if(!isDead){
            float defensiveEnergy = Dice.intensity(super.getIntelligence());
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
    @Override
    public void setPos(int row, int col){
        super.setPos(row, col);
    }
    
    @Override
    public String toString(){
        return "M"+super.toString(); 
    }
    
}