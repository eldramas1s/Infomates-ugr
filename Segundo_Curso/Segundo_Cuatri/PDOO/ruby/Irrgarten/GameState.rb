#encoding: UTF-8
module Irrgarten

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
		# @param register Almacen de eventos del turno anterior
		# @pos La instacia queda inicializada al completo
		def initialize(laby,avatars,beasts,p_player,victorious,register)
			@labyrinth = laby
			@players = avatars
			@monsters = beasts
			@current_player = p_player
			@winner = victorious
			@log = register
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
		# 	 		 false si no lo hay
		def winner
			@winner
		end

		# Consultor del almacen de eventos del turno anterior
		# return Eventos del turno anterior
		def log
			@log
		end

		def to_s

			#Lo pongo modo esquematico siendo el tablero de juego lo ultimo junto con quien le toca jugar
			str = ""
			if @winner then
				str += "There's a winner!\n"
			else
				str += "Just keep playing...\n"
			end
			str += "Players:\n" + @players
			str += "Monsters:\n" + @monsters
			str += "Some context:\n" + @log + "\n"

			if @winner then
				str += "Labyrinth: " + @labyrinth + "\n"
			else
				str += "Player #" + @current_player.to_s + " is your turn.\n"
				str += "Labyrinth: " + @labyrinth + "\n"
				str += "Make a good choice!\n"
			end
			str
		end
  end#class
end#module
