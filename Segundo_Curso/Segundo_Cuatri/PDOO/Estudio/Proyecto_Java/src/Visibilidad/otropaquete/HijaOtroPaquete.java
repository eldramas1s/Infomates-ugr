/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package Visibilidad.otropaquete;

import Visibilidad.Visibilidad;
/**
 *
 * @author el_dramas
 */
public class HijaOtroPaquete extends Visibilidad {
    
    public void testInstanciaHijaOtroPaquete(Visibilidad o){
        System.out.println(o.publico);      //Es publico
        //System.out.println(o.privado);     // NO estoy en el codigo de la misma clase que o
        //System.out.println(o.protegido);    //No es un yo
        //System.out.println(o.paquete);      //NO Estoy en el mismo paquete
        
        System.out.println(publico);      //Es publico
        //System.out.println(privado);      //Estoy en el codigo de la misma clase que o
        System.out.println(protegido);    //estoy en el mismo paquete
        //System.out.println(paquete);      //No estoy en el mismo paquete
    }
    
    public static void testClaseHijaOtroPaquete(Visibilidad o){
        System.out.println(o.publico);      //Es publico
        //System.out.println(o.privado);     // NO estoy en el codigo de la misma clase que o
        //System.out.println(o.protegido);    //No es un yo
        //System.out.println(o.paquete);      //NO Estoy en el mismo paquete
        
        //System.out.println(publico);      //Ambito de clase
        //System.out.println(privado);      //Estoy en el codigo de la misma clase que o
        //System.out.println(protegido);    // NO estoy en el mismo paquete
        //System.out.println(paquete);      //No estoy en el mismo paquete
    }
    public void testInstanciaHijaOtroPaquete(HijaOtroPaquete o){
        System.out.println(o.publico);      //Es publico
        //System.out.println(o.privado);      //Estoy en el codigo de la misma clase que o
        System.out.println(o.protegido);    //Es un yo y es visible por mi
        //System.out.println(o.paquete);      //NO Estoy en el mismo paquete
        
        System.out.println(publico);      //Es publico
        //System.out.println(privado);      //Estoy en el codigo de la misma clase que o
        System.out.println(protegido);    //Es visibli por mi por ser subclase
        //System.out.println(paquete);      //No estoy en el mismo paquete
    }
    
    public void testInstanciaHijaOtroPaquete(NietaOtroPaquete o){
        System.out.println(o.publico);      //Es publico
        //System.out.println(o.privado);      //Estoy en el codigo de la misma clase que o
        System.out.println(o.protegido);    //Es un yo y es visible por mi
        //System.out.println(o.paquete);      //NO Estoy en el mismo paquete
        
        System.out.println(publico);      //Es publico
        //System.out.println(privado);      //Estoy en el codigo de la misma clase que o
        System.out.println(protegido);    //Es visibli por mi por ser subclase
        //System.out.println(paquete);      //No estoy en el mismo paquete
    }
}
