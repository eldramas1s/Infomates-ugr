class RestrictedPoint3D
# Un error muy comun es definir new o alguno de sus homologos con codigo 
# similar al que se pondría en initialize; en este caso estamos 
# inicializando atributos de instancia que no están creados pues esa es la 
# función de initialize(este metodo siempre debe de estar en nuestra clase como
# metodo de clase privado)	
	@@LIMIT_MAX = 100 
	@@LIMIT_MIN = 0
	

	def self.new_3D(x,y,z)
		new(x,y,z)
	end

	def self.new_2D(x,y)
		new(x,y,0)
	end
	private_class_method :new
	private
	def restric_to_range(a)
		result = [@@LIMIT_MIN,a].max
		result = [a,@@LIMIT_MAX].min
		result
	end
	
	def initialize (x,y,z) 
		@x = restric_to_range(x)
		@y = restric_to_range(y)
		@z = restric_to_range(z)
	end

end

puts RestrictedPoint3D.new_3D(1,1,1).inspect

puts RestrictedPoint3D.new_2D(1,1).inspect

#puts RestrictedPoint3D.new(1,1,1) #Da error pues new es privado
