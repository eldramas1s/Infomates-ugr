#encoding: UTF-8

module Irrgarten
    
    class Labyrinth
    static private int INVALID_POS=-1;
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

    @@INVALID_POS=-1
    @@BLOCK_CHAR='X'
    @@EMPTY_BLOCK='-'
    @@MONSTER_CHAR='M'
    @@COMBAT_CHAR='C'
    @@EXIT_CHAR='E'
    @@ROW=0
    @@COL=1

        def initialize(nRows,nCols,exitRow,exitCol)
            @nRows=nRows
            @nCols=nCols
            @exitRow=exitRow
            @exitCol=exitCol
            @mtab=array.new(nRows) {(array.new(nCols))}
            @ltab=array.new(nRows) {(array.new(nCols))} 
            @ptab=array.new(nRows) {(array.new(nCols))}

            for i in 0..nrows do
                for j in 0..ncols do
                    @ltab=@@EMPTY_BLOCK
                end
            end
        end

        def spreadPlayers(players)
            #p3
        end

        def haveAWinner

        end

        def to_s
            str="#{@nRows}, #{@nCols},#{@exitRow},#{exitCol} \n"
            for i in 0..@nRows do
                for j in 0..@nCols do
                    str += "|" + @ltab + ""+ "|"
        end

    
    end
    
end
