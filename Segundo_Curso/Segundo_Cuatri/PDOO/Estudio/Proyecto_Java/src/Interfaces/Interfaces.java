/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Other/File.java to edit this template
 */
package Interfaces;


/**
 *
 * @author el_dramas
 */
interface Interfaz1 {
    int CONSTANTE=33;
    
    String hazAlgo();
    default void ahoraSiHago(){
        System.out.println("No hago nada");
    }
    
}

interface Interfaz2{
    
    String hzAlgo2();
    default void ahoraSiHago(){
        System.out.println("ahora si hago por que quiero");
    }
}

class Test implements Interfaz1, Interfaz2{
    @Override
    public String hazAlgo(){
        return "hago algo";
    }
    @Override 
    public String hzAlgo2(){
        return "Puto";
    }
    
    @Override
    public void ahoraSiHago(){
        Interfaz1.super.ahoraSiHago();
        Interfaz2.super.ahoraSiHago();
        System.out.println(Interfaz1.CONSTANTE); //Es public static void
    }
    
    public static void main(String args[]){
        Test t = new Test();
        t.ahoraSiHago();
        System.out.println(t.hazAlgo());
        System.out.println(t.hzAlgo2());
    }
}


