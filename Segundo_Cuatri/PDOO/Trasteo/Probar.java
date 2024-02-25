package basico;

enum ColorPelo { MORENO, CASTAÑO, RUBIO, PELIRROJO}

public class Persona{
    private String name;
    private int edad;
    private ColorPelo pelo;
    
    public Persona (String n, int e, ColorPelo p){
        //Estamos asignando punteros
        name=n;
        edad=e; //Asignamos enteros
        pelo=p;
    }
    
    public void saluda(){
        System.out.printIn("Hola soy" +name);
    }
}