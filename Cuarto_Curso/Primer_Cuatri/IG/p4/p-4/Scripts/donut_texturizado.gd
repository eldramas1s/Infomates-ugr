extends MeshInstance3D

func _ready():
	var mesh_instance = MeshInstance3D.new()
	mesh_instance.mesh =Utilidades.generarDonutUV(1)
	
	var mat := StandardMaterial3D.new()
	mat.albedo_texture = Utilidades.CargarTextura("res://texturas/ea-textura-cuadricula.jpeg")  # Misma textura en todas las caras
	mesh_instance.material_override = mat

	add_child(mesh_instance)
