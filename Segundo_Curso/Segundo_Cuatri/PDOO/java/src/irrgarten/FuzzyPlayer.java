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
public class FuzzyPlayer extends Player{
    
    public FuzzyPlayer(Player other){
        super (other);
    }
    
    //TODO:
    @Override
    public Directions move( Directions direction, ArrayList<Directions> validMoves){
        return Directions.UP;
    }
    
    @Override
    public float attack(){
        return super.attack();
    }
    
    @Override
    protected float defensiveEnergy(){
        return super.defensiveEnergy();
    }
    
    @Override
    public String toString(){
        String cad = super.toString();
        cad = cad.replaceFirst("P", "F");
        return cad;
    }
}
