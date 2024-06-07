/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Other/File.java to edit this template
 */
package Ordinarias.Lastra2122;
import java.util.ArrayList;


interface Doblable{
    void doblar();
}

class Mapa implements Doblable{
    @Override
    public void doblar(){
        
    }
}

class Kebab implements Doblable{
    @Override
    public void doblar(){
        
    }
}

class Alfombra implements Doblable{
    @Override
    public void doblar(){
        
    }
}
/**
 *
 * @author el_dramas
 */
public class Ej3 {

    /**
     * @param args the command line arguments
     */
    public static void main(String args[]) {
            Alfombra alf = new Alfombra();
            Kebab k = new Kebab();
            Mapa map = new Mapa();
            
            EnrolladorMapas em = new EnrolladorMapas();
            EnrolladorAlfombras ea = new EnrolladorAlfombras();
            EnrolladorKebabs ek = new EnrolladorKebabs();
            
            em.enrollar(map);
            ea.enrollar(alf);
            ek.enrollar(k);
            
    }
}
