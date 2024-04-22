require_relative 'Game'
require_relative 'UI/textUI'  # Como se ejecuta desde la carpeta Irrgarten no es necesario poner dicha carpeta al ser ruta relativa
require_relative 'Controller/controller'
module Irrgarten
  NPLAYERS = 2

  # Creo un juego
  game = Game.new(NPLAYERS)

  #Creo un UI
  ui = UI::TextUI.new()

  # Creo un controlador
  control = Control::Controller.new(game,ui)

  #Jugar
  control.play
end
