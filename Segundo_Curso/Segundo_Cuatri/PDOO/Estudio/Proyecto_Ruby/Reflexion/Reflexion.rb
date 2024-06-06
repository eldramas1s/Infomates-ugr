module Reflexion
    class Libro
	def initialize(titulo)
	    @titulo = titulo
	end
    end

    libro1 = Libro.new("Alexandra y las siete pruebas")

    Libro.class_eval do def publicacion(año)
			   @año = año
			end
		     end
    libro1.publicacion(2014)
    puts libro1.inspect

    libro2 = Libro.new("PeterPan")
    puts libro2.inspect

    libro2.instance_eval do def autor()
			    "J.K.Rowlings"
			    end
		 	 end
    libro2.publicacion(0000)
    puts libro2.inspect
    puts libro2.autor

#    puts libro1.autor No existe ese metodo para esta instancia. 
end


