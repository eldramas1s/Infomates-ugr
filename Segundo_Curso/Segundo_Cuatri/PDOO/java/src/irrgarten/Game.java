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
    private static final int COLS = 15;
    private static final int ROWS = 15;
    private static final String EMPTY_LOG = "";
    
    //Datos miembro
    private int currentPlayerIndex;
    private String log;
    
    private Player currentPlayer;
    private ArrayList<Player> players;
    private ArrayList<Monster> monsters;
    private Labyrinth labyrinth;
    
    /**
     * Crea un juego
     * @param nplayers número de jugardoes con los que jugar
     */
    public Game(int nplayers){
        
        //creacion de jugadores
        players = new ArrayList<>();
        for (int i=0; i< nplayers; ++i){
            Player p = new Player(String.valueOf(i).charAt(0),Dice.randomIntelligence(),Dice.randomStrength());
            players.add(p);
        }
        currentPlayerIndex = Dice.whoStarts(nplayers);

        //Creacion del jugador inicial
        currentPlayer = players.get(currentPlayerIndex);
        
        //Creacion de los monstruos
        monsters = new ArrayList<>(); //Tambien se puede poner new Monster[//necesitaparametro]
        
        
        //Creado asi aposta
        labyrinth = new Labyrinth(ROWS,COLS,ROWS-2,COLS-1);
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
            avatars += player.toString() + "\n";
        }
    
        String beasts = "";
        for (Monster monster : monsters) { //Para cada monstruo añado su to_string y un endl
            beasts += monster.toString() + "\n";
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
        labyrinth.addBlock(Orientation.VERTICAL, 0, 0,COLS);
        labyrinth.addBlock(Orientation.HORIZONTAL, 0, 1, ROWS);
        labyrinth.addBlock(Orientation.HORIZONTAL, ROWS-1, 1, ROWS);
        labyrinth.addBlock(Orientation.VERTICAL, 1, COLS-1, COLS);

        //*Creacion de monstruos
        monsters.add(new Monster(BOSS_NAME,8f,8f));
        labyrinth.addMonster(ROWS-2, COLS-2,monsters.get(0)); //Boss de la salida

        //Monstruos débiles (regalo en sitios lejanos o algo así)
        int nMonsters = 5;

        Integer[] intelligences = {3, 2, 3, 6, 5};
        Integer[] strengths = {2, 3, 3, 5, 6};
        for(int i = 0; i < nMonsters; i++){
            monsters.add(new Monster(MONSTER_NAME,intelligences[i],strengths[i]));
        }

        labyrinth.addMonster(6, COLS-3, monsters.get(1)); 
        labyrinth.addMonster(1, COLS-3, monsters.get(2)); 
        labyrinth.addMonster(11, 11,monsters.get(3));


        labyrinth.addMonster(12, 11,monsters.get(4));
        labyrinth.addMonster(13, 10,monsters.get(5));

        //* Monstruo para debug de resurrección 
        //labyrinth.addMonster(5,5,new Monster("elpapu",100,100));



        //*Creacion del resto de paredes
        labyrinth.addBlock(Orientation.VERTICAL, 1, COLS-2, COLS);
        labyrinth.addBlock(Orientation.VERTICAL, (ROWS>>1), COLS-3, (COLS>>1) -1);
        labyrinth.addBlock(Orientation.VERTICAL, (ROWS>>1) -2, COLS-4, (COLS>>1) -1);
     
        labyrinth.addBlock(Orientation.VERTICAL, 9, 2, 3);
        labyrinth.addBlock(Orientation.VERTICAL, 9, 3, 2);
        labyrinth.addBlock(Orientation.VERTICAL, 9, 4, 3);


        labyrinth.addBlock(Orientation.HORIZONTAL, 1,9, 3);
        labyrinth.addBlock(Orientation.HORIZONTAL, 2,9, 3);
        labyrinth.addBlock(Orientation.HORIZONTAL, 3,9, 3);
        labyrinth.addBlock(Orientation.HORIZONTAL, 5,9, 2);
        labyrinth.addBlock(Orientation.HORIZONTAL, 8,6, 6);
        labyrinth.addBlock(Orientation.HORIZONTAL, 9,6, 6);
        labyrinth.addBlock(Orientation.HORIZONTAL, 10,6, 6);
        labyrinth.addBlock(Orientation.HORIZONTAL, 11,6, 4); 
        labyrinth.addBlock(Orientation.HORIZONTAL, 13,1, ROWS-6);

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
            currentPlayer = new FuzzyPlayer(currentPlayer);
            players.set(currentPlayerIndex,currentPlayer);
            labyrinth.switchPlayer(currentPlayer);
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
