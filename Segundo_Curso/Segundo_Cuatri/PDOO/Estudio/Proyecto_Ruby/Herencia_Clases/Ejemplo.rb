module HerenciaClases
    class Padre

	@atributo_clase1 = 1
	@atributo_clase2 = 2
	@@atributo_clase3 = 0

	def self.salida
	    puts @atributo_clase1
	    puts @atributo_clase2 unless @atributo_clase2.nil?
	    puts @@atributo_clase3
	end

	def self.salida2
	    salida
	end
    end

    Padre.salida

    class Hija < Padre

	@atributo_clase1 = 3
	@@atributo_clase3 = 5

	def self.salida
	    super
#	    puts @atributo_clase1
	end
    end

    Padre.salida
    Hija.salida
    Padre.salida2
    Hija.salida2
end
