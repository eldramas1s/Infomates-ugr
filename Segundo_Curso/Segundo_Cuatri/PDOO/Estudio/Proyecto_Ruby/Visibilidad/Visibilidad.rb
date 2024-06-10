module Visibilidad
  class Padre
    
    private 
    def privado
	puts "Privado Padre"
    end

    protected
    def protegido
	puts "Protegido Padre"
    end
    
    public 
    def publico
	puts "Publico Padre"
    end

    def test(p)
      privado
      self.privado
      #p.privado
      protegido
      self.protegido
      p.protegido
    end
  end
  class Hija < Padre
    def test(p)
      privado 
      self.privado
#	p.privado
      p.protegido
      protegido
      self.protegido
      publico
      self.publico
      p.publico
    end
  end

  #Padre.new.test(Padre.new)
  #p = Padre.new

  #p.privado
  #p.protegido
  #p.publico
  
  Hija.new.test(Hija.new)
  Hija.new.test(Padre.new)
  h = Hija.new
#  h.privado
#  h.protegido
  h.publico
end
module Externo
    class Hija2 < Visibilidad::Padre	
	protected
	def protegido 
	    puts "Protegido Hija2"
	end

	private
	def privado
	   puts "Privado Hija2"

	end
	
	public
	def test (o)
	    privado
	    o.protegido
	    protegido
	    o.publico
	end
    end
h2 = Hija2.new
h2.test(Hija2.new)
h2.test(Visibilidad::Hija.new)
h2.test(Visibilidad::Padre.new)
end    
