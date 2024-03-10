#encoding: UTF-8
module Weapon
    class Weapon
        def initialize(power,uses)
            @power = power
            @uses = uses
        end

        def attack
            power = 0 
                if @uses > 0 then
                    power = @power
                    @uses -= 1
                end
             power
        end
        
	def discard
	    Dice::discardElement(@uses)
	end

        def to_s
            "W[" + @power + "," + @uses + "]*"
        end
    end
end
