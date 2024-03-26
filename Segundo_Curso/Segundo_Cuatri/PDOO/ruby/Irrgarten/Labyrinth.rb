#encoding: UTF-8

require_relative 'Dice'

module Irrgarten
    
    class Labyrinth

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
            @mtab=Array.new(nRows) {(Array.new(nCols))}
            @ltab=Array.new(nRows) {(Array.new(nCols))} 
            @ptab=Array.new(nRows) {(Array.new(nCols))}

            for i in 0...nRows do
                for j in 0...nCols do
                    @ltab[i][j] = @@EMPTY_BLOCK
                end
            end

            @ltab[exitRow][exitCol] = @@EXIT_CHAR
        end

        def spreadPlayers(players)
            #p3
        end

        def haveAWinner #bool

        end

        def to_s
            str="#{@nRows}, #{@nCols},#{@exitRow},#{@exitCol} \n"
            for i in 0...@nRows do
                for j in 0...@nCols do
                    str += "|" + @ltab + ""+ "|"
                end
            end
            return str
        end

        def addMonster(row,col,monster) #void
            if @ltab[row][col] == @@EMPTY_BLOCK then
                @ltab[row][col] = @@MONSTER_CHAR
                @mtab[row][col] = monster
            end

        end

        def putPlayer(direction, player) #monster
        end

        def addBlock(orientation,startRow,startcol, length)#void
        end

        def validMoves(row,col)#Directions[]
        end

        def posOK(row,col)#bool
            (0 <= row && row < @nRows && 0 <= col && col < @nCols)
        end

        def emptyPos(row,col)#bool
            @ltab[row][col] == @@EMPTY_BLOCK
        end

        def monsterPos(row,col)#bool
            @ltab[row][col] == @@MONSTER_CHAR
        end

        def exitPos(row,col)#bool
            @ltab[row][col] == @@EXIT_CHAR
        end

        def combatPos(row,col)#bool
            @ltab[row][col] == @@COMBAT_CHAR
        end

        def canSetOn(row,col)#bool
            posOK(row,col) && (emptyPos(row,col) || monsterPos(row,col) || exitPos(row,col))
        end

        def updateOldPos(row,col)#void
            if posOK(row, col) 
                if @ltab[row][col] == @@COMBAT_CHAR then
                    @ltab[row][col] = @@MONSTER_CHAR
                else 
                    @ltab[row][col] = @@EMPTY_BLOCK
                end
            end
            
        end

        def dir2Pos(row,col, direction) #int[]
            case direction
            when Directions::UP
                [row-1, col]
            when Directions::DOWN
                [row+1, col]
            when Directions::LEFT
                [row, col-1]
            when Directions::RIGHT
                [row, col+1]
            end
        end

        def randomEmptyPos #int[]
            begin
                row = Dice.randomPos(@nRows)
                col = Dice.randomPos(@nCols)
            end until emptyPos(row,col) 
            [row,col]
            
        end

        def putPlayer2D(oldRow, oldCol, row, col, player) #monster
        end

    end

end

