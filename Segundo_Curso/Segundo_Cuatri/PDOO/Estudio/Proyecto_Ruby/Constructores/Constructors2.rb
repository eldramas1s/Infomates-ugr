class RestrictedPoint3D

#No le gusta a lastra

	@@LIMIT_MAX = 100 
	@@LIMIT_MIN = 0

	private
	def restric_to_range(a)
		result = [@@LIMIT_MIN,a].max
		result = [a,@@LIMIT_MAX].min
		result
	end
	# def initialize (x,y,z=0) no importa el orden si tomamos parametros
	# nombrados:
	# def initialize (x:,y:,z:0) de esta forma puedo llamar
	# point = RestrictedPoint3D.new(y:1,z:9,x:1)
	def initialize (x,y,*z) # con el * indicamos que ese parámetro puede o
				# no aparecer
		@x = restric_to_range(x)
		@y = restric_to_range(y)
		if(z.size != 0) then
			z_param = z[0]
		else
			z_param = 0
		end
		@z = restric_to_range(z_param)
	end
	# Las variables locales no tienen visibilidad de bloque, solo de 
	# funcion
end

puts RestrictedPoint3D.new(1,1,1,2,5,8).inspect #solo tomara el numero de 
						#parametros dados en la 
						#definicion,es decir 3

#puts RestrictedPoint3D.new_2D(1,1).inspect

#puts RestrictedPoint3D.new(1,1,1) #Da error pues new es privado
