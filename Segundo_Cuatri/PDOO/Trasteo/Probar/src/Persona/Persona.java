/**
 *
 * @author el_dramas
 */
package Persona;

public class Persona {
    private String name;
    private int age;
    private ColorPelo hc;
    
    
    public Persona(String n, int e, ColorPelo p){
        name=n;
        age=e;
        hc=p;
    }
    
    public void saluda(){
        System.out.println("Hola soy" +name);
    }
}
