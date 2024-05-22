/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package Examen;
import irrgarten.Labyrinth;
import irrgarten.Dice;
import irrgarten.Player;
import irrgarten.FuzzyGoNuts;
import irrgarten.Directions;
import java.util.ArrayList;
/**
 *
 * @author el_dramas
 */
public class examen {
    private static final Directions DIR= Directions.UP;
    
    examen(){
        
    }
    
    public static void main (){
        ArrayList<Directions> validMoves = new ArrayList <>();
        validMoves.add(DIR);
        Labyrinth lab = new Labyrinth(3,3,0,0);
        Player p = new Player('0',Dice.randomIntelligence(),Dice.randomStrength());
        lab.putPlayer2D(0, 0, 3, 0, p);
        
        System.out.println(lab.toString());
        System.out.println(p.toString());
        
        p = new FuzzyGoNuts(p);
        lab.switchPlayer(p);
        
        for ( int i=0; i< 10; i++){
        ((FuzzyGoNuts)p).move();
        }
        
        System.out.println(lab.toString());
        System.out.println(p.toString());
    }
}
