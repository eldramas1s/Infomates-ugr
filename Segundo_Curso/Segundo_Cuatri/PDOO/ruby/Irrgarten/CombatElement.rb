module Irrgarten
  require_relative 'Dice'
  class CombatElement

    # Inicializador de CombatElement
    # effect -> efecto del elemento de combate
    # uses -> usos del elemento de combate
    def initialize(effect,uses)
      @effect = effect
      @uses = uses
    end

    protected

      # Efecto producido por un CombatElement
      # return -> valor del efecto producido
      def produceEffect()
        eff_val = 0
            if @uses > 0 then
                eff_val = @effect
                @uses -= 1
            end
        eff_val
      end

    public

      # Probabilidad de descarte de un CombatElement
      # return -> True -> se descarta
      #           False -> No se descarta
      def discard
        Dice.discardElement(@uses);
      end

      # Concatena la informacion de un CombatElement
      # return -> Cadena con la informacion
      def to_s
        return "[" + @effect.to_s + "," + @uses.to_s + "]*"
      end

  end

end
