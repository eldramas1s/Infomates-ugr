module Irrgarten
  class LabyrinthCharacter
    @@INVALID_POS = -1    # Se hereda

    # Inicializador de LabyrinthCharacter, no tiene numero pues los monstruos no se enumeran.
    # Si no hacemos uso de setStats que provoca que se ejecute el código de este archivo, en un hijo se ejecutará el initialize del hijo por la ligadura dinamica.
    def initialize(name,intelligence,strength,health)
      setStats(name,intelligence,strength,health)
      @row = @@INVALID_POS
      @col = @@INVALID_POS
    end

    #Creado porque si se sobrecarga initialize no se puede usar de forma segura
    #De esta forma podemos en el cloner delegar aqui. Además evita repeticion de codigo
    def setStats(name, intelligence,strength,health)
      @name = name
      @intelligence = intelligence.to_f
      @strength = strength.to_f
      @health = health
    end
    private :setStats

    attr_reader :name
    attr_reader :row
    attr_reader :col

    # Constructor de copia de un Player
    # other -> Personaje del que copiar
    def cloner(other)
      setStats(other.name,other.intelligence, other.strength,other.health)
      @row = other.row
      @col = other.col
    end

    # Comprueba si un jugador esta muerto
    # return -> True -> muerto
    #           False -> vivo
    def dead
      @health<=0
    end

    protected
      # getter intelligence
      def intelligence
        @intelligence
      end

      # getter strength
      def strength
        @strength
      end

      # getter health
      def health
        @health
      end

      # setter health
      # health -> nuevo valor de vida
      def health=(health)
        @health = health
      end

      # Daña a un LabyrinthCharacter
      def gotWounded
        @health -= 1
      end
    public

      # setter row y col
      # row -> fila nueva
      # col -> columna nueva
      def setPos(row,col)
        if (row >= 0) && (col >= 0) then
          @row = row
          @col = col
        end
      end

      # Concatena la informacion de un LabyrinthCharacter
      # return -> cadena con la informacion
      def to_s
        "[#{@name}, #{@health} HP, #{@intelligence} IP, #{@strength} SP,(#{@row},#{@col})]\n"
      end

  end#class
end#module
