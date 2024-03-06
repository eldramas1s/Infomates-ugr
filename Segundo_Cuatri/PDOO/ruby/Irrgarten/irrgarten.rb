
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
        
        def to_s
            return "W[" + @power + "," + @uses + "]*"
        end
    
    class shield #No interpretado
    	def initialize(defense,durability)
    		@protection = defense
    		@uses = durability
    	end
    	
    	def protect
    		prt_val = 0
    		#unless??
    		unless @uses > 0
    			prt_val = @protection
    			@uses -= 1
    		end
    		return prt_val
    	end 
    	
    	def to_s
    		return "S[" + @protection + "," + @uses + "]*"
    	end
    end
   
    class game_state
	def initialize(laby,avatars,beasts,p_player,victorious,account)
		@labyrinthv = laby
		@players = avatars
		@monsters = beasts
		@current_player = p_player
		@winner = victorious
		@log = account
	end
	
	def get_labyrinthv
		return @labyrinthv
	end
	
	def get_players
		return @players
	end

	def get_monsters
		return @monsters
	end
	
	def get_current_player
		return @current_player
	end
	
	def get_winner
		return @winner
	end
	
	def get_log
		return @log
	end
    end
end
