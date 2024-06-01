/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Other/File.java to edit this template
 */
package Clases_Parametrizables;

/**
 *
 * @author el_dramas
 */
abstract class Estudiantes {

    void Estudia(){
        System.out.println("Estudio");
    }
    
}

class Primario extends Estudiantes{
    
    @Override
    void Estudia(){
        super.Estudia();
        System.out.println("mates");
    }
    
}

class Secundario extends Estudiantes{
    //@Override
    //void Estudia(){
    //    super.Estudia();
    //    System.out.println("Porros");
    //}
}

class Curso<T extends Estudiantes>{
    
    void MatricularEstudiante( T e){
        e.Estudia();
    }
    
    /**
     * @param args the command line arguments
     */
    public static void main(String args[]) {
        Curso<Estudiantes> curso=new Curso();
        //Curso<Secundario> curso=new Curso();
        //Curso<Primario> curso=new Curso();
        
        curso.MatricularEstudiante(new Secundario());
        curso.MatricularEstudiante(new Primario());
    }
}