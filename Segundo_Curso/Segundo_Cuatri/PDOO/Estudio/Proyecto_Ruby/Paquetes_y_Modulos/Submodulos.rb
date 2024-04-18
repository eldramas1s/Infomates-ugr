module Externo
  class A
  end

  module Interno
    class B
    end
  end
end

module Test
  def Test
    puts "testing"
  end
end

class C
  include Test
end

puts a = Externo::A.new.inspect
puts b = Externo::Interno::B.new.inspect
puts c = C.new.Test
