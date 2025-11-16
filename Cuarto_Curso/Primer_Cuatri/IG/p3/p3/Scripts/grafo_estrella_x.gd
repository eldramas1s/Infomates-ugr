## Nombre: Lucas, Apellidos: Hidalgo Herrera, Titulación: GIM
## email: lucashidalgo@correo.ugr.es, DNI o pasaporte: 26512990Q
extends Node3D

@export var n : int = 6
@export var rad1 : float = 1
@export var rad2 : float = 0.5
@export var eje : int = 2
@export var centro : Vector3 = Vector3(0,0,0)

@export var rotation_speed := 2.5*2*PI 
var activa_izquierda : bool = false
var activa_drcha : bool = false

func _ready():
	
	## Material a usar
	var mat_star := StandardMaterial3D.new() 
	mat_star.shading_mode = BaseMaterial3D.SHADING_MODE_UNSHADED		# Sin iluminacion
	mat_star.cull_mode = BaseMaterial3D.CULL_DISABLED				# Sin cribado de caras (2D)
	mat_star.vertex_color_use_as_albedo = true
	
	var mat_cono := StandardMaterial3D.new() 
	mat_cono.albedo_color = Color(1,1,1)
	mat_cono.shading_mode = BaseMaterial3D.SHADING_MODE_UNSHADED		# Sin iluminacion
	
	## Creacion de la instancia de malla
	var perfil = PackedVector2Array([Vector2(0,1),Vector2(1,0)])
	var m : int = 20
	var estrellaX = Propio.ArrayMeshEstrellaZ(n,rad1,rad2,eje,centro)
	var mesh_instance = MeshInstance3D.new()
	mesh_instance.mesh = estrellaX
	mesh_instance.material_override = mat_star
	add_child(mesh_instance)
	
	# Creamos la mesh del cono
	var mesh_cono : ArrayMesh
	match eje:
		0:
			mesh_cono = Propio.GeneraCono(perfil,m,1)
		1:
			mesh_cono = Propio.GeneraCono(perfil,m,0)
		2:
			mesh_cono = Propio.GeneraCono(perfil,m,1)
	
	# Situamos los conos y les asignamos una instancia con su material
	var angulo : float = 0.0
	var posicion : Vector3 = Vector3(0,0,0)
	# Situamos cada cono
	for i in range(n):
		# Calculamos el angulo de la posicion
		angulo = 2.0*PI*i/n
		# Calculamos la posicion
		match eje:
			0:
				posicion = centro + max(rad1,rad2)*Vector3(cos(angulo),sin(angulo),0)
			1:
				posicion = centro + max(rad1,rad2)*Vector3(sin(angulo),0,cos(angulo))
			2:
				posicion = centro + max(rad1,rad2)*Vector3(0,cos(angulo),sin(angulo))
		
		
		var mesh_instance_2 = MeshInstance3D.new()
		mesh_instance_2.mesh = mesh_cono
		mesh_instance_2.material_override=mat_cono
		add_child(mesh_instance_2)	
		mesh_instance_2.scale = Vector3(0.14,0.15,0.14)
		match eje:
			0:
				mesh_instance_2.rotate_z(angulo-PI/2)
			1:
				mesh_instance_2.rotate_y(angulo-PI/2)
			2:
				mesh_instance_2.rotate_x(angulo)
		mesh_instance_2.position = posicion
		
func _process(delta: float) -> void:
	
	# Si se pulsa "1" rotamos a derecha
	if Input.is_action_just_pressed("Rotarderecha") and !activa_izquierda:
		activa_drcha = !activa_drcha
	if activa_drcha:
		match eje:
			0:
				rotation.z += rotation_speed * delta
			1:
				rotation.y += rotation_speed * delta
			2:
				rotation.x += rotation_speed * delta
		
	
	# Si se pulsa "2" rotamos a izquierda
	if Input.is_action_just_pressed("RotarIzquierda") and !activa_drcha:
		activa_izquierda = !activa_izquierda
	if activa_izquierda:
		match eje:
			0:
				rotation.z += -rotation_speed * delta
			1:
				rotation.y += -rotation_speed * delta
			2:
				rotation.x += -rotation_speed * delta
