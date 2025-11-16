## Nombre: Lucas, Apellidos: Hidalgo Herrera, Titulación: GIM
## email: lucashidalgo@correo.ugr.es, DNI o pasaporte: 26512990Q

extends MeshInstance3D

@export var n : int = 8
@export var rad1 : float = 0.5
@export var rad2 : float = 0.25
@export var eje : int = 0
@export var centro : Vector3 = Vector3(0.5,0.5,0)

func _ready():
	# Material a usar
	var mat := StandardMaterial3D.new() 
	mat.shading_mode = BaseMaterial3D.SHADING_MODE_UNSHADED		# Sin iluminacion
	mat.cull_mode = BaseMaterial3D.CULL_DISABLED				# Sin cribado de caras (2D)
	mat.vertex_color_use_as_albedo = true						# Difuminado de colores segun vertices
	
	# Creacion de la instancia de malla
	var estrella = Propio.ArrayMeshEstrellaZ(n,rad1,rad2,eje, centro)
	var mesh_instance = MeshInstance3D.new()
	
	mesh_instance.mesh = estrella
	mesh_instance.material_override = mat
	add_child(mesh_instance)				# Con este comando estamos anadiendo el hijo con la malla a EstrellaZ

# Necesito el eje como parametro porque permito cualquier centro, si solo permitiera en los planos x=0, y=0 o z=0 podria obviarlo
