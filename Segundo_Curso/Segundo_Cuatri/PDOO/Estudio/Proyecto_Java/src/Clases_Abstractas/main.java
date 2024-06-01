/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Other/File.java to edit this template
 */
package Clases_Abstractas;
import java.util.ArrayList;
/**
 *
 * @author el_dramas
 */
public class main {

    /**
     * @param args the command line arguments
     */
    public static void main(String args[]) {
        ArrayList<FiguraGeometrica> array = new ArrayList();
        
        
        for(int i=0; i<10; ++i){
            array.add(new Circulo(i));
            array.add(new Cuadrado(i));
        }
        
        for(FiguraGeometrica unaFig : array){
            System.out.println(unaFig.Area());
        }
   }
}
