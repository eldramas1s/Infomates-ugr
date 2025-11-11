extends Camera3D
func _ready():
	position = Vector3( 1.5, 1.5, 2.0 )
	look_at( Vector3( 0.0, 0.0, 0.0 ), Vector3.UP )	# Le digo a la camara que mire al 0.0.0
