/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package Visibilidad;
import Visibilidad.otropaquete.*;
/**
 *
 * @author el_dramas
 */
public class B extends A{
    protected int protegidoinstanciaB;
    private void privadoB(){
        
    }
    protected void protegidoB(B instanciaB, A instanciaA, C instanciaC){
        instanciaB.privadoB(); //Porque es de mi tipo
        instanciaB.protegidoB(instanciaB, instanciaA, instanciaC); //Porque es de mi tipo y es de mi mismo paquete
        //instanciaB.privadoA(); //Porque el codigo no esta en el codigo de mi clase LOS METODOS PRIVADOS NO SE HEREDAN
        //instanciaB.privadoC(); //Porque no existe
        
        privadoB();     //Porque estoy en la misma clase
        //privadoA();   //Porque this no es de tipo A y no estoy en el codigo de A
        //privadoC();   //Porque no existe
        protegidoA();   //Porque el codigo esta en mi mismo paquete y B tambien
        //protegidoC();   //Porque no existe
        protegidoB(instanciaB, instanciaA, instanciaC);   //Porque el codigo esta en mi mismo paquete y B tambien
        
        //instanciaA.privadoA(); //Porque el codigo no esta en mi misma clase y no es de tipo B
        instanciaA.protegidoA(); //Porque el codigo esta en mi mismo paquete y la clase tambien(esto ultimo no sirve como justificacion)
        instanciaA.protheredado(); //Porque el codigo esta en mi mismo paquete y la clase tambien, se ejecuta el de A
        //instanciaA.privadoB();     //Porque el metodo no existe para A idem con privadoC
        
        //instanciaC.protegidoC();    //Porque el codigo no es visible por mi
        //instanciaC.privadoC();  //Porque no es de tipo B y el codigo no esta en la clase B
        instanciaC.protegidoB(instanciaB, instanciaA,instanciaC);   //Porque C es un B y es visible por mi
        instanciaC.protegidoA();        //Porque el codigo esta en mi mismo paquete
        
        //instanciaC.protheredado();   //Porque C es un b y es visible por mi(al no heredar en C) (ya si hereda luego no es visible por mi)
    }
    //@Override
    private void privheredado(){    //LOS METODOS PRIVADOS NO SE HEREDAN
    
    }
    
    @Override
    protected void protheredado(){
        super.protheredado(); //Por ser subclase, el codigo esta en el mismo paquete
        protegidoA();
    }
}
