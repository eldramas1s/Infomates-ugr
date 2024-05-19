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
    
    /**
     * Constructor de LabyrinthCharacter.
     * @param name
     * @param intelligence
     * @param strength
     * @param health 
     */
    public LabyrinthCharacter(String name,float intelligence,float strength, float health){
        this.name = name;
        this.intelligence = intelligence;
        this.strength = strength;
        this.health = health;
        
        this.row = INVALID_POS;
        this.col = INVALID_POS; 
    }
    
    /**
     * Constructor de copia de un LabyrinthCharacter
     * @param other Instancia de LabyrinthCharacter
     */
    public LabyrinthCharacter(LabyrinthCharacter other){
        this (other.name,other.getIntelligence(),other.getStrength(),other.getHealth());    //Llama al constructor de LabyrinthCharacter
        this.row = other.row;
        this.col = other.col;
        //this.setPos(other.getRow(), other.getCol()); Da warning de overridable de setPos, es decir, si se sobreescribe no se ejecuta este metodo sino el de la ligadura dinamica

    }
    
    /**
     * Comprueba si el LabyrinthCharacter esta muerto.
     * @return true -> health <= 0;
     *         false -> health > 0;
     */
    boolean dead(){
        return this.health <= 0;
    }
    
    /**
     * Devuelve la fila.
     * @return Fila del LabyrinthCharacter.
     */
    public int getRow(){
        return this.row;
    }
    
    /**
     * Devuelve la columna.
     * @return Columna del LabyrinthCharacter.
     */
    public int getCol(){
        return this.col;
    }
    
    /**
     * Devuelve la inteligencia.
     * @return Inteligencia del LabyrinthCharacter.
     */
    protected float getIntelligence(){
        return this.intelligence;
    }
    
    /**
     * Devuelve la fuerza.
     * @return Fuerza del LabyrinthCharacter.
     */
    protected float getStrength(){
        return this.strength;
    }
    
    /**
     * Devuelve la salud.
     * @return Salud del LabyrinthCharacter.
     */
    protected float getHealth(){
        return this.health;
    }
    
    /**
     * Almacena la salud.
     * @param health salud del LabyrinthCharacter
     */
    protected void setHealth(float health){
        this.health = health;
    }
    
    /**
     * Impone la posicion del LabyrinthCharacter.
     * @param row Fila del LabyrinthCharacter.
     * @param col Columna del LabyrinthCharacter.
     */
    public void setPos(int row, int col){
        this.row = row;
        this.col = col;
    }
    
    /**
     * Concatena la informacion de una instancia.
     * @return Cadena con la informacion.
     */
    @Override
    public String toString(){
        return "[" + name + ", " + health +" HP," + strength + " SP, " +  intelligence + " IP, " + "(" + row + ", " +col + ")]";
    }
    
    /**
     * Maneja el daño de un LabyrinthCharacter.
     */
    protected void gotWounded(){
        this.health--;
    }
    
    /**
     * Maneja el ataque de un LabyrinthCharacter.
     * @return Valor de ataque.
     */
    public abstract float attack();
    
    /**
     * Maneja la defensa de un LabyrinthCharacter.
     * @param attack Ataque recibido
     * @return true -> perder por el golpe
     */
    public abstract boolean defend(float attack);

}
