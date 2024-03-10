#encoding: UTF-8

#Inclusiones

require_relative 'Dice.rb'

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
	    Dice::Dice.discardElement(@uses)
	end

        def to_s
            "W[" + @power.to_s + "," + @uses.to_s + "]*"
        end
    end

#Main

arma = Weapon.new(3.0,5)

puts arma.inspect

arma.attack

puts arma.to_s

puts arma.discard 

end
