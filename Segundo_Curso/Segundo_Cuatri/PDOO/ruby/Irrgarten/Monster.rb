
require_relative 'Dice'

module Monster  

    class Monster

        #Vida inicial de un monstruo
        @@INITIAL_HEALTH = 5
        #Posicion que consideramos inválida. Si una fila o columna
        #es menor o igual a INVALID_POS, no es válido dicho estado
        @@INVALID_POS = -1

        def initialize(name, intelligence, strength)
            @name = name                        #nombre del monstruo
            @intelligence = intelligence.to_f   #inteligencia del monstruo
            @strength = strength.to_f           #fuerza del monstruo
            @health = @@INITIAL_HEALTH          #vida del monstruo
            @row = @@INVALID_POS                #Fila en la que está el monstruo en un tablero
            @col = @@INVALID_POS                #Columna en la que esta el mounstruo en un tablero
        end

        #Comprueba si un moustruo esta muerto
        def dead
            @health <= 0 
        end

        #Calcula la intensidad de ataque del monstruo
        def attack
            Dice::Dice.intensity(@strength)
        end

        #Reposiciona al monstruo
        def setPos(row, col) 
            @row = row
            @col = col
            # en java es void, aqui simplemente ignoramos lo devuelto
        end
        
        #Devuelve el estado del monstruo en forma de cadena
        def to_s
            "M[#{@name},#{@intelligence},#{@strength},#{@health},({#{@row},#{@col}})]"
        end

        #Daña al monstruo
        def gotWounded
            @health -= 1
        end

        #Calclua como se defiende el monstruo
        def defend
            #nos dicen que hacer en la práctica 3
        end


        private :gotWounded
    end

end