module Pruebas
	class Persona
		@@num_personas = 0
		def self.num_personas
			@@num_personas
		end
		
		def initialize (un_nombre)
			@nombre = un_nombre
			@@num_personas += 1
		end
	end	
end
