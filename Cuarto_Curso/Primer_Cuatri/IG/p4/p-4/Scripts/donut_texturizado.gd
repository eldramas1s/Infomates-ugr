extends MeshInstance3D
@export var tipo :int=0
@export var reps_u : float=2.0
@export var reps_v : float=2.0
@export var eps : float=0.001

func _ready():
	var mesh_instance = MeshInstance3D.new()
	mesh_instance.mesh =Utilidades.generarDonutUV(tipo,eps,reps_u,reps_v)
	
	var mat := StandardMaterial3D.new()
	mat.albedo_texture = Utilidades.CargarTextura("res://texturas/ea-textura-cuadricula.jpeg")  # Misma textura en todas las caras
	mesh_instance.material_override = mat

	add_child(mesh_instance)
