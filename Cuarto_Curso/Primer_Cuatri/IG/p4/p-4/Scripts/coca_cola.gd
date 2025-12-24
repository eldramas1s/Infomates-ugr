extends MeshInstance3D

@export var n : int=200

func _ready():
	var perfil := PackedVector2Array([
		Vector2(0.3,-0.75),
		Vector2(0.5,0.-0.55),
		Vector2(0.5,0.55),
		Vector2(0.3,0.75)
	])
	
	var mesh_instance = MeshInstance3D.new()
	mesh_instance.mesh =Propio.revolucionaUV(perfil,n,false,false)
	
	mesh_instance.transform = Transform3D().translated(Vector3(0,0.75,0))*Transform3D().rotated(Vector3(1,0,0),PI)
	
	var mat := StandardMaterial3D.new()
	mat.albedo_texture = Utilidades.CargarTextura("res://texturas/text-lata-1.jpg")  # Misma textura en todas las caras
	mesh_instance.material_override = mat

	add_child(mesh_instance)
