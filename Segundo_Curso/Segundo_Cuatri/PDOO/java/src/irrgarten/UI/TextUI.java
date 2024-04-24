
package irrgarten.UI;

import irrgarten.Directions;  //Paquete y archivo, si quiero todos los archivo poner *
import irrgarten.GameState;
import java.util.ArrayList;
import java.util.Scanner;


public class TextUI {
    
    private static Scanner in = new Scanner(System.in);
    private static ArrayList<Directions> MOVES;
    private int counter;
    
    public TextUI(){
        counter=0;
        MOVES = new ArrayList<>();
        for (int i=0; i<22; ++i){
            MOVES.add(Directions.LEFT);
        }
        MOVES.set(0, Directions.UP);
        MOVES.set(1, Directions.UP);
    }
    
    private char readChar() {
        String s = in.nextLine();     
        return s.charAt(0);
    }
    

    public Directions nextMove() {
       Directions direction = MOVES.get(counter);
       counter++;
       System.out.println(direction);
       return direction;
    }
    public void showGame(GameState gameState) {   
        System.out.println(gameState.toString());
    }
    
}
