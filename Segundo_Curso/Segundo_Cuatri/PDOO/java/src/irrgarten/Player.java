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
public class Player extends LabyrinthCharacter {
    static private final String DEFAULT_NAME = "Player #";   
    static private int MAX_WEAPONS = 2;
    static private int MAX_SHIELDS = 3;
    static private int INITIAL_HEALTH = 10;
    static private int HITS2LOSE = 3;
    
    private char number;
    private int consecutiveHits = 0;
    private ArrayList<Weapon> weapons;
    private ArrayList<Shield> shields; 

    private ShieldCardDeck shieldDeck;
    private WeaponCardDeck weaponDeck;
    
    /**
     * Construye un jugador
     * @param number Su numero 
     * @param intelligence su inteligencia / defensa
     * @param strength su fuerza
     */
    public Player(char number, float intelligence, float strength){
        super (DEFAULT_NAME+number,intelligence,strength,INITIAL_HEALTH);
        weapons = new ArrayList<Weapon>();
        shields = new ArrayList<Shield>();

        shieldDeck = new ShieldCardDeck();
        weaponDeck = new WeaponCardDeck();

        this.number = number;
    }
    
    /**
     * Constructor de copia de un jugador
     * @param other Jugador donde el que copiar
     */
    public Player(Player other){
        super (other);
        this.consecutiveHits = other.consecutiveHits;
        this.number = other.getNumber();
        this.weapons = new ArrayList<Weapon>();
        for(Weapon w: other.weapons){
            this.weapons.add(new Weapon(w));
        }
        this.shields = new ArrayList<Shield>();
        for(Shield s: other.shields){
            this.shields.add(new Shield(s));
        }

        weaponDeck = new WeaponCardDeck();
        shieldDeck = new ShieldCardDeck();
    }

    /**
     * Maneja la resurreccion
     */
    public void resurrect(){
        this.resetHits();
        this.setHealth(INITIAL_HEALTH);
        this.shields.clear();
        this.weapons.clear();        
    }

    
    /**
     * @return El numero del jugador
     */
    public char getNumber(){
        return number;
    }
    
    /**
     * Comprueba si el jugador esta muerto
     * @return True si esta muerto
     */
    @Override
    public boolean dead(){
        return super.dead();
    }
    
    /**
     * Porporciona una direccion de movimiento de un jugador, si direction es correcta es la que se devuelve.
     * @param direction La direccion preferida
     * @param validMoves Direcciones posibles
     * @return La direccion a la que mover al jugador
     */
    public Directions move(Directions direction, ArrayList<Directions> validMoves){
        Directions output = direction;
        if(!validMoves.isEmpty() && !validMoves.contains(direction)){   //Comprueba si la direccion esta en el array
            output = validMoves.get(0);
        }
        return output;
    }
    
    /**
     * Maneja el ataque
     * @return la fuerza del ataque
     */
    @Override
    public float attack(){
        if(this.dead())
            return 0;
        else return super.getStrength()+this.sumWeapons();
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
        super.setHealth(super.getHealth()+Dice.healthReward());
    }


    /**
     * Defiende de un ataque
     * @param receivedAttack La fuerza del ataque
     * @return true si ha perdido por el golpe
     */
    @Override
    public boolean defend(float receivedAttack){
        return this.manageHit(receivedAttack);
    }
    
    /**
     * Metodo que concatena el estado
     * @return Cadena con la informacion de estado de la instancia
     */
    @Override
    public String toString(){
        String cad= "P" + super.toString() + "\n";
        
        cad += "Weapons:\n";
        
        for (int i=0; i<weapons.size()-1; ++i){
            cad += weapons.get(i).toString() + " - ";
        }
        
        if(!weapons.isEmpty()){
            cad += weapons.get(weapons.size()-1).toString() + "\n";
        }
        
        cad += "Shields:\n";
        
        for (int i=0; i<shields.size()-1; ++i){
            cad += shields.get(i).toString() + " - ";
        }
        
        if(!shields.isEmpty()){
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
     * Coge un arma de la baraja 
     * @return el arma
     */
    private Weapon newWeapon(){
        return weaponDeck.nextCard();
    }
    
    /**
     * Coge un escudo de la baraja
     * @return el escudo
     */
    private Shield newShield(){
        return shieldDeck.nextCard();
    }
    
    /**
     * Calcula el ataque con tus armas
     * @return el ataque total
     */
    protected float sumWeapons(){
        float fullAttack = 0;
        
        for (int i=0; i<weapons.size(); ++i){
            fullAttack += weapons.get(i).attack();      //Consulta el elemento de la posicion i-ésima
        }
        
        return fullAttack;
    }
    
    /**
     * Calcula la defensa de los escudos
     * @return La defensa
     */
    protected float sumShield(){
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
    protected float defensiveEnergy(){
        float defenseEnergy  = super.getIntelligence() + this.sumShield();
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
    
    private void incConsecutiveHits(){
        this.consecutiveHits++;
    }
    
    
    
}

