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
    private static final String BOSS_NAME = "Bowser";      
    private static final int COLS = 4;
    private static final int ROWS = 5;
    private static final String EMPTY_LOG = "";
    
    //Datos miembro
    private int currentPlayerIndex;
    private String log;
    
    private Player currentPlayer;
    private ArrayList<Player> players=new ArrayList<>();
    private ArrayList<Monster> monsters;
    private Labyrinth labyrinth;
    
    /**
     * Crea un juego
     * @param nplayers número de jugardoes con los que jugar
     */
    public Game(int nplayers){
        
        //creacion de jugadores
        for (int i=0; i< nplayers; ++i){
            Player p = new Player(String.valueOf(i).charAt(0),Dice.randomIntelligence(),Dice.randomStrength());
            players.add(p);
        }
        currentPlayerIndex = Dice.whoStarts(nplayers);

        //Creacion del jugador inicial
        currentPlayer = players.get(currentPlayerIndex);
        
        //Creacion de los monstruos
        monsters = new ArrayList<Monster>(); //Tambien se puede poner new Monster[//necesitaparametro]
        
        
        //Creado asi a posta
        labyrinth = new Labyrinth(ROWS,COLS,0,0);
        this.configureLabyrinth(); //inicia el laberinto
        
        log = EMPTY_LOG; 
        
        labyrinth.spreadPlayers(players);
    }

    /**
     * Comprueba si hay ganador
     * @return true si hay ganador
     */
    public boolean finished(){ 
        return labyrinth.haveAWinner();
    }
    
    /**
     * Mueve a un jugador
     * @param preferredDirection La direccion a la que mover, de ser posible, al personaje
     * @return La direacion a la que se va a mover, puede no ser preferredDirection
     */
    public boolean nextStep(Directions preferredDirection){
        log = EMPTY_LOG;
        boolean dead = currentPlayer.dead();
        if(!dead){
            Directions direction = actualDirection(preferredDirection); //Devuelve su direccion de movimiento en funcion de su posicion y su direccion preferida.
            if(direction != preferredDirection){
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
    
    /**
     * Devuelve el estado del juego
     * @return el gameState actual
     */
    public GameState getGameState() {
        String laby = labyrinth.toString();
    
        String avatars = "";
        for (Player player : players) { //Para cada jugador añado su to_string y un endl
            avatars+= (player.toString() + "\n");
        }
    
        String beasts = "";
        for (Monster monster : monsters) {
            beasts += (monster.toString() +"\n");
        }    
        int curr = currentPlayerIndex;
        boolean win = finished();
        String tempLog = log;
    
        return new GameState(laby, avatars, beasts, curr, win, tempLog);
    }
    
    /**
     * Configura el laberinto
     */
    private void configureLabyrinth(){
        
        //*Creacion de paredes iniciales
        labyrinth.addBlock(Orientation.HORIZONTAL, 2, 1, 3);

        //*Creacion de monstruos
        monsters.add(new Monster(BOSS_NAME,99999f,99999f));
        monsters.add(new Monster(MONSTER_NAME,0f,0f));
        labyrinth.addMonster(0, 2,monsters.get(0)); //Boss de la salida
        labyrinth.addMonster(3, 1,monsters.get(1)); //Boss de la salida
        
    }
    
    /**
     * Pasa el turno al siguiente jugador
     */
    private void nextPlayer(){
        currentPlayerIndex++;
        currentPlayerIndex=currentPlayerIndex % players.size();
        currentPlayer = players.get(currentPlayerIndex);
    }
    
    /**
     * Decide a que direccion te vas a mover
     * @param preferredDirection La direccion a la que te intenta mover primero
     * @return La primera dirección a la que te puede mover, puede no ser ninguna
     */
    private Directions actualDirection(Directions preferredDirection){
        int currentRow = currentPlayer.getRow();
        int currentCol = currentPlayer.getCol();
        return currentPlayer.move(preferredDirection, labyrinth.validMoves(currentRow,currentCol));
    }
    
    /**
     * Maneja el combate
     * @param monster El monstruo con el que combatir
     * @return el ganador (Jugador/Monstruo)
     */
    private GameCharacter combat(Monster monster){
        int rounds = 0;
        GameCharacter winner = GameCharacter.PLAYER;
        boolean lose = monster.defend(currentPlayer.attack());
        while (!lose && rounds < MAX_ROUNDS){
            lose = currentPlayer.defend(monster.attack());
            winner = GameCharacter.MONSTER;
            rounds++;
            if(!lose){ 
                lose = monster.defend(currentPlayer.attack());
                winner = GameCharacter.PLAYER;
            }
        }
        logRounds(rounds, MAX_ROUNDS);
        return winner;
    }
    
    /**
     * Maneja las recompensas cuando un jugador gana el combate
     * @param winner Player si ha ganado el jugador
     */
    private void manageReward(GameCharacter winner){
        if(winner == GameCharacter.PLAYER){
            currentPlayer.receiveReward();
            logPlayerWon();
        } else{
            logMonsterWon();
        }
    }
    
    /**
     * Decide al azar si resucitar a un jugador muerto en su turno
     */
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
    
    private void logNoMonster(){
        log += EMPTY_BLOCK_MSG + " " + NO_ORDER_MSG + "\n";
    }
    
    private void logRounds(int rounds, int max){
        log += " Se han producido " + rounds + " de " + max +"\n"; 
    }
}
