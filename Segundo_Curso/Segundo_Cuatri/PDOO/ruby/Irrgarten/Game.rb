#encoding: UTF-8

require_relative 'Dice'
require_relative 'GameCharacter'

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
        @@MONSTER_NAMES = ["Mike Wazousky"]
        @@ROWS = 15
        @@COLS = 15

        def initialize(nplayers)
            @currentPlayerIndex=Dice.whoStarts(nplayers)

            @players = Array.new(nplayers)
            for i in 0...nplayers do
                @players[i] = Player.new("")
            end
            @currentPlayer = @players[@currentPlayerIndex]


            @monsters=[]
            @log=""

            #TODO cambiar a algo con sentido
            @labyrinth=Labyrinth.new(@@ROWS,@@COLS,0,0)
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
			if monster == NULL then
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
            avatars = @players.to_s
            beasts = @monsters.to_s
            curr = @currentPlayerIndex
            win = finished
            tempLog = @log
            gs = GameState.new(laby,avatars,beasts,curr,win,tempLog)
        end

        def configureLabyrinth

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
		while !lose && (ronds < @@MAX_ROUNDS)
			winner = GameCharacter::MONSTER
			rounds++
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

	#TODO: Comprender clase GameCharacter (GameCharacter.PLAYER)
        def manageRewared(winner)
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

    end
end
