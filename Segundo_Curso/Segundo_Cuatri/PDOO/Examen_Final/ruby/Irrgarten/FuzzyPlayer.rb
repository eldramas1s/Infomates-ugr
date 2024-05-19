require_relative 'Dice'
require_relative 'Player'

module Irrgarten

  class FuzzyPlayer < Player
    @@FUZZY = "Fuzzy"

    # Pseudo-constructor de copia. Como en Ruby ni se pueden
    # sobrecargar es el único que se proporciona
    def initialize(player)
        cloner(player)
    end

    # Se encarga de realizar el movimiento de un FuzzyPlayer
    # Depende del azar y la direccion preferente es filtrada por el metodo move de
    # Player.
    # direction -> direccion preferente
    # validMoves -> array de movimientos validos
    # return -> direccion de movimiento ya calculada
    def move(direction,validMoves)
      direction = Dice.nextStep(super,validMoves,self.intelligence)
      super(direction,validMoves)
    end

    # Ataque de un FuzzyPlayer
    # return -> valor que representa la fuerza de ataque
    def attack
      sumWeapons + Dice.intensity(self.strength)
    end

    # Concatena la informacion de un FuzzyPlayer
    # return -> cadena con la informacion
    def to_s
      @@FUZZY + super
    end

  protected
    # Intensidad defensiva de un FuzzyPlayer
    # return -> Valor que representa la intensidad defensiva.
    def defensiveEnergy
      sumShields + Dice.intensity(self.intelligence)
    end

  end#class
end#module
