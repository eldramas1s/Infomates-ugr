#encoding: UTF-8

require_relative 'Dice'
require_relative 'CombatElement'

module Irrgarten
    # Esta clase pretende crear un objeto escudo que se encargará de
    # proteger a los individuos de juego
    # @param protection Cantidad de daño que protege
    # @param uses Cantidad de usos
    class Shield < CombatElement

	# Efectúa la proteccion de un golpe
	# @return Valor de proteccion
	# pre -> delega en produceEffect
    # see -> CombatElement -> produceEffect
    def protect
        self.produceEffect
    end

	# Metodo to string encargado de encadenar el estado del objeto
	# @return cadena con toda la informacion
        def to_s
            "S" + super
        end

    end#class
end#module
