/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package irrgarten;

/**
 *
 * @author el_dramas
 */
public class GameState {

    /**
     *  Estado del laberinto 
     */
    private String labyrinth;
    /**
     *  Estado de los jugadores
     */
    private String players;
    /**
     *  Estado de los montruos
     */
    private String monsters;
    /**
     *  Índice del jugador al que le toca jugar
     */
    private int currentPlayer;
    /**
     *  Estado de la partida, si hay un ganador se establece el valor true.
     */
    private boolean winner;
    /**
     *  Log de la partida, recoge todo lo ocurrido desde el último turno
     */
    private String log;
    
    /**
     * Constructor: Construye un GameState a partir de los siguientes parámetros
     * @param laby El laberinto
     * @param avatars Los jugadores
     * @param beasts Los monstruos
     * @param principalPlayer El primer jugador
     * @param victorious El ganador
     * @param _log El log inicial 
     */
    GameState(String laby, String avatars, String beasts,int principalPlayer, boolean victorious, String _log){
        labyrinth = laby;
        players = avatars;
        monsters = beasts;
        currentPlayer = principalPlayer;
        winner = victorious;
        log = _log;
        
    }
    
    /** 
     * Devuelve el estado del laberinto actual
     * @return El estado del laberinto actual
     */
    public String getLabyrinthv(){
        return labyrinth;
    }
    
    /**
     * Devuelve los jugadores actuales
     * @return Los jugadores actuales
     */
    public String getPlayers(){
        return players;
    }
    
    /**
     * Devuelve los monstruos actuales
     * @return Los monstruos actuales
     */
    public String getMonsters(){
        return monsters;
    }
    
    /**
     * Devuelve el jugador al que le toca
     * @return El índice jugador al que le toca
     */
    public int getCurrentPlayer(){
        return currentPlayer;
    }
    
    /**
     * Devuelve si hay un ganador
     * @return True si hay un ganador
     */
    public boolean getWinner(){
        return winner;
    }
    
    /**
     * Devuelve el log del último turno
     * @return El log del último turno
     */
    public String getLog(){
        return log;
    }
    
}  
