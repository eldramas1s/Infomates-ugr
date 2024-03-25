/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package irrgarten;
import java.util.ArrayList;

/**
 *
 * @author el_dramas
 */
public class Player {
    //TODO: Cambiar posicion de inicio por una random
    static private final String DEFAULT_NAME = "Player #";
    static private final int INVALID_POS = -1;
    
    static private int MAX_WEAPONS = 2;
    static private int MAX_SHIELD = 3;
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
    
    private ArrayList<Weapon> weapons = new ArrayList<Weapon>();
    private ArrayList<Shield> shields = new ArrayList<Shield>();
    
    public Player(char number, float intelligence, float strength){
        this.name = DEFAULT_NAME + number;
        this.number = number;
        this.intelligence = intelligence;
        this.strength = strength;
        this.col = INVALID_POS;
        this.row = INVALID_POS;
    }
    
    public void resurrect(){
        this.resetHits();
        this.health = INITIAL_HEALTH;
        ArrayList<Shield> newShields = new ArrayList<Shield>();
        ArrayList<Weapon> newWeapons = new ArrayList<Weapon>();
        this.shields = newShields;
        this.weapons = newWeapons;
    }
    
    public int getRow(){
        return row;
    }
    
    public int getCol(){
        return col;
    }
    
    public char getNumber(){
        return number;
    }
    
    public void setPos(int row, int col){
        this.row = row;
        this.col = col;
    }
    
    public boolean dead(){
        return health <= 0;
    }
    
    public Directions move(Directions directions, ArrayList<Directions> validMoves){
        throw new UnsupportedOperationException();        
    }
    
    public float attack(){
        if(this.dead())
            return 0;
        else return this.strength+this.sumWeapons();
    }
    
    public void receiveReward(){
        throw new UnsupportedOperationException();
    }
    public boolean defend(float receivedReward){
        return this.manageHit(receivedReward);
    }
    
    public String toString(){
        String cad= "P[" + name + ", " + intelligence + ", " + strength + ", " + health + ",(" + row + ", " +col + ", "+ consecutiveHits +")]\n"; 
        
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
        
        if(weapons.size()>0){
            cad += shields.get(shields.size()-1).toString() + "\n";
        }
        return cad;
    }
    
    private void receiveWeapon(Weapon w){
        throw new UnsupportedOperationException();
    }
    
    private void receiveShield(Shield s){
        throw new UnsupportedOperationException();
    }
    
    private Weapon newWeapon(){
        float power = Dice.randomStrength();
        int durability = Dice.usesLeft();
        Weapon arma = new Weapon(power,durability);
        return arma;
    }
    
    private Shield newShield(){
        float protection = Dice.randomStrength();
        int durability = Dice.usesLeft();
        Shield shield = new Shield(protection,durability);
        return shield;
    }
    
    private float sumWeapons(){
        float fullAttack = 0;
        
        for (int i=0; i<weapons.size(); ++i){
            fullAttack += weapons.get(i).attack();
        }
        
        return fullAttack;
    }
    
    private float sumShield(){
        float fullProtection = 0;
        
        for (int i=0; i<shields.size(); ++i){
            fullProtection += shields.get(i).protect();
        }
        
        return fullProtection;
    }
    
    private float defensiveEnergy(){
        float defenseEnergy  = intelligence + this.sumShield();
        return defenseEnergy;
    }
    
    private boolean manageHit(float receivedAttack){
        throw new UnsupportedOperationException();        
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

