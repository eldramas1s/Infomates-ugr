#encoding UTF-8
module Basico
	module ColorPelo
		MORENO= 	:moreno
		CASTAÑO= 	:castaño
		PELIRROJO=	:pelirrojo
		RUBIO= 		:rubio
		TEÑIDO=		:teñido
	end
	
	class Persona
		def initialize (n,e,p)
			@nombre=n
			@edad=e
			@pelo=p
		end
		public
		def saluda
			puts "Hola soy " +@nombre
		end
	end
	
	p=Persona.new("Pepe",10,ColorPelo::RUBIO)
	p.saluda
end
