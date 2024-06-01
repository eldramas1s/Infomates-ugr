/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package Clases_Abstractas;

/**
 *
 * @author el_dramas
 */
public class Cuadrado extends FiguraGeometrica {
    private float lado;
    
    public Cuadrado(float l){
        lado = l;
    }
    
    @Override
    public float Area(){
        return lado*lado;
    }
}
