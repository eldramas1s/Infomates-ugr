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
    
    /**
     * Constructor de FuzzyPlayer por copia.
     * @param other Otro jugador.
     */
    public FuzzyPlayer(Player other){
        super (other);
    }
    
    //TODO: Preguntar si es esto lo que se busca.
    /**
     * Calcula el movimiento de un FuzzyPlayer
     * @param direction Direccion preferente
     * @param validMoves Coleccion de movimientos posibles
     * @return Direccion de movimiento.
     */
    @Override
    public Directions move( Directions direction, ArrayList<Directions> validMoves){
        Directions output = super.move(direction, validMoves);
        return Dice.nextStep(output, validMoves, this.getIntelligence());
    }
    
    /**
     * Calcula el ataque de un FuzzyPlayer
     * @return Ataque del FuzzyPlayer.
     */
    @Override
    public float attack(){
        return super.attack();
    }
    
    /**
     * Calcula la energía defensiva de un FuzzyPlayer.
     * @return Energia defensiva de FuzzyPlayer
     */
    @Override
    protected float defensiveEnergy(){
        return super.defensiveEnergy();
    }
    
    /**
     * Concatena la informacion de una instancia.
     * @return Cadena con la informacion de la instancia.
     */
    @Override
    public String toString(){
        String cad = super.toString();
        cad = cad.replaceFirst("P", "F");
        return cad;
    }
}
