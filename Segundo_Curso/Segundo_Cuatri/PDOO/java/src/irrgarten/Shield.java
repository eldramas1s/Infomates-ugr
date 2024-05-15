/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package irrgarten;

/**
 *
 * @author el_dramas
 */
public class Shield extends CombatElement {
       
    /**
     * @brief Constructor, construye un escudo nuevo.
     * @param defense Defensa del escudo
     * @param durability Usos que le quedan al escudo
     */
    Shield (float defense, int durability ){
        super(defense,durability);
    }

    Shield(Shield other){
        super(other);
    }

    /**
     * Proteje al jugador que porte el escudo si no está roto,
     * disminuyendo la vida útil del escudo en uno.
     * @return El valor de la absorción de daño del escudo
     */
    public float protect(){
        return super.produceEffect();
    }
    /**
     * @brief Representa la instancia como string
     * @return Los atributos del escudo
     */
    @Override
    public String toString(){
        return "S" + super.toString();
    }

}
