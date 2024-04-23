/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package irrgarten;

/**
 *
 * @author el_dramas
 */
public class Shield {
    /**
     * @brief Atributo que representa de cuanto daño te puedes 
     * proteger con el escudo
     */
    private float protection;
    /**
     * @brief Atributo que representa cuantos usos quedan hasta
     * que tu escudo quede inservible.
     */
    private int uses;
    
    /**
     * @brief Constructor, construye un escudo nuevo.
     * @param defense Defensa del escudo
     * @param durability Usos que le quedan al escudo
     */
    Shield (float defense, int durability ){
        protection = defense;
        uses = durability;
    }
    
    /**
     * Proteje al jugador que porte el escudo si no está roto,
     * disminuyendo la vida útil del escudo en uno.
     * @return El valor de la absorción de daño del escudo
     */
    public float protect(){
        float prt_val=0;
        if(uses>0){
            prt_val=protection;
            uses--;
        }
        return prt_val;
    }
    /**
     * @brief Representa la instancia como string
     * @return Los atributos del escudo
     */
    public String toString(){
        return "S[" + protection + "," + uses + "]";
    }

    /**
     * Decide si desechar un arma
     * @return True si la desecha
     */
    public boolean discard(){
        return Dice.discardElement(uses);
    }
}
