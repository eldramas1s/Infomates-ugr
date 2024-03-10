#encoding: UTF-8

#Inclusion modulo Dice
require_relative 'Dice.rb'

module Shield
    # Esta clase pretende crear un objeto escudo que se encargará de 
    # proteger a los individuos de juego
    # @param protection Cantidad de daño que protege
    # @param uses Cantidad de usos 
    class Shield
	
	# Metodo inicializador de la clase Shield
	# @param defense Proteccion del escudo
	# @param durability Usos del escudo
	# @pos La instancia creada queda inicializada
        def initialize(defense,durability)
            @protection = defense   
            @uses = durability
        end
	
	# Efectúa la proteccion de un golpe
	# @return Valor de proteccion
	# @pos Si uses>0 perdera un uso
	#      Si uses=0 se destruirá el objeto        
        def protect
            prt_val = 0
                if @uses > 0 then
                    prt_val = @protection
                    @uses -= 1
                end
            prt_val
        end
 	
	# Se encarga de eliminar el escudo si no hay usos suficientes
	# @return Decisión de inutilizacion
	# @pos Si no hya usos suficientes el objeto quedará inutilizable
	def discard
		Dice::Dice.discardElement(@uses)
	end
        
	# Metodo to string encargado de encadenar el estado del objeto
	# @return cadena con toda la informacion
        def to_s
            "S[" + @protection.to_s + "," + @uses.to_s + "]*"
        end

    end

#Main
escudo = Shield.new(3.0,5)

puts escudo.inspect

escudo.protect

puts escudo.inspect

puts escudo.discard

puts escudo.to_s

end



