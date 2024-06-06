/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package Ordinarias.Lastra1920II.deepspace;
import java.util.ArrayList;
/**
 *
 * @author el_dramas
 */
public class SpaceAssets {
    private ArrayList<Object> assets = new ArrayList<>();
    
    public void add(Object o){
        assets.add(o);
    }
    
    public ArrayList<Object> getElements(){return assets;}
    
}
