class Prueba 
	def self.metodoClasePublico
		puts 'publico de clase'
	end
	
	private #solo afecta a los metodos de instancia
	
	def self.metodoClasePrivado #sigue siendo publico
		puts 'privado de clase'
	end
	
	def metodoInstanciaPrivado
		puts 'privado de instancia'
	end

	#Otra forma de hacerlo privado
	
	private :metodoInstanciaPrivado
	
	#Privatizar los metodos de clase
	
	private_class_method :metodoClasePrivado
	
end

Prueba.metodoClasePublico
#Prueba.metodoClasePrivado
#Prueba.metodoInstanciaProvado
#Prueba.new.metodoInstanciaPrivado
#Prueba.new.metodoClasePublico 
	

