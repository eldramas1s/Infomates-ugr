/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Other/File.java to edit this template
 */
package Ordinarias.Lastra1920II.subpaquete;
import Ordinarias.Lastra1920II.PaqueteA.Hija;
/**
 *
 * @author el_dramas
 */
public class Nieta extends Hija{
    
    void test(Hija p){
        //p.protegido(); //Error de compilacion, Hija no es una Nieta
        //p.metodo();    //Error de compilacion, no estoy en el mismo paquete
    }
    void test2(Nieta p){
        p.protegido();
        //p.metodo();    //Error de compilación, no estoy en el mismo paquete
    }
    @Override
    public void procesa(){
        System.out.println("Procesando en la nieta");
    }
    public void tareaNieto(){
        System.out.println("Tarea en el nieto");
    }
}
