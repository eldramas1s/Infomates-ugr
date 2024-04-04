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
    private static final String NO_ORDER_MSG = "Player couldn't move due to physical problems."; //TODO revisar esta frase tmb
    private static final String EMPTY_BLOCK_MSG = "Block with no action.";
    private static final int MAX_ROUNDS = 10;
    private static final String MONSTER_NAME = "Mike Wazousky";        
    private static final int COLS = 15;
    private static final int ROWS = 15;
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
        
        //TODO revisar esto
        //Creado asi aposta
        labyrinth = new Labyrinth(ROWS,COLS,ROWS-2,COLS-1);
        this.configureLabyrinth(); //inicia el laberinto
        
        log = EMPTY_LOG; 
        
        labyrinth.spreadPlayers(players);
    }
    public boolean finished(){ 
        return labyrinth.haveAWinner();
    }
    
    public boolean nextStep(Directions preferredDirection){
        log = EMPTY_LOG;
        boolean dead = currentPlayer.dead();
        if(!dead){
            Directions direction = actualDirection(preferredDirection);
            if(direction != preferredDirection){
                System.out.println("khe");
                logPlayerNoOrders();
            }
            Monster monster = labyrinth.putPlayer(direction, currentPlayer);
            if(monster == null){
                logNoMonster();
            } else{
                GameCharacter winner = combat(monster);
                manageReward(winner);
            }

        } else{
            manageResurrection();
        }

        boolean endGame = finished(); 
        if(!endGame){
            nextPlayer();
        }
        return endGame;
    }
    
    public GameState getGameState(){
        GameState gameState = new GameState(labyrinth.toString(), players.toString(), 
                    monsters.toString(), this.currentPlayerIndex, this.finished(), log );
        return gameState;
    }

    public String getLabyrinthv(){ //TODO Eliminar cuando acabe el debug
        return labyrinth.toString();
    }
    
    //TODO: Mirar si es con Dice
    private void configureLabyrinth(){
        //TODO: Cambiar esto, esto es solo para la prueba
        //Creacion de paredes iniciales
        labyrinth.addBlock(Orientation.VERTICAL, 0, 0,COLS);
        labyrinth.addBlock(Orientation.HORIZONTAL, 0, 1, ROWS);
        labyrinth.addBlock(Orientation.HORIZONTAL, ROWS-1, 1, ROWS);
        labyrinth.addBlock(Orientation.VERTICAL, 1, COLS-1, COLS);

        //Creacion de monstruos
        labyrinth.addMonster(ROWS-2, COLS-2,new Monster(MONSTER_NAME,8f,8f));//TODO preguntar si podemos


        //creacion del resto de paredes
        labyrinth.addBlock(Orientation.VERTICAL, 1, COLS-2, COLS);
        labyrinth.addBlock(Orientation.VERTICAL, 1, COLS-2, COLS);


    }
    
    private void nextPlayer(){
        currentPlayerIndex++;
        currentPlayerIndex=currentPlayerIndex % players.size();
        currentPlayer = players.get(currentPlayerIndex);
    }
    
    private Directions actualDirection(Directions preferredDirection){
        int currentRow = currentPlayer.getRow();
        int currentCol = currentPlayer.getCol();
        return currentPlayer.move(preferredDirection, labyrinth.validMoves(currentRow,currentCol));
    }
    
    private GameCharacter combat(Monster monster){
        int rounds = 0;
        GameCharacter winner = GameCharacter.PLAYER;
        boolean lose = monster.defend(currentPlayer.attack());
        while (!lose && rounds < MAX_ROUNDS){
            lose = currentPlayer.defend(monster.attack());
            winner = GameCharacter.MONSTER;
            rounds++;
            if(!lose){ //TODO preguntar por qué player tiene un turno más
                monster.defend(currentPlayer.attack());
                winner = GameCharacter.PLAYER;
            }
        }
        logRounds(rounds, MAX_ROUNDS);
        return winner;
    }
    
    private void manageReward(GameCharacter winner){
        if(winner == GameCharacter.PLAYER){
            currentPlayer.receiveReward();
            logPlayerWon();
        } else{
            logMonsterWon();
        }
    }
    
    private void manageResurrection(){
        if(Dice.resurrectPlayer()){
            currentPlayer.resurrect();
            logResurrected();
        } else{
            logPlayerSkipTurn();
        }
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
    
    //TODO mirar esto
    private void logNoMonster(){
        log += EMPTY_BLOCK_MSG + " " + NO_ORDER_MSG + "\n";
    }
    
    private void logRounds(int rounds, int max){
        log += " Se han producido " + rounds + " de " + max +"\n"; 
    }
}
