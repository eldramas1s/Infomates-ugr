## Nombre: Lucas, Apellidos: Hidalgo Herrera, Titulación: GIM
## email: lucashidalgo@correo.ugr.es, DNI o pasaporte: 26512990Q
extends Node3D
@export var n : int=4 # numero de radios
@export var m : int=5 # numero de esferas por radio
@export var radio_in :int = 1
@export var distancia_radial : int = 2
@export var radio_esf : float = 0.5

func _ready():
	var escena = Node3D.new()
	add_child(escena)
	
	var material = StandardMaterial3D.new()
	material.albedo_color= Color(0.5,0,0.7)
	material.roughness = 0.0
	material.metallic = 0.5
	for i in range(1,n+1):	#Para cada radio
		for j in range(1,m+1):	#Hay m esferas
			
			var mesh_ij=creaEsfera((radio_in+(i-1)*distancia_radial)*Vector3(cos((2*PI*j)/m),0,sin((2*PI*j)/m)),radio_esf)
			mesh_ij.material_override = material
			
			var body = StaticBody3D.new()
			
			var collision = CollisionShape3D.new()
			var shape = SphereShape3D.new()
			shape.radius = radio_esf
			collision.shape = shape
			collision.position = Vector3(0,0,0)
			
			body.add_child(collision)
			mesh_ij.add_child(body)
			escena.add_child(mesh_ij)

func creaEsfera(centro : Vector3 = Vector3(0,0,0) , radio : float = 1.0)->MeshInstance3D:
	var mesh_instance = MeshInstance3D.new()
	var esfera_mesh = SphereMesh.new()
	esfera_mesh.radius = radio
	esfera_mesh.height = radio * 2.0
	mesh_instance.mesh = esfera_mesh
	mesh_instance.position = centro  # Centra la esfera
	return mesh_instance
	
