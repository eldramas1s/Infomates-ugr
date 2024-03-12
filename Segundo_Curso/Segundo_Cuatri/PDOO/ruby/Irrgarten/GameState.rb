#encoding: UTF-8
module GameState

    # Clase encargada de la distribución del area de juego
    # @param labyrinthv Estado del laberinto
    # @param players Estado de los jugadores
    # @param monsters Estado de los monstruos
    # @param current_players Indice del jugador actual
    # @param winner Indicador de si hay un vencedor
    # @param log Almacen de eventos del turno anterior
    class GameState
		
		# Inicializador de la clase
		# @param laby Estado del laberinto
		# @param avatars Estado de los jugadores
		# @param beasts Estado de los monstruos
		# @param p_player Indice del jugador actual
		# @param victorious Indicador de vencedor
		# @param account Almacen de eventos del turno anterior
		# @pos La instacia queda inicializada al completo
		def initialize(laby,avatars,beasts,p_player,victorious,account)
			@labyrinth = laby
			@players = avatars
			@monsters = beasts
			@current_player = p_player
			@winner = victorious
			@log = account
		end
		
		# Consultor del estado del laberinto
		# return Estado del laberinto

		def labyrinth
			@labyrinth
		end

		# Consultor del estado de los jugadores
		# return Estado de los jugadores			
		def players
			@players
		end

		# Consultor del estado de los monstruos
		# return Estado de los monstruos
		def monsters
			@monsters
		end
		
		# Consultor del indice del jugador actual
		# return Indice del jugador actual
		def current_player
			@current_player
		end
		
		# Consultor del fin de la partida por vencedor
		# return true si hay vencedor
		# 	 false si no lo hay
		def winner
			@winner
		end
		
		# Consultor del almacen de eventos del turno anterior
		# return Eventos del turno anterior
		def log
			@log
		end
    end

# Main

estadio = GameState.new('Carpena','juan','varios',5,true,'dramas.es')

puts estadio.inspect

puts estadio.labyrinth

puts estadio.players

puts estadio.monsters

puts estadio.current_player

puts estadio.winner

puts estadio.log

end
