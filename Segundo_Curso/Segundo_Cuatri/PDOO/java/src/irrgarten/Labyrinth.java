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
    static private final int INVALID_POS=-1;
    static private final char BLOCK_CHAR = 'X';
    static private final char EMPTY_BLOCK = '-';
    static private final char MONSTER_CHAR = 'M';
    static private final char COMBAT_CHAR = 'C';
    static private final char EXIT_CHAR = 'E';
    static private final int ROW = 0;
    static private final int COL = 1;
    
    private int nRows;
    private int nCols;
    private int exitRow;
    private int exitCol;
    private Monster mtab[][];
    private char ltab[][];
    private Player ptab[][];
    
    //TODO: Crear un laberinto especifico
    public Labyrinth(int nRows, int nCols, int exitRow, int exitCol){
        this.nRows = nRows;
        this.nCols = nCols;
        this.exitCol = exitCol;
        this.exitRow = exitRow;
        
        mtab = new Monster[nRows][nCols];
        ltab = new char[nRows][nCols];
        ptab = new Player[nRows][nCols];
        
        for (int i=0; i<nRows; ++i){
            for(int j=0; j<nCols; ++j){
                ltab[i][j]=EMPTY_BLOCK;
                mtab[i][j]=null;
                ptab[i][j]=null;
            }
        }
        
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
    
    public String toString(){
        String cad = "Labyrinth: \n";
        
        cad += this.convertToString(ltab, nRows, nCols) + "\n\n";
        
        //cad += "Monsters: \n";
        
        //cad += this.convertToString(mtab, nRows, nCols) + "\n\n";
        
        //cad += "Players: \n";
        
        //cad += this.convertToString(ptab, nRows, nCols) + "\n\n";
        
        return cad;
    }
    
    public void addMonster(int row, int col, Monster monster){
        if(this.posOK(row, col)&&(ltab[row][col]==EMPTY_BLOCK) && !(this.exitPos(row, col))){
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
        return (this.posOK(row,col))&&(ltab[row][col] == EMPTY_BLOCK);
    }
    
    private boolean monsterPos(int row, int col){
        return (this.posOK(row,col))&&(ltab[row][col] == MONSTER_CHAR);
    }
    
    private boolean exitPos(int row, int col){
        return (this.posOK(row,col))&&(ltab[row][col]==EXIT_CHAR);
    }
    
    private boolean combatPos(int row, int col){
        return (this.posOK(row,col))&&(ltab[row][col] == COMBAT_CHAR);
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
        }
        
        
        ArrayList<Integer> position = new ArrayList<Integer>(2);
        position.add(ROW, nextRow);
        position.add(COL,nextCol);
        return position;
    }
    
    private ArrayList<Integer> randomEmptyPos(){
        Integer row=INVALID_POS,col=INVALID_POS;
        
        while(!this.posOK(row, col) && !this.emptyPos(row, col)){
            row=Dice.randomPos(nRows);
            col=Dice.randomPos(nCols);
        }
        
        ArrayList<Integer> position= new ArrayList<Integer>(2);
        position.add(ROW,row);
        position.add(COL,col);
        return position;
    }
    
    private Monster putPlayer2D(int oldRow, int oldCol, int row, int col, Player player){
        return null;
    }
    
    //TODO: Templates
    private String convertToString(char matrix[][], int rows, int cols){
        String cad="";
        
        for (int i=0; i<rows; ++i){
            
            if(i==0){
                for (int j=0; j<3*cols; ++j)
                    cad +="=";
                cad += "\n";
            }
            for (int j=0; j<cols; ++j)
                cad += "|"+matrix[i][j]+"|";
            
            cad += "\n";
            if(i==rows-1){
                for(int j=0; j<3*cols; ++j)
                    cad+="=";
                cad += "\n";
            }
        }
        return cad;
    }

}