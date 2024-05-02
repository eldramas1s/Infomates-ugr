/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package irrgarten;
import java.util.ArrayList;
/**
 *
 * @author el_dramas
 * @param <T> elemento de combate que queramos crear la baraja
 */
public abstract class CardDeck<T extends CombatElement> {
    private static final int NEXT_CARD = 0;
    //TODO: Revisar si es así
    protected static final int NUM_CARDS = 10;
    private ArrayList<T> cardDeck;
    
    public CardDeck(){
        cardDeck = new ArrayList<>();
    }
    
    //TODO:Cuantas cartas añado
    protected void addCards(){
    }
    
    protected void addCard(T card){
        cardDeck.add(card);
    }
    
    //TODO: Revisar si es así
    public T nextCard(){
        T card = cardDeck.get(NEXT_CARD); 
        cardDeck.remove(NEXT_CARD);
        return card;
    }
}
