/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package irrgarten;
import java.util.ArrayList;
import java.util.Collections;
/**
 *
 * @author el_dramas
 * @param <T> elemento de combate que queramos crear la baraja
 */
public abstract class CardDeck<T extends CombatElement> { //Debe ser algo que herede de CombatElement o que sea un CombatElement
    private static final int NEXT_CARD = 0;
    protected static final int NUM_CARDS = 10;
    private ArrayList<T> cardDeck;
    
    /**
     * Constructor de CardDeck.
     */
    public CardDeck(){
        cardDeck = new ArrayList<>();
    }
  
    /**
     * Añade un numero determinado de cartas de forma automatica.
     */
    protected abstract void addCards();
    
    
    /**
     * Añade una carta de tipo T
     * @param card Carta a añadir
     */
    protected void addCard(T card){
        cardDeck.add(card);
    }
    
    /**
     * Obtiene una carta del mazo eliminandola del mismo
     * @return Carta del mazo.
     */
    public T nextCard(){
        if(cardDeck.isEmpty()){
            this.addCards();
            Collections.shuffle(cardDeck);      //Baraja la collecion de cartas
        }
        T card = cardDeck.get(NEXT_CARD); 
        cardDeck.remove(NEXT_CARD);            // Borra la carta que este en la posicion NEXT_CARD=0
        return card;
    }
}
