
#require_relative 'Player'
require_relative 'Game'

module Test

  class Examen3
    def principal
      p = Irrgarten::Player.new(0,Irrgarten::Dice.randomIntelligence,Irrgarten::Dice.randomStrength)
      #w = Weapon.new(Dice.weaponPower, Dice.usesLeft)
      #s = Shield.new(Dice.shieldPower, Dice.usesLeft)
      p.receiveReward
      p
    end

    def Hangar
      g = Irrgarten::Game.new(1)
    end

  end


  # main

  e = Examen3.new
  p = e.principal
  puts "(2.a)" + p.to_s + "\n"
  l = e.Hangar
  puts "(2.b)" + l.getGameState.to_s + "\n"
  w = Irrgarten::Weapon.new(Irrgarten::Dice.weaponPower, Irrgarten::Dice.usesLeft)
  puts w.to_s
  p.receiveReward
  p.receiveReward
  p.receiveReward
  puts p.to_s

  p.attack
  p.receiveReward
  p.defend(100000)

  puts p.to_s

  s = Irrgarten::Shield.new(1.5,2)
  puts s.to_s

end
