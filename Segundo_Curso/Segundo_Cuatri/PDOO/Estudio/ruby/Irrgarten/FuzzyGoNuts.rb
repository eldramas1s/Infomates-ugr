require_relative 'FuzzyPlayer.rb'
require_relative 'Directions.rb'
module Irrgarten
	
	class FuzzyGoNuts < FuzzyPlayer
		@@DIRECTION = Directions::UP
		@@validMoves = Array.new(1)
		@@validMoves << @@DIRECTION
		#Mismo initialize de Fuzzy
		
		def move()
			result = super(@@DIRECTION,@@validMoves)
			resultado = Dice.nextStepFuzzy(result,@@DIRECTION)
		end
	end
end

