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
    @@ROWS = 15
    @@COLS = 15

    def initialize(nplayers)
        @currentPlayerIndex=Dice.whoStarts(nplayers)

        @players = Array.new(nplayers)
        for i in 0...nplayers do
            @players[i] = Player.new(i,Dice.randomStrength,Dice.randomIntelligence)
        end
        @currentPlayer = @players[@currentPlayerIndex]


        @monsters=[]
        @log=""

        #TODO cambiar a algo con sentido
        @labyrinth=Labyrinth.new(@@ROWS,@@COLS,@@ROWS-2,@@COLS-1)
        configureLabyrinth
        @labyrinth.spreadPlayers(@players)
    end

    def finished
        @labyrinth.haveAWinner
    end

    def nextStep(preferredDirection)#boolean
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

    def configureLabyrinth
      @labyrinth.addBlock(Orientation::VERTICAL, 0, 0,@@COLS);
      @labyrinth.addBlock(Orientation::HORIZONTAL, 0, 1, @@ROWS);
      @labyrinth.addBlock(Orientation::HORIZONTAL, @@ROWS-1, 1, @@ROWS);
      @labyrinth.addBlock(Orientation::VERTICAL, 1, @@COLS-1, @@COLS);

      # Creación de boss

      nMonsters=5
      intelligence = [2,3,3,5,6]
      strength = [3,2,3,6,5]

      @monsters << Monster.new(@@BOSS_NAME,8,8)
      for i in 0...nMonsters do
        @monsters << Monster.new(@@MONSTER_NAME,intelligence[i],strength[i])
      end

      @labyrinth.addMonster(5,5,Monster.new("debugOnly",20,20))

      @labyrinth.addMonster(@@ROWS-2, @@COLS-2,@monsters[0]);
      #Monstruos débiles
      @labyrinth.addMonster(6, @@COLS-3, @monsters[1]);
      @labyrinth.addMonster(1, @@COLS-3, @monsters[2]);
      @labyrinth.addMonster(11, 11, @monsters[3]);
      @labyrinth.addMonster(12, 11, @monsters[4]);
      @labyrinth.addMonster(13, 10, @monsters[5]);

      #Resto de paredes
      @labyrinth.addBlock(Orientation::VERTICAL,1,@@COLS-2,@@COLS)
      @labyrinth.addBlock(Orientation::VERTICAL,(@@ROWS>>1),@@COLS-3,(@@COLS>>1)-1)
      @labyrinth.addBlock(Orientation::VERTICAL,(@@ROWS>>1)-2,@@COLS-4,(@@COLS>>1)-1)

      @labyrinth.addBlock(Orientation::VERTICAL, 9, 2, 3);
      @labyrinth.addBlock(Orientation::VERTICAL, 9, 3, 2);
      @labyrinth.addBlock(Orientation::VERTICAL, 9, 4, 3);

      @labyrinth.addBlock(Orientation::HORIZONTAL, 1,9, 3);
      @labyrinth.addBlock(Orientation::HORIZONTAL, 2,9, 3);
      @labyrinth.addBlock(Orientation::HORIZONTAL, 3,9, 3);
      @labyrinth.addBlock(Orientation::HORIZONTAL, 5,9, 2);
      @labyrinth.addBlock(Orientation::HORIZONTAL, 8,6, 6);
      @labyrinth.addBlock(Orientation::HORIZONTAL, 9,6, 6);
      @labyrinth.addBlock(Orientation::HORIZONTAL, 10,6, 6);
      @labyrinth.addBlock(Orientation::HORIZONTAL, 11,6, 4);
      @labyrinth.addBlock(Orientation::HORIZONTAL, 13,1, @@ROWS-6);

    end

    def nextPlayer
        @currentPlayerIndex = (@currentPlayerIndex +1)% @players.size
        @currentPlayer = @players[@currentPlayerIndex]
    end

    def actualDirection(preferredDirection)
      currentRow = @currentPlayer.row
      currentCol = @currentPlayer.col
      validMoves = @labyrinth.validMoves(currentRow,currentCol)
      output = @currentPlayer.move(preferredDirection,validMoves)
    end

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

    def manageReward(winner)
      if winner == GameCharacter::PLAYER then
        @currentPlayer.receiveReward
        logPlayerWon
      else
        logMonsterWon
      end
    end

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
