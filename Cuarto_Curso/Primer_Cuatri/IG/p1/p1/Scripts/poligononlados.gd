## Nombre: Lucas, Apellidos: Hidalgo Herrera, Titulación: GIM
## email: lucashidalgo@correo.ugr.es, DNI o pasaporte: 26512990Q

extends MeshInstance3D
@export var n : int = 8
@export var rad : float = 0.5
@export var eje : int = 0
@export var centro : Vector3 = Vector3(0.5,0.5,0)
func _ready():
	# Material a usar 
	var mat := StandardMaterial3D.new() 
	mat.shading_mode = BaseMaterial3D.SHADING_MODE_UNSHADED  # Sin iluminacion
	mat.cull_mode = BaseMaterial3D.CULL_DISABLED
	mat.vertex_color_use_as_albedo = true		# Permite difuminado de colores
	
	# Creacion de la instancia de malla
	var poligonon = Propio.ArrayMeshPoligonoRegular(n,rad,eje,centro)
	var mesh_instance = MeshInstance3D.new()
	mesh_instance.mesh = poligonon
	mesh_instance.material_override = mat
	add_child(mesh_instance)
