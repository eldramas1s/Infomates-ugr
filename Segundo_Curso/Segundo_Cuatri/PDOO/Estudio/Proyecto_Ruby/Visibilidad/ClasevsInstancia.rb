require 'date'

class Persona
	@@MAYORIA_EDAD=18	#De clase
		
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
		return (edad>=@@MAYORIA_EDAD) #De clase
	end
end

