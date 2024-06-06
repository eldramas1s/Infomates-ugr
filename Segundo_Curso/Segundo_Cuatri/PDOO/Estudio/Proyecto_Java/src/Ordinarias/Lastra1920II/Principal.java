/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Other/File.java to edit this template
 */
package Ordinarias.Lastra1920II;
import java.util.ArrayList;
import Ordinarias.Lastra1920II.PaqueteA.Hija;
import Ordinarias.Lastra1920II.subpaquete.Nieta;
/**
 *
 * @author el_dramas
 */

interface MyInterface{
    void ejecutarTarea();
} 
public class Principal {

    /**
     * @param args the command line arguments
     */
    public static void main(String args[]) {
        Nieta n = new Nieta();
        n.ejecutarTarea();
        ((Hija)n).ejecutarTarea();
        
        Hija h = new Nieta();
        //MyInterface interf=h; //Error de compilacion, Hija no realiza la interfaz, tampoco Padre
        
        //h.tareaNieto(); //Error de compilacion, Hija no dispone de ese metodo -> ((Nieta)h).tareaNieto();
        ((Nieta)h).tareaNieto();
        
        ArrayList<Integer> array = (ArrayList<Integer>) (Object) h; //Error de ejecución, h no es un ArrayList<Integer>
        //ArrayList<Hija> array2 = new ArrayList<Nieta>(); //Error de compilacion, no puede realizarse dicha conversion.
    }
}
