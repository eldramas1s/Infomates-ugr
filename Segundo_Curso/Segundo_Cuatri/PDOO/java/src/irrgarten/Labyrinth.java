/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package irrgarten;
import java.util.ArrayList;
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
    static private int COL = 1;
    private int nRows;
    private int nCols;
    private int exitRow;
    private int exitCol;
    private Monster mtab[][];
    private char ltab[][];
    private Player ptab[][];
    
    public Labyrinth(int nRows, int nCols, int exitRow, int exitCol){
        this.nRows = nRows;
        this.nCols = nCols;
        this.exitCol = exitCol;
        this.exitRow = exitRow;
        
        //TODO: Algo no me cuadra sobre las dimensiones
        for (int i=0; i<nRows; ++i){
            for(int j=0; j<nCols; ++j){
                ltab[i][j]=EMPTY_BLOCK;
                mtab[i][j]=null;
                ptab[i][j]=null;
            }
        }
        
        //TODO: ¿Poner como constantes?
        if(this.posOK(exitRow, exitCol))
            ltab[exitRow][exitCol] = EXIT_CHAR;
        else
            ltab[this.nRows-1][this.nCols-2] = EXIT_CHAR;
        
    }
    
    public void spreadPlayers(ArrayList<Player> players){
        
    }
    
    public boolean haveAWinner(){
        return ptab[this.exitRow][this.exitCol]!=null;
    }
    
    //TODO: implementar(copypaste de ruby)
    public String toString(){
        return "luego";
    }
    
    public void addMonster(int row, int col, Monster monster){
        if(this.posOK(row, col)&&(ltab[row][col]==EMPTY_BLOCK)){
            mtab[row][col] = monster;
            ltab[row][col] = MONSTER_CHAR;
            monster.setPos(row, col);
        }
    }
    
    public Monster putPlayer(Directions direction, Player player){
        return null;
    }
    
    public void addBlock(Orientation orientation, int starRow, int startCol, int length){
        
    }
    
    public ArrayList<Directions> validMoves(int row, int col){
        return null;
    }
    
    private boolean posOK(int row, int col){
        boolean dentroRow = (0 <= row) && (row<this.nRows);
        boolean dentroCol = (0 <= col) && (col<this.nCols);
        return (dentroRow && dentroCol);
    }
    
    private boolean emptyPos(int row, int col){
        return (ltab[row][col] == EMPTY_BLOCK);
    }
    
    private boolean monsterPos(int row, int col){
        return (ltab[row][col] == MONSTER_CHAR);
    }
    
    private boolean exitPos(int row, int col){
        return (row==exitRow)&&(col==exitCol);
        //return (ltab[row][col]==EXIT_CHAR;
    }
    
    private boolean combatPos(int row, int col){
        return ltab[row][col] == COMBAT_CHAR;
    }
    
    private boolean canStepOn(int row, int col){
        return (this.posOK(row, col))&&(this.exitPos(row, col))&&(this.emptyPos(row, col)) && (this.monsterPos(row, col));
    }
    
    private void updateOldPos(int row, int col){
        if(this.posOK(row, col)){
            if(this.combatPos(row, col))
                ltab[row][col] = MONSTER_CHAR;
            else
                ltab[row][col] = EMPTY_BLOCK;
        }
        
    }
    
    //TODO: Devolver arrays java
    private ArrayList<Integer> dir2Pos(int row, int col, Directions direction){
        Integer nextRow=row;
        Integer nextCol=col;
        
        switch (direction){
            case LEFT:
                nextCol--;
                break;
            case RIGHT:
                nextCol++;
                break;
            case UP:
                nextRow--;
                break;
            case DOWN:
                nextRow++;
                break;
            default:
                    break;
        }
        
        ArrayList<Integer> position = new ArrayList<Integer>();
        position.clear();
        position.add(nextRow);
        position.add(nextCol);
        return position;
        
        
    }
    
    private ArrayList<Integer> randomEmptyPos(){
        return null;
    }
    
    private Monster putPlayer2D(int oldRow, int oldCol, int row, int col, Player player){
        return null;
    }
}
