/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package irrgarten;
import java.util.ArrayList;
import java.util.Iterator;
/**
 *
 * @author el_dramas
 */
public class Player {
    static private final String DEFAULT_NAME = "Player #";
    static private final int INVALID_POS = -1;
    
    static private int MAX_WEAPONS = 2;
    static private int MAX_SHIELDS = 3;
    static private int INITIAL_HEALTH = 10;
    static private int HITS2LOSE = 3;
    
    private String name;
    private char number;
    private float intelligence;
    private float strength;
    private float health;
    private int row;
    private int col;
    private int consecutiveHits = 0;
    
    private ArrayList<Weapon> weapons = new ArrayList<>();
    private ArrayList<Shield> shields = new ArrayList<>();
    
    /**
     * Construye un jugador
     * @param number Su numero 
     * @param intelligence su inteligencia / defensa
     * @param strength su fuerza
     */
    public Player(char number, float intelligence, float strength){
        this.name = DEFAULT_NAME + number;
        this.number = number;
        this.intelligence = intelligence;
        this.strength = strength;
        this.col = INVALID_POS;
        this.row = INVALID_POS;
        health = INITIAL_HEALTH;
    }
    
    /**
     * Maneja la resurreccion
     */
    public void resurrect(){
        this.resetHits();
        this.health = INITIAL_HEALTH;
        ArrayList<Shield> newShields = new ArrayList<>();
        ArrayList<Weapon> newWeapons = new ArrayList<>();
        this.shields = newShields;
        this.weapons = newWeapons;
    }
    
    /**
     * @return la fila del jugador
     */
    public int getRow(){
        return row;
    }
    
    /**
     * @return La columna del jugador
     */
    public int getCol(){
        return col;
    }
    
    /**
     * @return El numero del jugador
     */
    public char getNumber(){
        return number;
    }
    
    /**
     * Almacena la posicion del jugador
     * @param row la fila 
     * @param col la columna
     */
    public void setPos(int row, int col){
        this.row = row;
        this.col = col;
    }
    
    /**
     * Comprueba si el jugador esta muerto
     * @return True si esta muerto
     */
    public boolean dead(){
        return health <= 0;
    }
    
    /**
     * Porporciona una direccion de movimiento de un jugador, si direction es correcta es la que se devuelve.
     * @param direction La direccion preferida
     * @param validMoves Direcciones posibles
     * @return La direccion a la que mover al jugador
     */
    public Directions move(Directions direction, ArrayList<Directions> validMoves){
        Directions output = direction;
        if(validMoves.size() > 0 && !validMoves.contains(direction)){   //Comprueba si la direccion esta en el array
            output = validMoves.get(0);
        }
        return output;
    }
    
    /**
     * Maneja el ataque
     * @return la fuerza del ataque
     */
    public float attack(){
        if(this.dead())
            return 0;
        else return this.strength+this.sumWeapons();
    }
    
    /**
     * Maneja el recibo de recompensas
     * 
     */
    public void receiveReward(){
        int wReward = Dice.weaponsReward();
        int sReward = Dice.shieldsReward();
        while(wReward != 0){
            wReward--;
            Weapon wnew = newWeapon();
            receiveWeapon(wnew);
        }
        while(sReward != 0){
            sReward--;
            Shield snew = newShield();
            receiveShield(snew);
        }
        health += Dice.healthReward();
    }


    /**
     * Defiende de un ataque
     * @param receivedAttack La fuerza del ataque
     * @return true si ha perdido por el golpe
     */
    public boolean defend(float receivedAttack){
        return this.manageHit(receivedAttack);
    }
    
    public String toString(){
        String cad= "P[" + name + ", " + health +" HP,"+ strength + " SO, " +  intelligence + " IP, "  + ",(" + row + ", " +col + ", "+ consecutiveHits +")]\n"; 
        
        cad += "Weapons:\n";
        
        for (int i=0; i<weapons.size()-1; ++i){
            cad += weapons.get(i).toString() + " - ";
        }
        
        if(weapons.size()>0){
            cad += weapons.get(weapons.size()-1).toString() + "\n";
        }
        
        cad += "Shields:\n";
        
        for (int i=0; i<shields.size()-1; ++i){
            cad += shields.get(i).toString() + " - ";
        }
        
        if(shields.size()>0){
            cad += shields.get(shields.size()-1).toString() + "\n";
        }
        return cad;
    }
    
    /**
     * Recibe un arma y maneja el inventario
     * @param w el arma
     */
    private void receiveWeapon(Weapon w){

        Iterator<Weapon> it = weapons.iterator(); //Iteradores en java
        while(it.hasNext()){                      //Comprueba si hay otro 
            Weapon wl = it.next();                //Devuelve el siguiente
            if( wl.discard()){
                it.remove();
            }
        }
        
        if(weapons.size() < MAX_WEAPONS){
            weapons.add(w);                        //Añade en la ultima posicion
        }
    }
    
    /**
     * Recibe un escudo y maneja el inventario
     * @param s el escudo
     */
    private void receiveShield(Shield s){
        Iterator<Shield> it = shields.iterator();   //Lo inicializa antes del primero
        
        while(it.hasNext()){
            Shield sl = it.next();  //Devuelve el siguiente
            if( sl.discard()){
                it.remove();
            }
        }

        if(shields.size()<MAX_SHIELDS){
            shields.add(s);
        }
    }
    
    /**
     * Genera un arma
     * @return el arma
     */
    private Weapon newWeapon(){
        float power = Dice.weaponPower();
        int durability = Dice.usesLeft();
        Weapon arma = new Weapon(power,durability);
        return arma;
    }
    
    /**
     * Genera un escudo
     * @return el escudo
     */
    private Shield newShield(){
        float protection = Dice.shieldPower();
        int durability = Dice.usesLeft();
        Shield shield = new Shield(protection,durability);
        return shield;
    }
    
    /**
     * Calcula el ataque con tus armas
     * @return el ataque total
     */
    private float sumWeapons(){
        float fullAttack = 0;
        
        for (int i=0; i<weapons.size(); ++i){
            fullAttack += weapons.get(i).attack();      //COnsulta el elemento de la posicion i-ésima
        }
        
        return fullAttack;
    }
    
    /**
     * Calcula la defensa de los escudos
     * @return La defensa
     */
    private float sumShield(){
        float fullProtection = 0;
        
        for (int i=0; i<shields.size(); ++i){
            fullProtection += shields.get(i).protect();
        }
        
        return fullProtection;
    }
    
    /**
     * Calcula la defensa total
     * @return la defensa
     */
    private float defensiveEnergy(){
        float defenseEnergy  = intelligence + this.sumShield();
        return defenseEnergy;
    }
    
    /**
     * Maneja un ataque
     * @param receivedAttack la fuerza del ataque
     * @return si ha perdido por el ataque
     */
    private boolean manageHit(float receivedAttack){

        float defense = defensiveEnergy();
        if(defense < receivedAttack){
            gotWounded();
            incConsecutiveHits();
        } else {
            resetHits();
        }
        boolean lose = false;
        if(consecutiveHits == HITS2LOSE || dead()){
            resetHits();
            lose = true;
        }
        return lose;
    }
    
    private void resetHits(){
        this.consecutiveHits = 0;
    }
    
    private void gotWounded(){
        this.health--;
    }
    
    private void incConsecutiveHits(){
        this.consecutiveHits++;
    }
    
    
    
}

