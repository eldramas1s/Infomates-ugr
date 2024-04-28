#encoding: UTF-8

#Inclusiones

require_relative 'Dice'

module Irrgarten

    # Clase que simboliza el arma de un jugador
    # @param power Daño que realiza el arma
    # @param uses Veces que se puede utilizar el arma para atacar
    class Weapon < CombatElement

	# Inicializador de la clase
	# @param power Daño que va a tener el arma
	# @param uses Número de veces que se podrá usar el arma
	# @pos La instancia de la clase queda inicializada
        def initialize(power,uses)
            super
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

	# Metodo encargado de encadenar la informacion de estado de la instancia
	# @return Cadena con la informacion de estado de la instancia
	# @pos La instancia no queda modificada
        def to_s
            "W" + super
        end
    end
end
