#encoding: UTF-8

require_relative 'Dice'
require_relative 'GameCharacter'
require_relative 'Player'
require_relative 'Labyrinth'
require_relative 'GameState'
require_relative 'Monster'
require_relative 'Directions'

module Irrgarten
  class Game

    #Mensajes
    @@PLAYER_WON_MSG = "Player Won."
    @@MONSTER_WON_MSG = " Monster Won."
    @@RESURRECTED_MSG = "Player resurrected."
    @@SKIP_TURN_MSG = "Player is dead, turn skipped."
    @@NO_ORDER_MSG = "Player couldn't move due to physical problems."
    @@EMPTY_BLOCK_MSG = "Block with no action."
    @@BOSS_NAME = "Bowser"
    @@MAX_ROUNDS=10
    @@MONSTER_NAME = "Mike Wazousky"
    @@ROWS = 5
    @@COLS = 4

    # Inicializador
    # nplayers -> Numero de jugadores del juego
    # crea el juego al completo, inicializa el laberinto, tantos jugadores como se quiera y se mande en el main
    def initialize(nplayers)
        @currentPlayerIndex=Dice.whoStarts(nplayers)

        @players = Array.new(nplayers)
        for i in 0...nplayers do
            @players[i] = Player.new(i,Dice.randomStrength,Dice.randomIntelligence)
        end
        @currentPlayer = @players[@currentPlayerIndex]


        @monsters=[]    # Igual que poner Array.new
        @log=""

        @labyrinth=Labyrinth.new(@@ROWS,@@COLS,0,0)
        configureLabyrinth
        @labyrinth.spreadPlayers(@players)
    end

    # Devuelve true si hay un ganador
    def finished
        @labyrinth.haveAWinner
    end

    # Maneja el turno y devuelve si acaba el juego
    # Maneja: combate, movimiento y recompensas del jugador en juego en cada turno
    def nextStep(preferredDirection)
      @log = ""
      dead = @currentPlayer.dead()
      if !dead then
        direction = actualDirection(preferredDirection)
        if direction != preferredDirection then
          logPlayerNoOrders
        end

        monster = @labyrinth.putPlayer(direction,@currentPlayer)

        if monster == nil then
          logNoMonster
        else
          winner = combat(monster)
          manageReward(winner)
        end

      else
        manageResurrection
      end

      endGame = finished

      if !endGame then
        nextPlayer
      end

      endGame
    end

    # Devuelve el estado de juego con el formato deseado
    def getGameState
      laby = @labyrinth.to_s
      avatars = ""

      for i in 0...@players.size do
        avatars += @players[i].to_s + "\n"
      end

      beasts = ""

      for i in 0...@monsters.size do
        beasts += "\t" + @monsters[i].to_s + "\n"
      end

      curr = @currentPlayerIndex
      win = finished
      tempLog = @log
      gs = GameState.new(laby,avatars,beasts,curr,win,tempLog)
    end

    #private

    # Configura el laberinto a nuestro gusto, es un 15x15 con 5 monstruos y un jefe.
    def configureLabyrinth
      @labyrinth.addBlock(Orientation::HORIZONTAL, 2, 1, 3);
  	  
      @monsters << Monster.new(@@MONSTER_NAME,0,0)
      @monsters << Monster.new(@@BOSS_NAME,99999,99999)

      #@labyrinth.addMonster(5,5,Monster.new("debugOnly",20,20))

      @labyrinth.addMonster(0, 2,@monsters[1]);
      @labyrinth.addMonster(3, 1,@monsters[0]);
      
    end

    # Devuelve el jugador del siguiente turno, es un ciclo.
    def nextPlayer
        @currentPlayerIndex = (@currentPlayerIndex +1)% @players.size
        @currentPlayer = @players[@currentPlayerIndex]
    end

    # Devuelve la direccion de movimiento real, es decir, si se pasa un movimiento imposible devuelve la solucion a ese conflicto
    # preferredDirection -> Direccion a la que me quiero mover
    def actualDirection(preferredDirection)
      currentRow = @currentPlayer.row
      currentCol = @currentPlayer.col
      validMoves = @labyrinth.validMoves(currentRow,currentCol)
      output = @currentPlayer.move(preferredDirection,validMoves)
    end

    # Maneja el combate con un monstruo y lo registra en el log
    # monster -> monstruo con el que se combate
    # Se controla el numero de turnos
    # True -> gana jugador
    # False -> gana monstruo
    # Player tiene un turno mas
    def combat(monster)
      rounds = 0
      winner = GameCharacter::PLAYER
      playerAttack = @currentPlayer.attack
      lose = monster.defend(playerAttack)
      while ((!lose) && (rounds < @@MAX_ROUNDS))
        winner = GameCharacter::MONSTER
        rounds += 1
        monsterAttack = monster.attack
        lose = @currentPlayer.defend(monsterAttack)
        if !lose then
          playerAttack = @currentPlayer.attack
          winner = GameCharacter::PLAYER
          lose = monster.defend(playerAttack)
        end
      end
      logRounds(rounds,@@MAX_ROUNDS)
      winner
    end

    # Maneja si el jugador que ha combatido recibe o no regalos dependiendo si gana o no
    # winner -> bool que es True si current player ha ganado
    def manageReward(winner)
      if winner == GameCharacter::PLAYER then
        @currentPlayer.receiveReward
        logPlayerWon
      else
        logMonsterWon
      end
    end

    # Maneja si un jugador resucita o no y lo registra en log
    # Delega en Dice
    def manageResurrection
      resurrect = Dice.resurrectPlayer
      if resurrect then
        @currentPlayer.resurrect
        logResurrected
      else
        logPlayerSkipTurn
      end
    end

    def logPlayerWon
      @log += @@PLAYER_WON_MSG + "\n"
    end

    def logMonsterWon
      @log += @@MONSTER_WON_MSG + "\n"
    end

    def logResurrected
      @log += @@RESURRECTED_MSG + "\n"
    end

    def logPlayerSkipTurn
      @log += @@SKIP_TURN_MSG + "\n"
    end

    def logPlayerNoOrders
      @log += @@NO_ORDER_MSG + "\n"
    end

    def logNoMonster
      @log += @@EMPTY_BLOCK_MSG + " " + @@NO_ORDER_MSG + "\n"
    end

    def logRounds(rounds, max)
      @log += " Se han producido #{rounds} de #{max}\n"
    end

  end#Class
end#Module
