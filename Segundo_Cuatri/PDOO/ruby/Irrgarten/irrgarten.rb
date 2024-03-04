
module Irrgarten

    module GameCharacter
        PLAYER =:player
        MONSTER =:monster
    end

    module Orientation
        VERTICAL =:vertical
        HORIZONTAL =:horizontal
    end

    module Directions
        LEFT =:left
        RIGHT =:right
        UP =:up
        DOWN =:down
    end

    class weapon
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
    
    class shield #No interpretado
    	def initialize(defense,durability)
    		@protection = defense
    		@uses = durability
    	end
    	
    	def protect
    		prt_val = 0
    		if @uses > 0
    			prt_val = @protection
    			@uses -= 1
    		end
    		return prt_val
    	end 
    	
    	def to_s
    		puts "S[" + @protection + "," + @uses + "]*"
    	end

end
