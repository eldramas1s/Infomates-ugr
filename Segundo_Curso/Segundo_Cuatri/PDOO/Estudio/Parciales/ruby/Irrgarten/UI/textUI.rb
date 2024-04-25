
require 'io/console'
require_relative '../Directions'

module UI

  class TextUI
    @@desp = Array.new(22){Irrgarten::Directions::LEFT}
    @@desp[0]=@@desp[1]=Irrgarten::Directions::UP
    #https://gist.github.com/acook/4190379

    def initialize
	@index = 0
    end
    
    def read_char
      STDIN.echo = false
      STDIN.raw!

      input = STDIN.getc.chr
      if input == "\e"
        input << STDIN.read_nonblock(3) rescue nil
        input << STDIN.read_nonblock(2) rescue nil
      end
    ensure
      STDIN.echo = true
      STDIN.cooked!

      return input
    end

    def next_move
	output = @@desp[@index]
	@index += 1
	output
    end

    def show_game(game_state)
      puts game_state.to_s
    end

  end # class

end # module
