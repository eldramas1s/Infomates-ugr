extends MeshInstance3D

@export var d : int = 1
func _ready():
	var mesh_instance = MeshInstance3D.new()
	mesh_instance.mesh = Propio.ArrayMeshCubo24_CCT(d)

	var mat := StandardMaterial3D.new()
	mat.albedo_texture = Utilidades.CargarTextura("res://texturas/logo-ugr-cuadr-opaco.png")  # Misma textura en todas las caras
	mesh_instance.material_override = mat

	add_child(mesh_instance)
