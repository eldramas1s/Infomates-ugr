require 'date'

class Persona
	@MAYORIA_EDAD=18	#De instancia de la clase
	def self.edad_legal
		@MAYORIA_EDAD
	end
	def initialize (fecha)
		@fecha_nacimiento = fecha	#Local
	end
	
	def mayor_edad
		ahora = Date.today	#Variable local
		edad = ahora.year - @fecha_nacimiento.year - 1
	
		if (ahora.month > @fecha_nacimiento.month)
			edad+=1
		else
			if(ahora.month == @fecha_nacimiento.month)
				if(ahora.day >= @fecha_nacimiento.day)
					edad+=1
				end
			end
		end
		return (edad>=elf.class.edad_legal) #De clase
	end
end

