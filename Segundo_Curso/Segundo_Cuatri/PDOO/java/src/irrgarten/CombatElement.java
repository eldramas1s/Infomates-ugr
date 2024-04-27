/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package irrgarten;

/**
 *
 * @author el_dramas
 */
public abstract class CombatElement {
    private float effect;
    private int uses;
    
    public CombatElement(float eff,int durability){
        effect = eff;
        uses = durability;
    }
    
    protected float produceEffect(){
        float eff_val = 0;
        if(uses > 0){
            eff_val = effect;
            uses--;
        }
        return eff_val;
    }
    
    public boolean discard(){
        return Dice.discardElement(uses);
    }
    
    public String toString(){
        return "[" + effect + "," + uses + "]";
    }
}
