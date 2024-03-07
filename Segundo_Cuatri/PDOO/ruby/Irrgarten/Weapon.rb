#encoding: UTF-8
module Weapon
    class Weapon
        def initialize(power,uses)
            @power = power
            @uses = uses
        end

        public def attack
            power = 0 
                if @uses > 0 
                    power = @power
                    @uses -= 1
                end
            return power
        end
        
        def to_s
            return "W[" + @power + "," + @uses + "]*"
        end
    end
end