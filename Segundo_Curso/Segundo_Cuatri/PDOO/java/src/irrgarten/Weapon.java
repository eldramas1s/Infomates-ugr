/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package irrgarten;

/**
 *
 * @author airam
 */
public class Weapon {
    private float power;
    private int uses;
    
    Weapon(float strength, int durability){
        power = strength;
        uses = durability;
    }
    
    public float attack(){  
        float atk_val = 0;
        if(uses > 0){
            atk_val = power;
            uses--;
        }
        return atk_val;
    }
    
    public String toString(){
        return "W[" + power +"," + uses + "]";
    }
    
    public boolean discard(){
        return true;
    }
}

