# Enunciado:
# Dado el siguiente codigo:

# Codigo:

module Primero

    class Padre
	def publico(p)	    # Linea 35: Como p es Hija, y recordando que estamos en Ruby:
	    privado	    # Se ejecuta a la perfeccion pues es un metodo privado del objeto 
			    # implicito
#	    p.privado	    # Error, estamos accediendo a un metodo privado con un
			    # receptor de mensaje explicito
	    protegido	    # Se ejecuta perfectamente, esta disponible para el objeto implicito
	    p.protegido	    # Hija es subclase de padre luego puede ejecutarse un elemento 
			    # protegido de Hija
	end

	private

	def privado
	end

	protected 
	def protegido
	end
    end
end

module Segundo
    class Hija < Primero::Padre
	def publico(p)	    # Linea 36, pasamos un Padre como argumento
	    privado	    # Se ejecuta bien, es un metodo privado de Padre y estoy en la clase
			    # Hija
#	    p.privado	    # Error, estoy llamando a un metodo privado con una instancia
			    # (receptor de mensaje explicito)
	    protegido	    # Se ejecuta bien, es un metodo disponible para Hija por heredar de
			    # Padre, se ejecuta el codigo de Padre 
	    p.protegido	    # Una Hija es un Padre a todos los efectos, luego una instancia de 
			    # Padre puede acceder a cada uno de sus protegidos desde el codigo de
			    # Hija
	end
    end
end

Primero::Padre.new.publico(Segundo::Hija.new)
Segundo::Hija.new.publico(Primero::Padre.new)

#Empezando en las lineas 35 y 36 indicar en las lineas donde se produce algun error relacionado con la accesibilidad (visibilidad) de metodos, asumiendo que cada error es ignorado y que la ejecucion puede continuar.
