#encoding: UTF-8

#Inclusiones

require_relative 'Dice.rb'

module Irrgarten

    # Clase que simboliza el arma de un jugador
    # @param power Daño que realiza el arma
    # @para uses Veces que se puede utilizar el arma para atacar
    class Weapon

	# Inicializador de la clase
	# @param power Daño que va a tener el arma
	# @param uses Número de veces que se podrá usar el arma
	# @pos La instancia de la clase queda inicializada
        def initialize(power,uses)
            @power = power
            @uses = uses
        end

	# Metodo que simboliza el acto de ataque por parte de una entidad
	# @return Daño causado
	# @pos Si @uses>0 => @uses=@uses-1
	#      Si @uses==0 => arma rota 
        def attack
            power = 0 
                if @uses > 0 then
                    power = @power
                    @uses -= 1
                end
             power
        end
        
	# Metodo encargado de tomar la decision de descarte del arma
	# @return true si se descarta el arma
	# 	  false si no se descarta 
	def discard
	    Dice.discardElement(@uses)
	end
	
	# Metodo encargado de encadenar la informacion de estado de la instancia
	# @return Cadena con la informacion de estado de la instancia
	# @pos La instancia no queda modificada
        def to_s
            "W[" + @power.to_s + "," + @uses.to_s + "]*"
        end
    end

#Main

arma = Weapon.new(3.0,5)

puts arma.inspect

arma.attack

puts arma.to_s

puts arma.discard 

end
