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
    
    /**
     * Constructor de CombatElement.
     * @param eff Efecto del elemento de combate.
     * @param durability Usos del elemento.
     */
    public CombatElement(float eff,int durability){
        effect = eff;
        uses = durability;
    }

    /**
     * Constructor de copia de CombatElement
     * @param other Objeto a copiar
     */
    public CombatElement(CombatElement other){
        effect = other.effect;
        uses = other.uses;
    }
    
    /**
     * Devuelve el efecto del elemento
     * @return effect de elemento
     * @post Pierde un uso.
     */
    protected float produceEffect(){        //Es prtected para poder llamarlo desde las clases hijas
        float eff_val = 0;
        if(uses > 0){
            eff_val = effect;
            uses--;
        }
        return eff_val;
    }
    
    /**
     * Calcula la probabilidad de eliminar el elemento.
     * @return Probabilidad de eliminar el elemento.
     */
    public boolean discard(){
        return Dice.discardElement(uses);
    }
    
    /**
     * Concatena la informacion de una instancia
     * @return Cadena con la informacion.
     */
    @Override
    public String toString(){
        return "[" + effect + "," + uses + "]";
    }
}
