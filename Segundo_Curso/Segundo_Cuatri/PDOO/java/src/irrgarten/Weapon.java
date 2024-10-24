/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package irrgarten;

/**
 *
 * @author airam
 */
public class Weapon extends CombatElement{
    
    /**
     * @brief Constructor, construye un arma según sus atributos
     * @param strength Poder de ataque
     * @param durability Número de usos del arma
     */
    Weapon(float strength, int durability){
        super (strength,durability);        //Debe estar en la primera linea por ser un constructor
    }

    /**
     * Constructor de copia de Weapon
     * @param other Arma a copiar
     * Delega en su padre
     */
    Weapon(Weapon other){
        super(other);           //Debe estar en la primera linea por ser un constructor
    }

    /**
     * Ataca con el arma si no esta rota, pierde un uso
     * @return El poder de ataque
     */
    public float attack(){  
        return produceEffect(); //Podemos llamarlo por ser protegido
    }
    
    /**
     * @brief Representa la instancia como string
     * @return Los atributos del arma
     */
    @Override
    public String toString(){
        return "W"+super.toString();
    }
    

}


