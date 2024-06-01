/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Other/File.java to edit this template
 */
package Polimorfismo;

/**
 *
 * @author el_dramas
 */
public class Polimorfismo {

    /**
     * @param args the command line arguments
     */
    public static void main(String args[]) {
       Persona p = new Persona();
       Persona p1 = new Profesor();

       p.hablar();
       p1.hablar();
       //((Profesor)p).hablar(); //Le estoy diciendo que p sera un profesor y no es asi -> Fallo de ejecucion (no de compilacion pues existe el codigo)
       ((Persona)p1).hablar(); //Un profesor es una persona, pero ejecuta el codigo de profesor
    }
}

class Persona{
   public void andar(){
      System.out.println("Voy andando como persona");
   }

   public void hablar(){
      System.out.println("Estoy hablando como persona");
   }
}

class Profesor extends Persona{
   @Override
   public void hablar(){
      System.out.println("Estoy impartiendo clase");
   }
}

