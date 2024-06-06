/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Other/File.java to edit this template
 */
package Herencia_Clases;

/**
 *
 * @author el_dramas
 */
public class Ejemplo {

    /**
     * @param args the command line arguments
     */
    public static void main(String args[]) {
        System.out.println(Padre.DECLASE);
        System.out.println(Hija.DECLASE);
        System.out.println(Nieta.DECLASE); //Los atributos de clase se heredan
        System.out.println(Padre.getDECLASE());
        System.out.println(Hija.getDECLASE());
        System.out.println(Nieta.getDECLASE());
        
    }
}

class Padre{
    public static final int DECLASE = 1;
    public static int getDECLASE(){return DECLASE;}
    public void tienePapa(){}
}

class Hija extends Padre{
    public static final int DECLASE = 2;
}

class Nieta extends Hija{
    public static int getDECLASE(){
        //super.getDECLASE();  //NO se puede, es estatico
        return DECLASE;
    }
    
    @Override                   //Una hija puede no sobreescribirlo y la nieta si.
    public void tienePapa(){}
}