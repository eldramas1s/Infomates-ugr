/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package irrgarten;

import irrgarten.controller.Controller;

import irrgarten.UI.*;

/**
 *
 * @author airam
 */


public class Irrgarten {
    public static void main(String args[]){
        final int NPLAYERS = 1;
        Game game = new Game(NPLAYERS); 
        UI ui = new VisualUI();
        Controller control = new Controller(game,ui);
        control.play();
    }
}
