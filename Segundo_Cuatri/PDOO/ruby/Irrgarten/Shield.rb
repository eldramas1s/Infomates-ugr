#encoding: UTF-8

#require 'Dice'
# TODO: revisar por Airam
module Shield
    class Shield
        def initialize(defense,durability)
            @protection = defense   
            @uses = durability
        end
        
        def protect
            prt_val = 0
                if @uses > 0 then
                    prt_val = @protection
                    @uses -= 1
                end
            prt_val
        end
 
	def discard
		Dice::discarElement(@uses)
	end
        
        def to_s
            "S[" + @protection + "," + @uses + "]*"
        end

    end
end
