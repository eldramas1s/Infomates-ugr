#encoding: UTF-8

#require 'Dice'
#TODO: Revisar por Airam
module Dice
    class Dice
   	#Atributos de clase
	@@MAX_USES = 5
        @@MAX_ITELLIGENCE = 10.0
        @@MAX_STRENGTH = 10.0
        @@RESURRECT_PROB = 0.3
        @@WEAPONS_REWARD = 2
        @@SHIELDS_REWARD = 3
        @@HEALTH_REWARD = 5
        @@MAX_ATTACK = 3
        @@MAX_SHIELD = 2
	@@generator = Random.new		
	def initialize
	     #TODO: que hago con esto?
	end

	def self.randomPos(max)
	    return @@generator.rand(max)
	end

	def self.whoStarts(players)
	    return @@generator.rand(players)
	end

	def self.randomIntelligence
	    return (@@generator.rand(@MAX_ITELLIGENCE))
	end

	def self.randomStrength
	    return (@@generator.rand(@MAX_STRENGTH))
	end

	def self.resurrectPlayer
	    return @@generator.rand(1.0) < RESURRECT_PROB
	end

	def self.weaponsReward
	    return @@generator.rand(@WEAPONS_REWARD)
	end

	def self.shieldsReward
	    return @@generator.rand(@SHIELDS_REWARD)
	end

	def self.healthReward
	    return @@generator.rand(@HEALTH_REWARD)
	end

	def self.weaponPower
	    return @@generator.rand(@MAX_ATTACK)
	end

	def self.shieldPower
	    return @@generator.rand(@MAX_SHIELD)
	end

	def self.usesLeft
	    return @@generator.rand(@MAX_USES)
	end

	def self.intensity(competence)
	    return @@generator.rand(competence)
	end

	def self.discardElement(usesLeft)
	    return (@@generator.rand() < (@MAX_USES-usesLeft).to_f()/@MAX_USES.to_f())
   	end
	
    end
end
