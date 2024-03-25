/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package irrgarten;

/**
 *
 * @author airam
 */
public class TestP1 {
    public static void main(String [] args){
        String name="Pepo";
        float intelligence=15,strength = 10;
        
        Monster monster = new Monster(name, intelligence, strength);
<<<<<<< HEAD
        System.out.println(monster.attack());
=======
        
        System.out.println(monster.toString());
        
        System.out.println(monster.dead());
        
        System.out.println(monster.attack());
        
        monster.setPos(0,5);
        
        System.out.println(monster.toString());
        
        monster.matar();
        
        //System.out.println(monster.attack());
        
=======
        System.out.println(monster.attack());
>>>>>>> PDOO
>>>>>>> main
    }
}
