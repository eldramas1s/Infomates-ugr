#encoding: UTF-8

require_relative 'Dice'
require_relative 'LabyrinthCharacter'


module Irrgarten

    class Monster < LabyrinthCharacter

        #Vida inicial de un monstruo
        @@INITIAL_HEALTH = 5

        def initialize(name, intelligence, strength)
            super(name,intelligence,strength,@@INITIAL_HEALTH)
        end

        #TODO*: Revisar si todos a gusto
        #*Eliminados: dead, setPos, gotWounded

        #Calcula la intensidad de ataque del monstruo
        def attack
            atk=0
            atk=Dice.intensity(@strength) unless dead
            atk
        end

        #Devuelve el estado del monstruo en forma de cadena
        def to_s
            "M"+super
        end

        #Calcula como se defiende el monstruo
        def defend(receivedAttack)
		    isDead = dead
          	if !isDead
                defensiveEnergy = Dice.intensity(@intelligence)
                if(defensiveEnergy < receivedAttack)
                    gotWounded
                    isDead = dead
                end
		    end
		    isDead
        end
    end#class
end#module
