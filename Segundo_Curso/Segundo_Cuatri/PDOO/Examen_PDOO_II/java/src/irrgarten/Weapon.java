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
    /**
     * Poder de ataque del arma
     */
    private float power;
    /**
     * Número de usos restantes del arma
     */
    private int uses;
    
    /**
     * @brief Constructor, construye un arma según sus atributos
     * @param strength Poder de ataque
     * @param durability Número de usos del arma
     */
    Weapon(float strength, int durability){
        power = strength;
        uses = durability;
    }
    
    /**
     * Ataca con el arma si no esta rota, pierde un uso
     * @return El poder de ataque
     */
    public float attack(){  
        float atk_val = 0;
        if(uses > 0){
            atk_val = power;
            uses--;
        }
        return atk_val;
    }
    
    /**
     * @brief Representa la instancia como string
     * @return Los atributos del arma
     */
    public String toString(){
        return "W[" + power +"," + uses + "]";
    }
    

    /**
     * Decide si desechar el arma según los usos que le queden
     * @return True si decide desecharla
     */
    public boolean discard(){
        return Dice.discardElement(uses);  
    }
}


