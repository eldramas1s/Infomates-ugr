#encoding: UTF-8

require_relative 'Dice'
require_relative 'Directions'
require_relative 'FuzzyPlayer'
require_relative 'Orientation'

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

        # Inicializador
        # nRows->Numero de filas del laberinto
        # nCols->Numero de columnas del laberinto
        # exitRow->Fila de la salida
        # exitCol->Columna de la salida
        def initialize(nRows,nCols,exitRow,exitCol)
            @nRows=nRows
            @nCols=nCols
            @exitRow=exitRow
            @exitCol=exitCol
            @mtab=Array.new(nRows) {(Array.new(nCols))}     #Declaración de un array de arrays de nRows filas y nCols columnas
            @ltab=Array.new(nRows) {(Array.new(nCols))}
            @ptab=Array.new(nRows) {(Array.new(nCols))}     # Se inicializan a nil por defecto

            for i in 0...nRows do
                for j in 0...nCols do
                    @ltab[i][j] = @@EMPTY_BLOCK
                end
            end

            @ltab[exitRow][exitCol] = @@EXIT_CHAR
        end

        # Spawnea los jugadores en el laberinto de forma aleatoria, solo aparecen en bloques vacios
        # Delega en PutPlayer2D
        def spreadPlayers(players)
            for i in 0..players.size-1 do
                pos = randomEmptyPos
                putPlayer2D(@@INVALID_POS,@@INVALID_POS,pos[@@ROW],pos[@@COL],players[i])
            end
        end

        # True -> Hay ganador
        # False -> No hay ganador
        def haveAWinner #bool
            @ptab[@exitRow][@exitCol] != nil
        end

        def to_s
            str="[#{@nRows}x#{@nCols}],(#{@exitRow},#{@exitCol}) \n"
            for i in 0...@nRows do
                for j in 0...@nCols do
                    str += "|" + @ltab[i][j].to_s + "|"
                end
                str +="\n"
            end
            return str
        end

        # Añade un monstruo en una posicion del laberinto, lo añade en el laberinto como una M y en la matriz de monstruos
        # row -> fila del monstruo
        # col -> columna del monstruo
        # monster -> monstruo a añadir
        def addMonster(row,col,monster) #void
            if @ltab[row][col] == @@EMPTY_BLOCK then
                @ltab[row][col] = @@MONSTER_CHAR
                @mtab[row][col] = monster
            end
        end

        # Mueve al jugador a una casilla adyacente
        # direction -> direccion de movimiento
        # player -> jugador a mover
        # return monster -> si hay un monstruo en la posicion de llegada devuelve ese monstruo, si no lo hay devuelve nil
        # post -> La casilla a la que se mueva no tiene por qué ser la que se busca
        def putPlayer(direction, player) #monster
            oldRow = player.row
            oldCol = player.col
            newPos = dir2Pos(oldRow,oldCol,direction)
            monster = putPlayer2D(oldRow,oldCol,newPos[@@ROW],newPos[@@COL],player)
            monster
        end

        # Añade un bloque o conjunto de bloque segun:
        # orientation -> orientacion que se sigue para añadir los bloques
        # startRow -> fila de inicio
        # startCol -> columna de inicio
        # length -> longitud del conjunto de bloques a añadir
        def addBlock(orientation,startRow,startCol, length)#void
            if orientation == Orientation::VERTICAL then
                incRow = 1
                incCol = 0
            else
                incRow = 0
                incCol = 1
            end
            row = startRow
            col = startCol

            while posOK(row,col) && emptyPos(row,col) && length > 0
                @ltab[row][col] = @@BLOCK_CHAR
                length -= 1
                row += incRow
                col += incCol
            end

        end

        # Devuelve un array con las direcciones de movimientos posibles de un jugador
        # row -> fila del jugador
        # col -> columna del jugador
        # output -> Array con las direcciones posibles
        def validMoves(row,col)#Directions[]
            output = Array.new
            if(canStepOn(row+1,col))then
                output.append(Directions::DOWN)
            end

            if(canStepOn(row-1,col))then
                output.append(Directions::UP)
            end

            if(canStepOn(row,col+1))then
                output.append(Directions::RIGHT)
            end

            if(canStepOn(row,col-1))then
                output.append(Directions::LEFT)
            end
            output
        end

        def switchPlayer(player)
            @ptab[player.row][player.col] = player
            @ltab[player.row][player.col] = player.number
        end

	private
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

        def canStepOn(row,col)#bool
            posOK(row,col) && (emptyPos(row,col) || monsterPos(row,col) || exitPos(row,col))
        end

        # Actualiza la posicion del tablero despues de combate
        # row -> fila
        # col -> columna
        def updateOldPos(row,col)#void
            if posOK(row, col)
                if @ltab[row][col] == @@COMBAT_CHAR then
                    @ltab[row][col] = @@MONSTER_CHAR
                else
                    @ltab[row][col] = @@EMPTY_BLOCK
                end
            end
        end

        # Traduce una direccion a una coordenada
        # row -> fila
        # col -> columna
        # direction -> direccion de movimiento
        # devuelve un array de dos enteros que representa la posicion
        def dir2Pos(row,col, direction) #int[]
            case direction      #switch
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

        # Busca una posicion vacia de forma aleatoria en el tablero
        # Devuelve una posicion en un array de dos posiciones
        def randomEmptyPos #int[]
            begin
                row = Dice.randomPos(@nRows)
                col = Dice.randomPos(@nCols)
            end until emptyPos(row,col)
            [row,col]

        end

        # Mueve el jugador y procura dejar el tablero en estado consistente
        # oldRow -> Fila inicial
        # oldCol -> Columna inicial
        # row -> nueva fila
        # col -> nueva columna
        # player -> nuevo jugador
        # Devuelve un monstruo si lo hay, si no devuelve nil
        def putPlayer2D(oldRow, oldCol, row, col, player) #monster
            output = nil
            if canStepOn(row,col) then
                if posOK(oldRow,oldCol) then
                    p = @ptab[oldRow][oldCol]
                    if p == player then
                        updateOldPos(oldRow,oldCol)
                        @ptab[oldRow][oldCol] = nil
                    end
                end

                monsterPos = monsterPos(row,col)
                if monsterPos then
                    @ltab[row][col] = @@COMBAT_CHAR
                    output = @mtab[row][col]
                else
                    number = player.number
                    @ltab[row][col] = number
                end
                @ptab[row][col] = player
                player.setPos(row,col)
            end
            output
        end

    end#class
end#module
