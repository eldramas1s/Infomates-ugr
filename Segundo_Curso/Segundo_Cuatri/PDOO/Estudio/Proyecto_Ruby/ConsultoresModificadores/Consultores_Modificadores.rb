require 'date'

class Persona

  @@MAYOR = 18
  @PRUEBA = 0
  def initialize(años)
    @años = años
    @prueba = "Tu puta madre"
  end

  attr_reader :años
  attr_writer :años
  attr_reader :prueba

  def self.mayor_edad=edad
    @@MAYOR = edad
    puts @@MAYOR
  end

  def Prueba
    puts @@MAYOR
    @@MAYOR = 2
    puts @@MAYOR
  end
end

p = Persona.new(1)
puts p.años
p.años=2
puts p.años
Persona.mayor_edad=11
puts p.inspect
p.Prueba
