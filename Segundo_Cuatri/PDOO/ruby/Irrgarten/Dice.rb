#encoding: UTF-8
module Dice #TODO Cambiar a atributos de clase
    def initialize()
        @MAX_USES = 5
        @MAX_ITELLIGENCE = 10.0
        @MAX_STRENGTH = 10.0
        @RESURRECT_PROB = 0.3
        @WEAPONS_REWARD = 2
        @SHIELDS_REWARD = 3
        @HEALTH_REWARD = 5
        @MAX_ATTACK = 3
        @MAX_SHIELD = 2
        @generator = Random.new()
    end

    def randomPos(max)
        return @generator.rand(max)
    end

    def whoStarts(players)
        return @generator.rand(players)
    end

    def randomIntelligence
        return (@generator.rand(@MAX_ITELLIGENCE))
    end

    def randomStrength
        return (@generator.rand(@MAX_STRENGTH))
    end

    def resurrectPlayer
        return @generator.rand(1.0) < RESURRECT_PROB
    end

    def weaponsReward
        return @generator.rand(@WEAPONS_REWARD)
    end

    def shieldsReward
        return @generator.rand(@SHIELDS_REWARD)

    def healthReward
        return @generator.rand(@HEALTH_REWARD)
    end

    def weaponPower
        return @generator.rand(@MAX_ATTACK)
    end

    def shieldPower
        return @generator.rand(@MAX_SHIELD)
    end

    def usesLeft
        return @generator.rand(@MAX_USES)
    end

    def intensity(competence)
        return @generator.rand(competence)
    end

    def discardElement(usesLeft)
        return (@generator.rand() < (@MAX_USES-usesLeft).to_f()/@MAX_USES.to_f())
    end
end
