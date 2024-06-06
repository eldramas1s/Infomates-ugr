/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Other/File.java to edit this template
 */
package Ordinarias.Lastra1920II.deepspace;
import java.util.ArrayList;
/**
 *
 * @author el_dramas
 */
public class Examen_malo {

    /**
     * @param args the command line arguments
     */
    public static void main(String args[]) {
        
        SpaceAssets sa = new SpaceAssets();
        ArrayList<Object> assets = sa.getElements();
        
        float value = 0.0f;
        
        for (Object o : assets){
            if(o instanceof Weapon){
                value += ((Weapon)o).power()*1.5f;
            }
            else{
                if(o instanceof Shield){
                    value+= ((Shield)o).boost()*1.3f;
                }
                else{
                    SpaceStation ss = (SpaceStation) o;
                    for(Weapon w : ss.getWeapon()){
                        value += w.power();
                    }
                    
                    for(Shield s : ss.getShield()){
                        value += s.boost();
                    }
                    
                    //Me da pereza crear el Hangar
                    
                    //La solucion es crear una interfaz que realicen todas las clases que haga getAction, donde cada clase hara loq ue tenga que hacer
                    // en el caso de Weapon o shield haran effecto*float y en el caso de SpaceStation hara los dos bucles.
                    //Si queremos un mejor diseño aun, usaria una clase abstracta CombatElement que junte shield y Weapon con el motivo de que solo 
                    //haya un arrayList de ambos pues no necesito mas, en ese caso se reducieria el codigo y se dejaria trabajar a la ligadura dinamica.
                    
                }
            }
        }
    }
}
