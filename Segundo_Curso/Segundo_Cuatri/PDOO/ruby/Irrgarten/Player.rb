#encoding: UTF-8

require_relative 'Dice'
require_relative 'Weapon'
require_relative 'Shield'

module Irrgarten

    class Player
        @@DEFAULT_NAME = "Player #"
        @@INVALID_POS = -1 #TODO: Ver si lo puedes meter junto con el de monstruo en Labyrinth
        
        @@MAX_WEAPONS = 2
        @@MAX_SHIELDS = 3
        @@INITIAL_HEALTH = 10
        @@HITS2LOSE = 3
	
	##TODO: PREGUNTAR LOS CONTENEDORES QUE SON
 
        def initialize(number,intelligence,strength)
            @name = @@DEFAULT_NAME
            @number = number
            @intelligence = intelligence
            @strength =strength
            @health = @INITIAL_HEALTH
            @row = @INVALID_POS
            @col = @INVALID_POS
            @consecutiveHits = 0 
            @weapons = Array.new(0)
            @shields = Array.new(0)
        end

	    def resurrect
            weapons.clear()
            shields.clear()
            health = @INITIAL_HEALTH
            consecutiveHits = 0
        end

        #getter row, col, number
        attr_reader :row
        attr_reader :col
        attr_reader :number
    
        def setPos(row,col)
            if row >= 0 && col >= 0 then
                @row = row
                @col = col
            end
        end

        def dead
            @health <= 0
        end

	    def move(direction, validMoves)
            size = validMoves.length
            contained = find(direction,validMoves)
            if (size > 0) && !contained then
                firstElement = validMoves[0]
                return firstElement
            else 	
                return direction
            end 
        end

	    def attack
            @strength + sumWeapons
        end

	    def defend(receivedAttack)
            manageHit(receivedAttack)
        end

	def receiveReward
        wReward = Dice.weaponsReward
        sReward = Dice.shieldsReward
        for i in 0..wReward do
            wnew = newWeapon
            receiveWeapon(wnew)
        end
        for i in 0..sReward do
            snew = newShield
            receiveShield(snew)
        end
        extraHealth = Dice.healthReward
        @health += extraHealth
    end

	    def to_s
            str="#{@name}, #{@number}, #{@intelligence}, #{@strength}\n"
            str+= "Weapons: ["
            str += @weapons[0].to_s unless @weapons.length==0

            for w in 1...@weapons.length do
                str += " - " + w.to_s
            end
            str += "]\n"
            str+= "Shields: ["
            str += @shields[0].to_s unless @shields.size==0

            for sh in 1...@shields.size do
                str += " - " + sh.to_s
            end
            str += "]\n"
            str
                
        end 

	##private

        def receiveWeapon(w)
	    i=0
	    while i<@weapons.length
		wi=@weapons[i] 
           	if(wi.discard()) then
                    @weapons.shift
                else
		    i+=1
		end
            end
            size = @weapons.length
            if size<@@MAX_WEAPONS then
                w = newWeapon
                @weapons.append(w)	
            end
        end

	#TODO: Si no tiene armas o escudos da fallo
        def receiveShield(s)
            i=0
            while i<@shields.length
                si=@shield[i]
                if(si.discard) then
                    @shields.shift
                        else
                    i+=1
                end
	        end
            size = @shields.length
            if(size<@@MAX_SHIELDS) then
                s = newShield
                @shields.append(s)
            end
        end

        def manageHit(receivedAttack)
            defense=defensiveEnergy
            if defense<receivedAttack then
                gotWounded
                incConsecutiveHits
            else
                resetHits
            end
            lose=true
            if (@consecutiveHits == @@HITS2LOSE)||(dead()) then
                resetHits
            else	
                lose=false
            end
            return lose
        end 

	#TODO: No añade el arma al set de armas?
        def newWeapon
            Weapon.new(Dice.weaponPower, Dice.usesLeft)
        end

	#TODO: Acordar si el metodo shieldPower es el que hay que usar(igual con weaponPower)
        def newShield
            Shield.new(Dice.shieldPower, Dice.usesLeft)
        end

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

        def sumWeapons
            sum=0
            for i in 0..@weapons.size do
                sum += @weapons[i].attack
            end
            sum
        end

        def sumShields
            sum=0
            for i in 0..@shields.size do
                sum += @shields[i].protect
            end
            sum
        end

    def find(element,array)
        found = false
        i = 0
        while !found && (i<array.size) 
            if array[i] == element then 
                found = true
            else 
                i += 1
            end
        end
        found	
    end
end #class


p = Player.new('45',0,0)

puts p.to_s

p.setPos(0,0)

w = p.newWeapon
s = p.newShield

puts w.to_s
puts s.to_s

p.receiveWeapon(w)

p.receiveShield(s)

puts p.to_s

validMoves = [Directions::UP]

p.move(Directions::UP,validMoves)

p.manageHit(10)

puts p.to_s

puts p.dead()

p.receiveReward

puts p.to_s
end #module
