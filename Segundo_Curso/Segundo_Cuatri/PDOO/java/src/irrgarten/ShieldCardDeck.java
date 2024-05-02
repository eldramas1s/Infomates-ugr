/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package irrgarten;

/**
 *
 * @author el_dramas
 */
public class ShieldCardDeck extends CardDeck<Shield>{

    @Override
    protected void addCards(){
        for(int i = 0; i < NUM_CARDS; i++){
            addCard(new Shield(Dice.shieldPower(), Dice.usesLeft()));
        }
    }
    
}
