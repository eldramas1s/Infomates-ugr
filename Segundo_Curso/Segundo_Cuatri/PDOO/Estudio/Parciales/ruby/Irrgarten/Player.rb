#encoding: UTF-8

require_relative 'Dice'
require_relative 'Weapon'
require_relative 'Shield'
require_relative 'Directions'

module Irrgarten

    class Player
        @@DEFAULT_NAME = "Player #"
        @@INVALID_POS = -1

        @@MAX_WEAPONS = 2
        @@MAX_SHIELDS = 3
        @@INITIAL_HEALTH = 10
        @@HITS2LOSE = 3

        # Inicializador
        # number -> Numero de jugador
        # intelligence -> Inteligencia del jugador
        # strength -> Fuerza del jugador
        def initialize(number,intelligence,strength)
            @name = @@DEFAULT_NAME + number.to_s #Por si no se pasa una cadena
            @number = number
            @intelligence = intelligence
            @strength = strength
            @health = @@INITIAL_HEALTH
            @row = @@INVALID_POS
            @col = @@INVALID_POS
            @consecutiveHits = 0
            @weapons = Array.new        # Declara un array de objetos, tambien vale []
            @shields = Array.new
        end

        # Resucita a un jugador
	    def resurrect
            @weapons.clear()
            @shields.clear()
            @health = @@INITIAL_HEALTH
            @consecutiveHits = 0
        end

        #getter row, col, number
        attr_reader :row
        attr_reader :col
        attr_reader :number

        # Modificador de la posicion de un jugador
        # row -> fila nueva
        # col -> columna nueva
        # @pre la posicion debe estar dentro del tablero
        def setPos(row,col)
            if row >= 0 && col >= 0 then
                @row = row
                @col = col
            end
        end

        # Comprueba si el jugador esta muerto
        def dead
            @health <= 0
        end

        # Mueve al jugador a la posicion indicada por direction si esta en validMoves
        # direction -> direccion de movimiento
        # validMoves -> movimientos validos
        # si el movimiento realizado no esta en los validos se mueve uno aleatorio dentro de los validos
	    def move(direction, validMoves)
            size = validMoves.length
            contained = find(direction,validMoves)      # existe la funcion include?()
            if (size > 0) && !contained then
                firstElement = validMoves[0]
                return firstElement
            else
                return direction
            end
        end

        # Calcula el ataque de un jugador
	    def attack
            @strength + sumWeapons
        end

        # Calcula la defensa de un jugador y maneja la recepcion de un golpe.
	    def defend(receivedAttack)
            manageHit(receivedAttack)
        end

        # Asignar los recursos que obtiene el jugador en una pelea si gana
        # Puede añadir: vida, armas y escudos
        def receiveReward
            wReward = Dice.weaponsReward
            sReward = Dice.shieldsReward
            for i in 0..wReward do
                wnew = newWeapon
                receiveWeapon(wnew)
            end
            for i in 0..sReward do
                snew = newShield
                receiveShield(snew)
            end
            extraHealth = Dice.healthReward
            @health += extraHealth
        end

	    def to_s
            str="\t#{@name}, #{@health} HP, #{@intelligence} IP, #{@strength} SP\n"
            str+= "\t\tWeapons: ["
            str += @weapons[0].to_s unless @weapons.size==0

            for i in 1...@weapons.length do         # for element in @weapons
                str += ", " + @weapons[i].to_s
            end
            str+= "]\n"
            str+= "\t\tShields: ["
            str += @shields[0].to_s unless @shields.size==0

            for i in 1...@shields.size do
                str += ", " + @shields[i].to_s
            end
            str += "]\n"
            str

        end

	private

        # Encargado de obtener la probabilidad de recibir un nuevo arma y borra las que tomen probabilidad de borrado igual a true (wi.discard())
        # Añade un arma si hay huecos en la mochila del jugador
        def receiveWeapon(w)
            i=0
            while i<@weapons.size
                wi=@weapons[i]
                if(wi.discard()) then
                        @weapons.shift      # Extrae los n primeros elementos del array, sin args devuelve el primero
                else
                    i+=1
                end
            end
            size = @weapons.size
            if size<@@MAX_WEAPONS then
                w = newWeapon
                @weapons.append(w)          # Añade un elemento al final del array, similar a <<
            end
        end
        # Encargado de obtener la probabilidad de recibir un nuevo escudo y borra las que tomen probabilidad de borrado igual a true (wi.discard())
        # Añade un escudo si hay huecos en la mochila del jugador
        def receiveShield(s)
            i=0
            while i<@shields.length
                si=@shields[i]
                if(si.discard) then
                    @shields.shift
                else
		            i+=1
		    end
	    end
            size = @shields.length
            if(size<@@MAX_SHIELDS) then
                s = newShield
                @shields.append(s)
            end
        end

        # Gesstiona los golpes que recibe el jugador
        # receivedAttack -> valor del ataque recibido
        # return -> lose
        #               True -> Jugador muere
        #               False -> No muere
        def manageHit(receivedAttack)
            defense=defensiveEnergy
            if defense<receivedAttack then
                gotWounded
                incConsecutiveHits
            else
                resetHits
            end
            lose=true
            if (@consecutiveHits == @@HITS2LOSE)||(dead()) then
                resetHits
            else
                lose=false
            end
            return lose
        end

        # Crea un nuevo arma y lo devuelve
        def newWeapon
            Weapon.new(Dice.weaponPower, Dice.usesLeft)
        end

        # Crea un nuevo escudo y lo devuelve
        def newShield
            Shield.new(Dice.shieldPower, Dice.usesLeft)
        end

        # Devuelve la enegia defensiva
        def defensiveEnergy
            @intelligence + sumShields
        end

        # Resetea los hits
        def resetHits
            @consecutiveHits = 0
        end

        # Decrementa el valor de health
        def gotWounded
            @health -= 1
        end

        # Incrementa los hits consecutivos
        def incConsecutiveHits
            @consecutiveHits +=1
        end

        # Suma y devuelve el valor de ataque de todas las armas
        def sumWeapons
            sum=0
            for i in 0...@weapons.size do   #rango exclusivo
                sum += @weapons[i].attack
            end
            sum
        end

        # Suma y devuelve el valor de defensa de todos los escudos
        def sumShields
            sum=0
            for i in 0..@shields.size-1 do  # rango inclusivo
                sum += @shields[i].protect
            end
            sum
        end

        # Busca un elemento en un array
        # Se usa para encontrar una direccion en validMoves
        # element -> Elemento a buscar
        # array -> Array donde buscar
        # True -> Encontrado
        # False -> No encontrado
        def find(element,array)
            found = false
            i = 0
            while !found && (i<array.size)
                if array[i] == element then
                    found = true
                else
                    i += 1
                end
            end
            found
        end
    end #class
end #module
