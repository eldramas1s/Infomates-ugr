/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package Visibilidad;

/**
 *
 * @author el_dramas
 */
public class visibilidadHija extends Visibilidad {
    
    public void testInstanciaHija(Visibilidad o){
        System.out.println(o.publico);      //Es publico
        //(System.out.println(o.privado);     // NO estoy en el codigo de la misma clase que o
        System.out.println(o.protegido);    //Estoy en el mismo paquete
        System.out.println(o.paquete);      //Estoy en el mismo paquete
        
        System.out.println(publico);      //Es publico
        //System.out.println(privado);      //Estoy en el codigo de la misma clase que o
        System.out.println(protegido);    //estoy en el mismo paquete
        System.out.println(paquete);
    }
    
    public static void testClaseHija(Visibilidad o){
        System.out.println(o.publico);      //Es publico
        //(System.out.println(o.privado);     //NO estoy en el codigo de la misma clase que o
        System.out.println(o.protegido);    //Estoy en el mismo paquete
        System.out.println(o.paquete);      //Estoy en el mismo paquete
        
        //System.out.println(publico);      // Ambito de clase
        //System.out.println(privado);      // Ambito de clase
        //System.out.println(protegido);    // Ambito de clase
        //System.out.println(paquete);      // Ambito de clase
    }
}
