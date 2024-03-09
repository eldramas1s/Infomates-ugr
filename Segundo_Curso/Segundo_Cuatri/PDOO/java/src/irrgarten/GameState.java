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
    private String labyrinthv;
    private String players;
    private String monsters;
    private int currentPlayer;
    private boolean winner;
    private String log;
    
    GameState(String laby, String avatars, String beasts,int principalPlayer, boolean victorious, String account){
        labyrinthv = laby;
        players = avatars;
        monsters = beasts;
        currentPlayer = principalPlayer;
        winner = victorious;
        log = account;
        
    }
    
    public String getLabyrinthv(){
        return labyrinthv;
    }
    
    public String getPlayers(){
        return players;
    }
    
    public String getMonsters(){
        return monsters;
    }
    
    public int getCurrentPlayer(){
        return currentPlayer;
    }
    
    public boolean getWinner(){
        return winner;
    }
    
    public String getLog(){
        return log;
    }
    
}  
