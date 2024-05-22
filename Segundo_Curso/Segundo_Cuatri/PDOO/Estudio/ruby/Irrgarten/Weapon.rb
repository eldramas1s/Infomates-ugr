#encoding: UTF-8

require_relative 'Dice'
require_relative 'CombatElement'

module Irrgarten

    # Clase que simboliza el arma de un jugador
    # @param power Daño que realiza el arma
    # @param uses Veces que se puede utilizar el arma para atacar
    class Weapon < CombatElement

	# Metodo que simboliza el acto de ataque por parte de una entidad
	# @return Daño causado
	# pre -> delega en produceEffect
    # see -> CombatElement->produceEfect
        def attack
            self.produceEffect
        end

	# Metodo encargado de encadenar la informacion de estado de la instancia
	# @return Cadena con la informacion de estado de la instancia
	# @pos La instancia no queda modificada
        def to_s
            "W" + super
        end
    end
end
