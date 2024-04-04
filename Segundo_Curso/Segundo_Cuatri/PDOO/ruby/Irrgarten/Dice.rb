#encoding: UTF-8

module Irrgarten
    # Clase encargada de tomar las decisiones de azar en la partida
    class Dice
   	#Atributos de clase
	@@MAX_USES = 5			# Numero maximo de usos de armas y escudos
        @@MAX_ITELLIGENCE = 10.0	# Valor maximo para la inteligencia de jugadores y monstruos
        @@MAX_STRENGTH = 10.0		# Valor maximo para la fuerza de jugadores y monstruos
        @@RESURRECT_PROB = 0.3		# Numero maximo de armas recibidas al ganar un combate
        @@WEAPONS_REWARD = 2		# Probabilidad de que un jugador sea resucitado en cada turno
        @@SHIELDS_REWARD = 3		# Numero maximo de escudos recibidos al ganar un combate
        @@HEALTH_REWARD = 5		# Numero maximo de unidades de salud recibidas al ganar un combate
        @@MAX_ATTACK = 3		# Maxima potencia de armas
        @@MAX_SHIELD = 2		# Maxima potencia de escudos
	@@generator = Random.new	# Encargado de las decisiones de azar

	# No hay initialize creado por nosotros pues no se van a crear objetos
	
	# Metodo de clase encargado de generar una posicion en el tablero
	# @param max Posicion maxima de una dimension del tablero
	# @return Posicion en esa dimension del tablero 
	def self.randomPos(max)
	    @@generator.rand(max)
	end
	
	# Metodo de clase encargado de decidir que jugador empieza
	# @param players Numero de jugadores de la partida
	# @return Entero que representa el jugador que empieza
	def self.whoStarts(players)
	    @@generator.rand(players)
	end
	
	# Metodo de clase encargado de determinar un valor de inteligencia
	# @return Valor de inteligencia
	def self.randomIntelligence
	    (@@generator.rand(@@MAX_ITELLIGENCE))
	end

	# Metodo de clase encargado de determinar un valor de fuerza
	# @return Valor de fuerza
	def self.randomStrength
	    (@@generator.rand(@@MAX_STRENGTH))
	end

	# Metodo de clase encargado de determinar una probabilidad de resurrecion
	# @return Valor de probabilidad de resurrecion 
	def self.resurrectPlayer
	    @@generator.rand(1.0) < @@RESURRECT_PROB
	end

	# Metodo de clase encargado de determinar un valor de la cantidad de armas que puede 
	# recibir el jugador al final del combate
	# @return Valor de dicha cantidad
	def self.weaponsReward
	    @@generator.rand(@@WEAPONS_REWARD)
	end

	# Metodo de clase encargado de determinar un valor de la cantidad de escudos que puede
	# recibir un jugador al final de un combate
	# @return Valor de dicha cantidad
	def self.shieldsReward
	    @@generator.rand(@@SHIELDS_REWARD)
	end

	# Metodo de clase encargado de determinar la cantidad de unidades de salud que recibe un 
	# jugador al terminar un combate
	# @return Valor de las unidades de salud
	def self.healthReward
	    @@generator.rand(@@HEALTH_REWARD+1)
	end

	# Metodo de clase encargado de determinar un valor de poder de un arma
	# @return Poder del arma
	def self.weaponPower
	    @@generator.rand(@@MAX_ATTACK+1)
	end

	# Metodo de clase encargado de determinar un valor de escudo
	# @return Valor de escudo
	def self.shieldPower
	    @@generator.rand(@@MAX_SHIELD+1)
	end

	# Metodo de clase encargado de determinar el numero de usos que se le asignaran a un arma
	# o escudo
	# @return Usos de dichos objetos
	def self.usesLeft
	    @@generator.rand(@@MAX_USES+1)
	end
	
	# Metodo de clase que devuelve la cantidad de competencia aplicada.
	# @return Competencia aplicada  
	def self.intensity(competence)
	    @@generator.rand(competence)
	end
	
	# Metodo de clase asigna la probabilidad de deshechar un objeto equipado
	# @return true si se descarta
	# 	  false si no se descarta
	def self.discardElement(usesLeft)
	    (@@generator.rand() < (@@MAX_USES-usesLeft).to_f()/@@MAX_USES.to_f())
   	end
	
    end#class
end#module
