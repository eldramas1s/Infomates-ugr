/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Other/File.java to edit this template
 */
package Reflexion;
import Clases_Abstractas.Circulo;
import java.lang.reflect.Constructor;
import java.lang.reflect.Field;
import java.lang.reflect.Method;

/**
 *
 * @author el_dramas
 */
public class reflexion {

    /**
     * @param args the command line arguments
     */
    public static void main(String args[]) {
        Circulo c = new Circulo(3.14f);
        Class clase = c.getClass();
        Field[] varInstancia = clase.getFields();
        Constructor[] construct = clase.getConstructors();
        Method[] metodosInstancia = clase.getMethods();
        String nombreClase = clase.getSimpleName();
        
        System.out.println(varInstancia.toString());
        System.out.println(construct.toString());
        System.out.println(metodosInstancia.toString());
        System.out.println(nombreClase.toString());
    }
}
