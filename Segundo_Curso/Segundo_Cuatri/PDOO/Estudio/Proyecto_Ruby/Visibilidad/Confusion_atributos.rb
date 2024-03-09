module Confusion
	class Clase
		@@variable = 'De clase'
		@variable = 'De instancia de la clase'
		def initialize
			@variable = 'De instancia'
		end
		def muestraValores
			puts @@variable
			puts @variable
		end

		def self.muestraValores
			puts @@variable
			puts @variable
		end
	end
	
	objeto = Clase.new
	objeto.muestraValores
	Clase.muestraValores
end

