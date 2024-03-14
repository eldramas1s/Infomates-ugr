/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package irrgarten;

/**
 *
 * @author el_dramas
 */
public class Labyrinth {
    static private char BLOCK_CHAR = 'X';
    static private char EMPTY_BLOCK = '-';
    static private char MONSTER_CHAR = 'M';
    static private char COMBAT_CHAR = 'C';
    static private char EXIT_CHAR = 'E';
    static private int ROW = 0;
    static private int COL = 0;
    private int nRows;
    private int nCols;
    private int exitRow;
    private int exitCol;
    
    
    public Labyrinth(int nRows, int nCols, int exitRow, int exitCol){
        this.nRows = nRows;
        this.nCols = nCols;
        this.exitCol = exitCol;
        this.exitRow = exitRow;
    }
    
    
}
