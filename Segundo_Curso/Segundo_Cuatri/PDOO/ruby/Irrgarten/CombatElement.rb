module Irrgarten
  require_relative 'Dice'
  class CombatElement
    def initialize(effect,uses)
      @effect = effect
      @uses = uses
    end

    protected
      def produceEffect()
        eff_val = 0
            if @uses > 0 then
                eff_val = @effect
                @uses -= 1
            end
        eff_val
      end

    public
      def discard
        Dice.discardElement(@uses);
      end

      def to_s
        return "[" + @effect.to_s + "," + @uses.to_s + "]*"
      end
  end

end
