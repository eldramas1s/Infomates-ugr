/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package irrgarten;

import java.util.ArrayList;

/**
 *
 * @author el_dramas
 */
public class FuzzyGoNuts extends FuzzyPlayer {
    private static final Directions DIR= Directions.UP;
    private ArrayList<Directions> validMoves = new ArrayList <>();
    public FuzzyGoNuts(Player other){
        super(other);
        validMoves.add(Directions.UP);
    }
    
    public Directions move(){
        Directions filtro = super.move(DIR,validMoves);
        Directions result = Dice.nextStepGoNuts(filtro, validMoves);
        return result;
    }
    
}
