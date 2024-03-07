#encoding: UTF-8
module Weapon
    class Weapon
        def initialize(power,uses)
            @power = power
            @uses = uses
        end

        public def attack
            power = @power 
            unless @uses > 0 
                power = 0 
                @uses -= 1
            end
            return power
        end
        
        def to_s
            return "W[" + @power + "," + @uses + "]*"
        end
    end
end