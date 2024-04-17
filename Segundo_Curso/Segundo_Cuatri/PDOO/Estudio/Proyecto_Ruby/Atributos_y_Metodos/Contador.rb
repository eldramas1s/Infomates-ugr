class Persona
  @@num_personas = 0

  def self.num_personas
    @@num_personas
  end

  def initialize(un_nombre)
    @nombre = un_nombre
    @@num_personas += 1
  end
end

pepe = Persona.new("juan")
juan = Persona.new("pepe")
puts pepe.inspect
puts Persona.num_personas
