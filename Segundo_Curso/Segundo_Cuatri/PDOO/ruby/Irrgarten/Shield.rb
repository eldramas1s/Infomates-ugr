#encoding: UTF-8

require_relative 'Dice'
require_relative 'CombatElement'

module Irrgarten
    # Esta clase pretende crear un objeto escudo que se encargará de
    # proteger a los individuos de juego
    # @param protection Cantidad de daño que protege
    # @param uses Cantidad de usos
    class Shield < CombatElement

	# Metodo inicializador de la clase Shield
	# @param defense Proteccion del escudo
	# @param durability Usos del escudo
	# @pos La instancia creada queda inicializada
    # def initialize(defense,durability)
    #     super
    # end
    
	# Efectúa la proteccion de un golpe
	# @return Valor de proteccion
	# pre -> delega en produceEffect
    # see -> CombatElement -> produceEffect
    def protect
        self.produceEffect
    end

	# Se encarga de eliminar el escudo si no hay usos suficientes
	# @return Decisión de inutilizacion
	# @pos Si no hya usos suficientes el objeto quedará inutilizable
	def discard
		Dice.discardElement(@uses)
	end

	# Metodo to string encargado de encadenar el estado del objeto
	# @return cadena con toda la informacion
        def to_s
            "S" + super
        end

    end#class
end#module
