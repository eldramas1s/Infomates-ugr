/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package irrgarten;

import irrgarten.controller.Controller;

//import java.util.ArrayList;

import UI.TextUI;

/**
 *
 * @author airam
 */


public class Prueba {
    public static void main(String args[]){
        final int NPLAYERS = 2;
        Game game = new Game(NPLAYERS); 
        TextUI UI = new TextUI();
        Controller control = new Controller(game,UI);
        control.play();
    }
}
