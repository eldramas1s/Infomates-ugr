/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package Clases_Abstractas;

/**
 *
 * @author el_dramas
 */
public class Circulo extends FiguraGeometrica{
    private float radio;
    
    public Circulo (float r){
        radio = r;
    }
    
    @Override
    public float Area(){
        return 3.14f*radio*radio;
    }
}
