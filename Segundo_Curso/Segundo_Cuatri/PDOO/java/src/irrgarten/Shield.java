/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package irrgarten;

/**
 *
 * @author el_dramas
 */
public class Shield {
    private float protection;
    private int uses;
    
    Shield (float defense, int durability ){
        protection = defense;
        uses = durability;
    }
    
    public float protect(){
        float prt_val=0;
        if(uses>0){
            prt_val=protection;
            uses--;
        }
        return prt_val;
    }

    public String toString(){
        return "S[" + protection + "," + uses + "]";
    }
}
