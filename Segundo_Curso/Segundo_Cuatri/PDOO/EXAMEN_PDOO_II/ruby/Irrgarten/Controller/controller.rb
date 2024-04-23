module Control

  class Controller
    def initialize(game,view)
      @game = game
      @view = view
    end

    def play
      end_of_game = false
      while (!end_of_game)
        @view.show_game(@game.getGameState)
        direction = @view.next_move
        end_of_game = @game.nextStep(direction)
      end
      @view.show_game(@game.getGameState)
    end
  end # class
end # module
