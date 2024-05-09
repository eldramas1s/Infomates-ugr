/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package irrgarten;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Iterator;

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
    
    /**
     * Construye un laberinto
     * @param nRows Numero de filas
     * @param nCols Numero de columnas
     * @param exitRow Fila en la que poner la salida
     * @param exitCol Columna en la que poner la salida
     */
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
                setBlock(i,j,EMPTY_BLOCK);
                setMonsterAt(i,j,null);
                setPlayerAt(i,j,null);
            }
        }
        
        if(this.posOK(exitRow, exitCol))
            setBlock(exitRow, exitCol, EXIT_CHAR);
        else
            setBlock(0,0,EXIT_CHAR);; 
        
    }
    
    /**
     * Reparte los jugadores por el tablero
     * @param players Los jugadores a repartir
     */
    public void spreadPlayers(ArrayList<Player> players){
        for (Player player : players) {
            ArrayList<Integer> newPos = randomEmptyPos();
            //System.out.println(newPos);
            putPlayer2D(INVALID_POS, INVALID_POS, newPos.get(ROW), newPos.get(COL), player);
        }
    }
    
    /**
     * Comprueba si hay un jugador en la casilla de salida
     * @return True si hay un jugador
     */
    public boolean haveAWinner(){
        return getPlayerAt(exitRow, exitCol) != null;
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
    
    /**
     * Añade un monstruo a la posicion (row, col)
     * @param row fila
     * @param col columna
     * @param monster El mountruo a añadir
     */
    public void addMonster(int row, int col, Monster monster){
        if(this.posOK(row, col)&&(getBlock(row, col)==EMPTY_BLOCK) && !(this.exitPos(row, col))){
            setMonsterAt(row,col,monster);
            setBlock(row,col,MONSTER_CHAR);
            monster.setPos(row, col);
        }     
           
    }
    
    /**
     * Mueve el jugador a una casilla adyacente
     * @param direction Direccion en la que intentar ponerlo
     * @param player El jugador a mover
     * @return Un monstruo si se lo encuentra en la casilla, si no devuelve null
     */
    public Monster putPlayer(Directions direction, Player player){
        int oldRow = player.getRow();
        int oldCol = player.getCol();
        ArrayList<Integer> newPos = dir2Pos(oldRow, oldCol, direction);
        return putPlayer2D(oldRow, oldCol, newPos.get(ROW), newPos.get(COL), player);
    }
    
    /**
     * Añade bloques hasta encontrarse con un obstaculo o llegar al numero deseado
     * @param orientation Si ponerlos en horizontal o vertical
     * @param startRow Fila en la que poner el primer bloque
     * @param startCol Columna en la que poner el primer bloque
     * @param length Numero de bloques a poner
     */
    public void addBlock(Orientation orientation, int startRow, int startCol, int length){
        int incRow=0, incCol=0;
        if(orientation == Orientation.VERTICAL){
            incRow++;
        } else{
            incCol++;
        }
        int row = startRow, col = startCol;
        while( posOK(row,col) && emptyPos(row, col) && length > 0){
            setBlock(row, col, BLOCK_CHAR);
            length--;
            row += incRow;
            col += incCol;
        }

    }
    
    /**
     * Comprueba que movimientos son válidos
     * @param row la fila
     * @param col la columna
     * @return Los movimientos válidos
     */
    public ArrayList<Directions> validMoves(int row, int col){

        ArrayList<Directions> directions = new ArrayList<>(Arrays.asList(Directions.DOWN, Directions.UP, Directions.RIGHT, Directions.LEFT)); //Inicializa la lista con los valores pasados por argumentos
        Iterator<Directions> it = directions.listIterator();  //IMPORTANTE
        
        //Depende del número de direcciones
        while(it.hasNext()){
            ArrayList<Integer> posToCheck = dir2Pos(row, col, it.next());
            if(!canStepOn(posToCheck.get(ROW),posToCheck.get(COL))){
                it.remove();  
            }
        }
        return directions;

    }

    public void turnFuzzy(FuzzyPlayer player){
        setPlayerAt(player.getRow(),player.getCol(), player);
    }
    
    /**
     * Comprueba si la posicion esta dentro del laberinto
     * @param row la fila
     * @param col la columna
     * @return True si esta dentro
     */
    private boolean posOK(int row, int col){
        boolean dentroRow = (0 <= row) && (row<this.nRows);
        boolean dentroCol = (0 <= col) && (col<this.nCols);
        return (dentroRow && dentroCol);
    }
    
    /**
     * Comprueba si una posición esta vacia
     * @param row fila 
     * @param col columna
     * @return True si la posición esta vacia
     */
    private boolean emptyPos(int row, int col){
        return (this.posOK(row,col))&&(getBlock(row, col) == EMPTY_BLOCK);
    }
    
    private boolean monsterPos(int row, int col){
        return (this.posOK(row,col))&&(getBlock(row, col) == MONSTER_CHAR);
    }
    
    private boolean exitPos(int row, int col){
        return (this.posOK(row,col))&&(getBlock(row, col)==EXIT_CHAR);
    }
    
    private boolean combatPos(int row, int col){
        return (this.posOK(row,col))&&(getBlock(row, col) == COMBAT_CHAR);
    }
    
    private boolean canStepOn(int row, int col){
        return (this.posOK(row, col))&& ((this.exitPos(row, col))||(this.emptyPos(row, col)) || (this.monsterPos(row, col)));
    }
    
    /**
     * Actualiza una casilla tras moverse un jugador
     * @param row fila en la que estaba el jugador
     * @param col columna en la que estaba el jugador
     */
    private void updateOldPos(int row, int col){
        if(this.posOK(row, col)){
            if(this.combatPos(row, col))
                setBlock(row, col, MONSTER_CHAR);
            else
                setBlock(row, col, EMPTY_BLOCK);
        }
        
    }
    
    /**
     * Traduce una dirección a una coordenada
     * @param row fila en la que esta el jugador
     * @param col columna en la que esta el jugador
     * @param direction direccion a la que mover
     * @return la nueva posicion
     */
    private ArrayList<Integer> dir2Pos(int row, int col, Directions direction){
        int nextRow=row;
        int nextCol=col;
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
        
        
        ArrayList<Integer> position = new ArrayList<Integer>();
        position.add(nextRow); //Añade en pos ROW = 0
        position.add(nextCol);  //Añade en pos COL = 1
        return position;
    }
    
    /**
     * Busca una posición vacia en el tablero
     * @return la posición que encuentre primero
     */
    private ArrayList<Integer> randomEmptyPos(){
        Integer row=INVALID_POS,col=INVALID_POS;
        
        while(!(this.posOK(row, col) && this.emptyPos(row, col))){
            row=Dice.randomPos(nRows);
            col=Dice.randomPos(nCols);
        }
        
        ArrayList<Integer> position= new ArrayList<Integer>();
        position.add(ROW,row);
        position.add(COL,col);
        return position;
    }
    
    /**
     * Mueve al jugador y procura dejar el tablero en estado consistente
     * @param oldRow fila antigua
     * @param oldCol columna antigua
     * @param row fila nueva
     * @param col columna nueva
     * @param player El jugador que mover
     * @return Un monstruo si al mover al jugador encuentra a uno, null si no
     */
    private Monster putPlayer2D(int oldRow, int oldCol, int row, int col, Player player){
        Monster output = null;
        if(canStepOn(row, col)){
            if(posOK(oldRow, oldCol)){
                Player p = getPlayerAt(oldRow, oldCol);
                if(p == player){
                    updateOldPos(oldRow, oldCol);
                    setPlayerAt(oldRow, oldCol, null);
                }
            }

            if(monsterPos(row, col)){
                setBlock(row, col, COMBAT_CHAR);
                output = getMonsterAt(row, col);
            } else{
                setBlock(row, col, player.getNumber());
            }

            setPlayerAt(row, col, player);
            player.setPos(row, col);            
        }
        return output;
    }
    
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

    private void setBlock(int row, int col, char bloque){
        ltab[row][col] = bloque;
    }

    private char getBlock(int row, int col){
        return ltab[row][col];
    }

    private void setMonsterAt(int row, int col, Monster monster){
        mtab[row][col] = monster;
    }

    private Monster getMonsterAt(int row, int col){
        return mtab[row][col];
    }

    
    private void setPlayerAt(int row, int col, Player player){
        ptab[row][col] = player;
    }

    private Player getPlayerAt(int row, int col){
        return ptab[row][col];
    }

}