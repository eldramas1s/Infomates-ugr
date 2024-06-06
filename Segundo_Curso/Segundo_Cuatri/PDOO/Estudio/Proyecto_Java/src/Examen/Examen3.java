/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Other/File.java to edit this template
 */
package Examen;


import java.util.ArrayList;
import java.util.Arrays;
import java.util.Random;

/**
 *
 * @author el_dramas
 */


class Examen4{
    private ArrayList<Integer> contenedor = new ArrayList<>();
    
    private Random generador = new Random();
    
    public void rellena(){
        for(int i=0; i<10; ++i){
            contenedor.add(generador.nextInt(100));
        }
    }
    
    public ArrayList<Integer> getContendor(){return contenedor;}
}
public class Examen3 {

    /**
     * @param args the command line arguments
     */
    public static void main(String args[]) {
        Examen4 ex4 = new Examen4();
        ex4.rellena();
        ex4.getContendor();
    }
}
