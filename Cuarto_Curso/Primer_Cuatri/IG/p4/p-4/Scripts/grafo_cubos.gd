## Nombre: Lucas, Apellidos: Hidalgo Herrera, Titulación: GIM
## email: lucashidalgo@correo.ugr.es, DNI o pasaporte: 26512990Q
extends Node3D

@export var n : int = 10		# numero de divisiones en el eje x		# numero de divisiones en el eje y
@export var inferiorIzquierda : Vector3 = Vector3(0,0,0)
@export var longitudInferior : float = 1.0		# Longitud del lado inferior
@export var longitudIzquierda : float = 1.0		# Longitud del lado izquierdo

@export var rotation_speed := 2.5*2*PI 
var activa_izquierda : bool = false
var activa_drcha : bool = false

var tranform : bool = true

func _ready():
	
	## Nodo del que parte toda la estructura
	var cubo_grande = Node3D.new()
	cubo_grande.transform = Transform3D.IDENTITY
	add_child(cubo_grande)
	
	## Materiales a usar
	var mat := StandardMaterial3D.new() 
	mat.shading_mode = BaseMaterial3D.SHADING_MODE_UNSHADED		# Sin iluminacion
	mat.cull_mode = BaseMaterial3D.CULL_DISABLED				# Sin cribado de caras (2D)
	mat.vertex_color_use_as_albedo = true						# Difuminado de colores segun vertices
	
	var mat_cub := StandardMaterial3D.new() 
	mat_cub.albedo_color = Color( 1, 1, 1 )
	mat_cub.shading_mode = BaseMaterial3D.SHADING_MODE_UNSHADED
	mat_cub.cull_mode = BaseMaterial3D.CULL_DISABLED
	
	var vertex : PackedVector3Array = []
	var indexes : PackedInt32Array = []
	var colors : PackedColorArray = []
	
	var cubo = Propio.CrearCubo24()	#Esta centrado en (0.5,0.5,0.5)	
	# cubo.material_override = mat 	!!! Falla porque el arrayMesh no tiene atributo material_override
	#								!!! Se tendria que hacer con cubo.surfece_set_material(0,mat)
	var caracubo = Propio.ArrayMeshRejilla(n,n,0,vertex,indexes,colors,Vector3(0,0,0),longitudInferior,longitudIzquierda)
	
	var cubos_tranform = Transform3D().translated(Vector3(0.5,0.5,-0.5))* Transform3D().rotated(Vector3(1,0,0),PI/2) *  Transform3D().scaled(Vector3(0.25,0.5,0.25))
	
	if(tranform):
		#Cara trasera
		var trasera = MeshInstance3D.new()
		trasera.mesh = caracubo
		trasera.material_override = mat
		trasera.transform = Transform3D().translated(Vector3(-0.5, -0.5, -0.5))
		
		#cubo trasera
		var c_trasero = MeshInstance3D.new()
		c_trasero.mesh=cubo
		c_trasero.material_override=mat_cub
		trasera.add_child(c_trasero)
		c_trasero.transform = cubos_tranform
		
		cubo_grande.add_child(trasera)
		
		# Cara delantera
		var delantera = MeshInstance3D.new()
		delantera.mesh = caracubo
		delantera.material_override = mat
		delantera.transform = Transform3D().translated(Vector3(-0.5, -0.5, 0.5))
		
		#cubo delantera
		var c_delantera = MeshInstance3D.new()
		c_delantera.mesh=cubo
		c_delantera.material_override=mat_cub
		delantera.add_child(c_delantera)
		c_delantera.transform = Transform3D().scaled(Vector3(0.25,0.5,0.25))
		c_delantera.transform = Transform3D().rotated(Vector3(1,0,0),PI/2)*c_delantera.transform
		c_delantera.transform = Transform3D().translated(Vector3(0.5,0.5,0.5))* c_delantera.transform
		cubo_grande.add_child(delantera)
		
		 #Cara inferior
		var inferior = MeshInstance3D.new()
		inferior.mesh = caracubo
		inferior.material_override = mat
		inferior.transform = Transform3D().rotated(Vector3(1,0,0),-PI/2)
		inferior.transform = Transform3D().translated(Vector3(-0.5, -0.5, 0.5))*inferior.transform
		
		#cubo inferior
		var c_inferior = MeshInstance3D.new()
		c_inferior.mesh=cubo
		c_inferior.material_override=mat_cub
		inferior.add_child(c_inferior)
		c_inferior.transform = cubos_tranform	
		cubo_grande.add_child(inferior)
		#Primero escalariamos pero no hace falta
		
		# Cara superior
		var superior = MeshInstance3D.new()
		superior.mesh = caracubo
		superior.material_override = mat
		superior.transform = Transform3D().rotated(Vector3(1,0,0),PI/2)
		superior.transform = Transform3D().translated(Vector3(-0.5,0.5,-0.5))*superior.transform
	
		#cubo superior
		var c_superior = MeshInstance3D.new()
		c_superior.mesh=cubo
		c_superior.material_override=mat_cub
		superior.add_child(c_superior)
		c_superior.transform = cubos_tranform
		
		cubo_grande.add_child(superior)
		
		#Cara izquierda
		var izquierda = MeshInstance3D.new()
		izquierda.mesh = caracubo
		izquierda.material_override = mat
		izquierda.transform = Transform3D().rotated(Vector3(0,1,0),PI/2)
		izquierda.transform = Transform3D().translated(Vector3(-0.5,-0.5,0.5)) * izquierda.transform
	
		#cubo izquierda
		var c_izquierda = MeshInstance3D.new()
		c_izquierda.mesh=cubo
		c_izquierda.material_override=mat_cub
		izquierda.add_child(c_izquierda)
		c_izquierda.transform = cubos_tranform		
		
		cubo_grande.add_child(izquierda)

		#Cara derecha
		var derecha = MeshInstance3D.new()
		derecha.mesh = caracubo
		derecha.material_override = mat
		derecha.transform = Transform3D().rotated(Vector3(0,1,0),-PI/2)
		derecha.transform = Transform3D().translated(Vector3(0.5,-0.5,-0.5))*derecha.transform

		#cubo derecha
		var c_derecha = MeshInstance3D.new()
		c_derecha.mesh=cubo
		c_derecha.material_override=mat_cub
		derecha.add_child(c_derecha)
		c_derecha.transform = cubos_tranform	
		
		cubo_grande.add_child(derecha)
		
		
	else:
	
		#!!!! hay que tener cuidado en como aplicamos las transformaciones
		
		##Cara trasera
		var trasera = MeshInstance3D.new()
		trasera.mesh = caracubo
		trasera.material_override = mat
		trasera.position = Vector3(-0.5,-0.5,-0.5)
		#cubo trasera
		var c_trasero = MeshInstance3D.new()
		c_trasero.mesh=cubo
		c_trasero.material_override=mat_cub
		trasera.add_child(c_trasero)
		c_trasero.scale = Vector3(0.25,0.5,0.25)
		c_trasero.rotate_x(PI/2)
		c_trasero.position = Vector3(0.5,0.5,-0.5)
		cubo_grande.add_child(trasera)
		
		# Cara delantera
		var delantera = MeshInstance3D.new()
		delantera.mesh = caracubo
		delantera.material_override = mat
		delantera.position = Vector3(-0.5,-0.5,0.5)
		#cubo delantera
		var c_delantera = MeshInstance3D.new()
		c_delantera.mesh=cubo
		c_delantera.material_override=mat_cub
		delantera.add_child(c_delantera)
		c_delantera.scale = Vector3(0.25,0.5,0.25)
		c_delantera.rotate_x(PI/2)
		c_delantera.position = Vector3(0.5,0.5,0.5)
		cubo_grande.add_child(delantera)
		
		# Cara inferior
		var inferior = MeshInstance3D.new()
		inferior.mesh = caracubo
		inferior.material_override = mat
		inferior.rotate_x(-PI/2)
		inferior.position=Vector3(-0.5,-0.5,0.5)
		#cubo inferior
		var c_inferior = MeshInstance3D.new()
		c_inferior.mesh=cubo
		c_inferior.material_override=mat_cub
		inferior.add_child(c_inferior)
		c_inferior.scale = Vector3(0.25,0.5,0.25)
		c_inferior.rotate_x(-PI/2)
		c_inferior.position = Vector3(0.5,0.5,-0.5)
		cubo_grande.add_child(inferior)
		#Primero escalariamos pero no hace falta
		
		
		# Cara superior
		var superior = MeshInstance3D.new()
		superior.mesh = caracubo
		superior.material_override = mat
		superior.rotate_x(PI/2)
		superior.position = Vector3(-0.5,0.5,-0.5)
		#cubo superior
		var c_superior = MeshInstance3D.new()
		c_superior.mesh=cubo
		c_superior.material_override=mat_cub
		superior.add_child(c_superior)
		c_superior.scale = Vector3(0.25,0.5,0.25)
		c_superior.rotate_x(PI/2)
		c_superior.position = Vector3(0.5,0.5,-0.5)
		cubo_grande.add_child(superior)
		#Primero escalariamos pero no hace falta
		
		#Cara izquierda
		var izquierda = MeshInstance3D.new()
		izquierda.mesh = caracubo
		izquierda.material_override = mat
		izquierda.rotate_y(PI/2)
		izquierda.position = Vector3(-0.5,-0.5,0.5)
		#cubo izquierda
		var c_izquierda = MeshInstance3D.new()
		c_izquierda.mesh=cubo
		c_izquierda.material_override=mat_cub
		izquierda.add_child(c_izquierda)
		c_izquierda.scale = Vector3(0.25,0.5,0.25)
		c_izquierda.rotate_x(PI/2)
		c_izquierda.position = Vector3(0.5,0.5,-0.5)
		cubo_grande.add_child(izquierda)
		#Primero escalariamos pero no hace falta

	
		#Cara derecha
		var derecha = MeshInstance3D.new()
		derecha.mesh = caracubo
		derecha.material_override = mat
		derecha.rotate_y(-PI/2)
		derecha.position = Vector3(0.5,-0.5,-0.5)
		#cubo derecha
		var c_derecha = MeshInstance3D.new()
		c_derecha.mesh=cubo
		c_derecha.material_override=mat_cub
		derecha.add_child(c_derecha)
		c_derecha.scale = Vector3(0.25,0.5,0.25)
		c_derecha.rotate_x(-PI/2)
		c_derecha.position = Vector3(0.5,0.5,-0.5)
		cubo_grande.add_child(derecha)
		#Primero escalariamos pero no hace falta
	
func _process(delta:float):
	# Si se pulsa "1" rotamos a derecha
	if Input.is_action_just_pressed("Rotarderecha") and !activa_izquierda:
		activa_drcha = !activa_drcha
	if activa_drcha:
		#cubo.rotate(Vector3(1, 0, 0), angulo)  para eje X local	(Vector3.RIGHT)
		#cubo.rotate(Vector3(0, 1, 0), angulo)  para eje Y local	(Vector3.UP)
		#cubo.rotate(Vector3(0, 0, 1), angulo)  para eje Z local	(Vector3.BACK)

		for i in range(6):
			get_child(0).get_child(i).get_child(0).rotate(Vector3.BACK,rotation_speed*delta)
		
		
	# Si se pulsa "2" rotamos a izquierda
	if Input.is_action_just_pressed("RotarIzquierda") and !activa_drcha:
		activa_izquierda = !activa_izquierda
	if activa_izquierda:
		for i in range(6):
			get_child(0).get_child(i).get_child(0).rotate(Vector3.BACK,-rotation_speed*delta)
