## Nombre: Lucas, Apellidos: Hidalgo Herrera, Titulación: GIM
## email: lucashidalgo@correo.ugr.es, DNI o pasaporte: 26512990Q
extends MeshInstance3D
@export var n := 100
@export var m := 99
@export var r_max := 1

func _ready():
	var mesh_instance = MeshInstance3D.new()
	mesh_instance.mesh = Propio.ArrayMeshDiscoUV(n,m,r_max)

	mesh_instance.transform = Transform3D().rotated(Vector3(1,0,0),PI/2)
	
	var mat := StandardMaterial3D.new()
	mat.albedo_texture = Utilidades.CargarTextura("res://texturas/ea-textura-cuadricula.jpeg")  # Misma textura en todas las caras
	mesh_instance.material_override = mat

	add_child(mesh_instance)
