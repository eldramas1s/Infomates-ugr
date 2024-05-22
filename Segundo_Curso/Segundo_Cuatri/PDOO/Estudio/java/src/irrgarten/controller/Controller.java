package irrgarten.controller;

import irrgarten.Directions;
import irrgarten.Game;
import irrgarten.UI.*;


public class Controller {       //No es quien implementa la interfaz
    
    private Game game;
    //private TextUI view;
    private UI view;
    
    //public Controller(Game game, TextUI view) {
    public Controller(Game game, UI view) {
        this.game = game;       //inicializamos el juego
        this.view = view;       //Inicializamos la vista
    }
    
    public void play() {
        boolean endOfGame = false;
        while (!endOfGame) {

            view.showGame(game.getGameState());         //Mostramos la vista, Modulo -> Controller -> Vista
            Directions direction = view.nextMove();             //Siguiente movimiento, Vista -> Controller
            endOfGame = game.nextStep(direction);//Controller -> Game
        }

        view.showGame(game.getGameState());        //Mostramos por ultimo el estado del juego
    }
        
}
