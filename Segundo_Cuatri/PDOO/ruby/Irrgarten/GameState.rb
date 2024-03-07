#encoding: UTF-8
module GameState
    class GameState
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