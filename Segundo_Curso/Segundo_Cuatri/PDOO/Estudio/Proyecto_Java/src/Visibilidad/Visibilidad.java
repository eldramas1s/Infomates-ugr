/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package Visibilidad;
import Visibilidad.otropaquete.HijaOtroPaquete;
/**
 *
 * @author el_dramas
 */
public class Visibilidad {
    private int privado;
    public int publico;
    protected int protegido;
    int paquete;
    
    public void testInstanciaPadre(Visibilidad o){
        System.out.println(o.publico);      //Es publico
        System.out.println(o.privado);      //Estoy en el codigo de la misma clase que o
        System.out.println(o.protegido);    //estoy en el mismo paquete
        System.out.println(o.paquete);      //Estoy en el mismo paquete
    }
    
    public static void testClasePadre(Visibilidad o){
        System.out.println(o.publico);      //Es publico
        System.out.println(o.privado);      //Estoy en el codigo de la misma clase que o
        System.out.println(o.protegido);    //estoy en el mismo paquete
        System.out.println(o.paquete);      //Estoy en el mismo paquete
    }
    
    public void testInstanciaPadre(HijaOtroPaquete o){
        System.out.println(o.publico);      //Es publico
        //System.out.println(o.privado);      //No Estoy en el codigo de la misma clase que o
        System.out.println(o.protegido);    //estoy en el mismo paquete
        //System.out.println(o.paquete);      //No estoy en el mismo paquete
    }
}
