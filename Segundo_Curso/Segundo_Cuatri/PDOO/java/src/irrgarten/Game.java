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
public class Game {
    
    //Constantes
    private static final String PLAYER_WON_MSG = "Player Won.";
    private static final String MONSTER_WON_MSG = "Monster Won.";
    private static final String RESURRECTED_MSG = "Player resurrected.";
    private static final String SKIP_TURN_MSG = "Player is dead, turn skipped.";
    private static final String NO_ORDER_MSG = "Player couldn't move due to physical problems.";
    private static final String EMPTY_BLOCK_MSG = "Block with no action.";
    private static final int MAX_ROUNDS = 10;
    private static final String MONSTER_NAME = "Mike Wazousky";        
    private static final int COLS = 10;
    private static final int ROWS = 10;
    private static final String EMPTY_LOG = "";
    
    //Datos miembro
    private int currentPlayerIndex;
    private String log;
    
    private Player currentPlayer;
    private ArrayList<Player> players=new ArrayList<Player>();
    private ArrayList<Monster> monsters=new ArrayList<Monster>();
    private Labyrinth labyrinth;
    
    //TODO: Constructor
    public Game(int nplayers){
        
        //creacion de jugadores
        for (int i=0; i< nplayers; ++i){
            Player p = new Player(String.valueOf(i).charAt(0),Dice.randomIntelligence(),Dice.randomStrength());
            players.add(p);
        }
        currentPlayerIndex = Dice.whoStarts(nplayers);
        currentPlayer = players.get(currentPlayerIndex);
        
        monsters = new ArrayList<Monster>();
        
        //Creado asi a posta
        labyrinth = new Labyrinth(ROWS,COLS,ROWS-2,COLS-1);
        
        log = EMPTY_LOG;
        
        labyrinth.spreadPlayers(players);
    }
    public boolean finished(){
        return labyrinth.haveAWinner();
    }
    
    public boolean nextStep(Directions preferredDirection){
        return true;
    }
    
    public GameState getGameState(){
        GameState gameState = new GameState(labyrinth.toString(), players.toString(), 
                    monsters.toString(), this.currentPlayerIndex, this.finished(), log );
        return gameState;
    }
    
    //TODO: Mirar si es con Dice
    private void configureLabyrinth(){
        
    }
    
    private void nextPlayer(){
        ++currentPlayerIndex;
        currentPlayerIndex=currentPlayerIndex % players.size();
    }
    
    private Directions actualDirection(Directions preferredDirection){
        return null;
    }
    
    private GameCharacter combat(Monster monster){
        return null;
    }
    
    private void manageReward(GameCharacter winner){
        
    }
    
    private void manageResurrection(){
        
    }
    
    private void logPlayerWon(){
        log+= PLAYER_WON_MSG + "\n";
    }
    
    private void logMonsterWon(){
        log+= MONSTER_WON_MSG + "\n";
    }
    
    private void logResurrected(){
        log += RESURRECTED_MSG + "\n"; 
    }
    
    private void logPlayerSkipTurn(){
        log +=SKIP_TURN_MSG + "\n"; 
    }
    
    private void logPlayerNoOrders(){
        log += NO_ORDER_MSG + "\n";
    }
    
    private void logNoMonster(){
        log += EMPTY_BLOCK_MSG + " " + NO_ORDER_MSG + "\n";
    }
    
    private void logRounds(int rounds, int max){
        log += " Se han producido " + rounds + " de " + max +"\n"; 
    }
}
