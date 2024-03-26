#encoding: UTF-8

require_relative 'Dice'

module Irrgarten
    class Game

        #Mensajes 
        @@PLAYER_WON_MSG = "Player Won."
        @@MONSTER_WON_MSG = " Monster Won."
        @@RESURRECTED_MSG = "Player resurrected."
        @@SKIP_TURN_MSG = "Player is dead, turn skipped."
        @@NO_ORDER_MSG = "Player couldn't move due to physical problems."
        @@EMPTY_BLOCK_MSG = "Block with no action."

        @@MAX_ROUNDS=10
        @@MONSTER_NAMES = ["Mike Wazousky"]
        @@ROWS = 10
        @@COLS = 10

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

        def nextStep(preferredDirection)

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
        end

        def combat(monster)
        end

        def manageRewared(winner)
        end

        def manageResurrection
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