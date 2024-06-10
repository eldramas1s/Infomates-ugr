/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package Visibilidad;
import Visibilidad.otropaquete.C;
/**
 *
 * @author el_dramas
 */
public class D extends C{
    protected void protegidoD(B instanciaB,C instanciaC, D instanciaD){
        //instanciaD.privadoC(); //Porque el codigo a ejecutar no esta en mi misma clase
        instanciaD.protegidoB(instanciaB, instanciaC, instanciaD);    //Porque todo esta en el mismo paquete
        //instanciaC.protegidoC();    //Porque no es un yo
        instanciaD.protegidoC();      //Porque es un yo y es visible por mi, ya que el codigo del metodo no esta en el mismo paquete
        instanciaC.protegidoA();      //Porque el codigo esta en el mismo paquete que D
        //instanciaC.paqueteC();        //Porque esta en otro paquete
        //instanciaC.protegidoC();      //porque no es un yo pero si es visible por mi
        //instanciaC.protegidoinstanciaC=0;
    }
    
    void paqueteD(){
        
    }
}
