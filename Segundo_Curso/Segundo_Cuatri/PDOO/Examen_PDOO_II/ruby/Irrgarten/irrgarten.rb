require_relative 'Game'
require_relative 'UI/textUI'
require_relative 'Controller/controller'
module Irrgarten
  NPLAYERS = 2
  game = Game.new(NPLAYERS)
  ui = UI::TextUI.new()
  control = Control::Controller.new(game,ui)
  control.play
end
