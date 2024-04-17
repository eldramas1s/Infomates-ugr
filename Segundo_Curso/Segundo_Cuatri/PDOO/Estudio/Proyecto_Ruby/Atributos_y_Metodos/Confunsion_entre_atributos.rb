class Clase
  @@variable = "De clase"
  @variable = "De Instancia de la clase"

  def initialize()
    @variable = "De Instancia"
  end

  def self.getter()
    puts "#{@variable} \n"
    puts "#{@@variable}"
  end
end

object = Clase.new
Clase.getter
puts object.inspect
