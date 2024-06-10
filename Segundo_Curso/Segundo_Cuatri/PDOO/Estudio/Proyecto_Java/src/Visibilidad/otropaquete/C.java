/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package Visibilidad.otropaquete;

import Visibilidad.*;

/**
 *
 * @author el_dramas
 */
public class C extends B{
    protected int protegidoinstanciaC;
    private void privadoC(){
        
    }
    
    protected void protegidoC(){
        
    }
    
    @Override
    protected void protheredado(){
        
    }
    
    void paqueteC(){
        
    }
    
    public void testC(C instanciaC,B instanciaB, D instanciaD){
        instanciaC.protegidoinstanciaC =0;
        this.protegidoinstanciaC = 0;
        //instanciaC.protegidoinstanciaB=0;
        //this.protegidoinstanciaB = 0;
        protegidoB(instanciaB,new A(),instanciaC);
        protegidoA();
        //privadoA();   //Porque no estoy en A
        this.protegidoC(); //Porque esta en mi mismo paquete
        
        instanciaC.privadoC();
        instanciaC.protegidoC();    //Porque el código esta en mi mismo paquete
        instanciaC.protegidoB(instanciaB,new A(),instanciaC); //Porque es un yo y es visible por mi
        instanciaC.protegidoA(); //Porque es un yo y es visible por mi
        
        //instanciaB.protegidoB(); //Porque no es un yo
        //instanciaB.protegidoA(); //Porque no es un yo
        //instanciaB.protegidoC(); //Porque no existe
        //instanciaB.privadoB();   //Porque no es de Tipo C
        
        instanciaD.protegidoA();
        //protegidoD();   //No esta en mi paquete
    }
}
