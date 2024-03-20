
require_relative 'Dice'
require_relative 'Weapon'
require_relative 'Shield'


module Player

    class Player
        @@DEFAULT_NAME = "Player #"
        @@INVALID_POS = -1 #TODO: Ver si lo puedes meter junto con el de monstruo en Labyrinth
        
        @@MAX_WEAPONS = 2
        @@MAX_SHIELD = 3
        @@INITIAL_HEALTH = 10
        @@HITS2LOSE = 3

        def initialize(number,intelligence,strength)
            @name = @@DEFAULT_NAME
            @number = number
            @intelligence = intelligence
            @strength =strength
            @health = @INITIAL_HEALTH
            @row = @INVALID_POS
            @col = @INVALID_POS
            @consecutiveHits = 0 #Constante?
            @weapons = []
            @shields = []
        end

        def resurrect
            weapons.clear()
            shields.clear()
            health = @INITIAL_HEALTH
            consecutiveHits = 0
        end

        def setPos(row,col)
            @row = row
            @col = col
        end

        def dead
            @health <= 0
        end

        #TODO
        def attack
            @strength + sumWeapons
        end

        #TODO
        def defend(received_Attack)
            #Se manejará en manageHit
        end

        def to_s
            "#{@name}#{number}, #{@intelligence}, #{@strength}, #{@health}, (#{@row},#{@col}), #{@consecutiveHits}, #{@weapons}, #{@shields}"
        end

        private: 

        def newWeapon
            Weapon.new(Dice::Dice.randomStrength, Dice::Dice.usesLeft)
        end

        def newShield
            Shield.new(Dice::Dice.randomShield, Dice::Dice.usesLeft)
        end

        #TODO
        def defensiveEnergy
            @intelligence + sumShields
        end

        def resetHits
            @consecutiveHits = 0
        end

        def gotWounded
            @health -= 1
        end

        def incConsecutiveHits
            @consecutiveHits +=1
        end

        #TODO comprobar sintaxis
        def sumWeapons
            sum=0
            for i in 0..@weapons.size do
                sum += @weapons[i].attack
            end
            sum
        end

        #TODO
        def sumShields
            sum=0
            for i in 0..@shields.size do
                sum += @shields[i].protect
            end
            sum
        end
    end
end


