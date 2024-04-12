package irrgarten.controller;

import irrgarten.Directions;
import irrgarten.Game;
import irrgarten.UI.TextUI;


public class Controller {
    
    private Game game;
    private TextUI view;
    
    public Controller(Game game, TextUI view) {
        this.game = game;
        this.view = view;
    }
    
    public void play() {
        boolean endOfGame = false;
        while (!endOfGame) {
            //TODO: quitar esto cuando la clase GameState esté completa
            System.out.println(game.getLabyrinthv()); 

            view.showGame(game.getGameState()); 
            Directions direction = view.nextMove(); 
            endOfGame = game.nextStep(direction);
        }
        //TODO: quitar esto cuando la clase GameState esté completa
        //System.out.println(game.getLabyrinthv());

        view.showGame(game.getGameState());        
    }
        
}
