module Visibilidad
  class Padre
    
    private 
    def privado
    end

    protected
    def protegido
    end
    
    public 
    def publico
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
      p.privado
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
  h.privado
  h,protegido
  h.publico
end
