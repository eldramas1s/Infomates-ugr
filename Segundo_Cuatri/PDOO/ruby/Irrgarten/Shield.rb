#encoding: UTF-8
module Shield
    class Shield #No interpretado
        def initialize(defense,durability)
            @protection = defense
            @uses = durability
        end
        
        def protect
            prt_val = 0
            #unless??
            unless @uses > 0
                prt_val = @protection
                @uses -= 1
            end
            return prt_val
        end 
        
        def to_s
            return "S[" + @protection + "," + @uses + "]*"
        end
    end
end