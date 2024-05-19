/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package irrgarten;

/**
 *
 * @author el_dramas
 */
public class WeaponCardDeck extends CardDeck<Weapon>{   //Hereda de una clase parametrica, luego "hereda" de CarDeck con T=Shield 
    /**
     * Añade las cartas necesarias para el juego usando cada una de las posiciones de los
     * arrays defensa y usos.
     */
    @Override
    protected void addCards(){
        int ataque[] = {1,2,3,4,2,2,3,4,1,1};
        int usos[] = {3,5,1,5,1,4,3,3,2,1};
        for(int i = 0; i < NUM_CARDS; i++){
            addCard(new Weapon(ataque[i],usos[i]));
        } 
    }
}
