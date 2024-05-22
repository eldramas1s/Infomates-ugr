require_relative 'Game'
require_relative 'UI/textUI'  # Como se ejecuta desde la carpeta Irrgarten no es necesario poner dicha carpeta al ser ruta relativa
require_relative 'Controller/controller'
require_relative 'FuzzyPlayer'

module Irrgarten
	NPLAYERS = 2

	p = Player.new('0',0,0.0)
	p.receiveReward()
	fp = FuzzyPlayer.new(p)
	q = Player.new('3',1,1)
	fq = FuzzyPlayer.new(q)
	puts p.to_s
	puts fp.to_s
	puts fq.to_s

	
end
