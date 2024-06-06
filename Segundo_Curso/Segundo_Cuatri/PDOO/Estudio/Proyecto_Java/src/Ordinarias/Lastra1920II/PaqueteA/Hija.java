/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Other/File.java to edit this template
 */
package Ordinarias.Lastra1920II.PaqueteA;

/**
 *
 * @author el_dramas
 */
class Padre{
    protected void protegido(){
        System.out.println("Protegido Padre");
    }
    
    void metodo(){
        System.out.println("Metodo Padre");
    }
    
    public void procesa(){
        System.out.println("Procesando en el padre...");
    }
    
    public void ejecutarTarea(){
        procesa();
        System.out.println("Fin de la tarea en el padre");
    }
}
public class Hija extends Padre{

    void test(Padre p){
        p.protegido();
        p.metodo();
    }
}
