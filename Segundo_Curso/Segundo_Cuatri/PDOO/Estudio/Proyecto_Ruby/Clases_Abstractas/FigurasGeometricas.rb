module Figuras
  class Figura
    def initialize
    end
    def area
    end
    private_class_method :new
  end

  class Cuadrado < Figuras
   def initialize(l)
     @l = l
   end

   def area
     @l*@l
   end
   public_class_method :new
  end

  class Circulo < Figuras
    def initialize(r)
      @r=r
    end
    
    def area
      3.14*@r*@r
    end

    public_class_method :new
  end
  figuras = []
  figuras << Circulo.new(2)
  figuras << Cuadrado.new(2)

  for element in figuras
    puts element.area
  end
end

