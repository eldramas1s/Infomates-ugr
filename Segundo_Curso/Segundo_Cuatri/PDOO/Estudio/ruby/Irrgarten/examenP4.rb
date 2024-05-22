require_relative 'Labyrinth.rb'
require_relative 'Monster.rb'
require_relative 'FuzzyGoNuts.rb'

module Prueba
	class Prueba 
		def self.main
			lab = Irrgarten::Labyrinth.new(3,3,0,0)
			p=Irrgarten::Player.new(0,Irrgarten::Dice.randomIntelligence,Irrgarten::Dice.randomStrength)
			lab.spreadPlayers(p)
			
			puts lab.to_s
			puts p.to_s
			
			p = Irrgarten::FuzzyGoNuts.new(p)
			lab.switchPlayer(p)
			
			for i in 0..10 do
				p.move()
			end
		
			puts lab.to_s
			puts p.to_s
		end #main
	end #Prueba
	
	Prueba.main
end #Modulo


