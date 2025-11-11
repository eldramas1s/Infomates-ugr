## Nombre: Lucas, Apellidos: Hidalgo Herrera, Titulación: GIM
## email: lucashidalgo@correo.ugr.es, DNI o pasaporte: 26512990Q
extends Node3D

@export var n : int = 8
@export var rad1 : float = 1
@export var rad2 : float = 0.5
@export var eje : int = 2
@export var centro : Vector3 = Vector3(0,0,0)

@export var rotation_speed := 2.5*2*PI 
var activa_izquierda : bool = false
var activa_drcha : bool = false

func _ready():
	var perfil = PackedVector2Array([Vector2(0,1),Vector2(1,0)])
	var m : int = 20
	var estrellaX = ArrayMeshEstrellaZ(n,rad1,rad2,eje,centro)
	var mesh_instance = MeshInstance3D.new()
	mesh_instance.mesh = estrellaX
	add_child(mesh_instance)
	
	var mesh_cono : ArrayMesh
	match eje:
		0:
			mesh_cono = GeneraCono(perfil,m,1)
		1:
			mesh_cono = GeneraCono(perfil,m,0)
		2:
			mesh_cono = GeneraCono(perfil,m,1)
	
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

func ArrayMeshEstrellaZ(n: int, rad1 : float, rad2 : float, eje:int, centro : Vector3 = Vector3(0,0,0) ) -> ArrayMesh :
	
	var indexes : PackedInt32Array = []
	var vertex : PackedVector3Array = []
	var colors : PackedColorArray = []
	
	# Establecemos los radios
	var radg : float=max(rad1,rad2)
	var radp : float=min(rad1,rad2)
	
	assert(eje==0 or eje == 1 or eje==2, "No ha seleccionado ningun eje")
	
	match eje:
		0:
			#Eje z = 0
			#assert(centro.z==0, "z=0")	# Esta linea sirve para forzar que sea el plano z=0
			for i in range(n):
				vertex.append(radg*Vector3(cos((2*PI*i)/n),sin((2*PI*i)/n),0))
				vertex.append(radp*Vector3(cos(2*PI*(i+0.5)/n),sin(2*PI*(i+0.5)/n),0))
	
		1: 	
			# Eje y = 0
			#assert(centro.y==0, "y=0") # Esta linea sirve para forzar que sea el plano z=0
			for i in range(n):
				vertex.append(radg*Vector3(sin((2*PI*i)/n),0,cos((2*PI*i)/n)))
				vertex.append(radp*Vector3(sin((2*PI*(i+0.5))/n),0,cos((2*PI*(i+0.5))/n)))
		
		2: 
			# Eje x = 0
			#assert(centro.x==0, "x=0") # Esta linea sirve para forzar que sea el plano z=0
			for i in range(n):
				vertex.append(radg*Vector3(0,cos((2*PI*i)/n), sin((2*PI*i)/n)))
				vertex.append(radp*Vector3(0,cos((2*PI*(i+0.5))/n), sin((2*PI*(i+0.5))/n)))
	
	# Trasladamos los vertices al centro correspondiente
	for i in range(2*n):
		vertex[i] = vertex[i] + centro
	
	vertex.append(centro)	# Esta en la posicion 2n del array de vertices.
	
	
	# Triangulos
	for i in range(2*n):
		indexes.append(i%(2*n))
		indexes.append(2*n)
		indexes.append((i+1)%(2*n))
	
	# Añadimos los colores
	for i in range(2*n):
		colors.append(Color(vertex[i].x,vertex[i].y,vertex[i].z))
		
	colors.append(Color(1, 1, 1))
	
	
	# Creamos la malla y le asignamos las cosas que hemos creado
	## inicializar el array con las tablas
	var tablas : Array = []   ## tabla vacía incialmente
	tablas.resize( Mesh.ARRAY_MAX ) ## redimensionar al tamaño adecuado
	tablas[ Mesh.ARRAY_VERTEX ] = vertex
	tablas[ Mesh.ARRAY_INDEX  ] = indexes
	tablas[ Mesh.ARRAY_NORMAL ] = Utilidades.calcNormales(vertex, indexes)
	tablas[ Mesh.ARRAY_COLOR ] = colors
	
	## crear e inicialzar el objeto 'mesh' de este nodo 
	var mesh = ArrayMesh.new() ## crea malla en modo diferido, vacía
	mesh.add_surface_from_arrays( Mesh.PRIMITIVE_TRIANGLES, tablas )
	
	## crear un material
	var mat := StandardMaterial3D.new() 
	mat.shading_mode = BaseMaterial3D.SHADING_MODE_UNSHADED		# Sin iluminacion
	mat.cull_mode = BaseMaterial3D.CULL_DISABLED				# Sin cribado de caras (2D)
	mat.vertex_color_use_as_albedo = true						# Difuminado de colores segun vertices
	
	mesh.surface_set_material(0, mat)
	
	return mesh

func GeneraCono(perfil : PackedVector2Array, n : int, eje : int, trasl : Vector3 = Vector3(0,0,0))->ArrayMesh:
	var vertex : PackedVector3Array = []
	var indexes : PackedInt32Array = []
	
	Revolucion.revoluciona(perfil,n,vertex,indexes,true,true,eje)
	
	var tablas : Array = []   ## tabla vacía incialmente
	tablas.resize( Mesh.ARRAY_MAX ) ## redimensionar al tamaño adecuado
	tablas[ Mesh.ARRAY_VERTEX ] = vertex
	tablas[ Mesh.ARRAY_INDEX  ] = indexes
	tablas[ Mesh.ARRAY_NORMAL ] = Utilidades.calcNormales(vertex, indexes)
	
	# DUDA: Con generacion de normales se refiere a esto, o a que se muestren tambien los segmentos de las normales? 
	
	## crear e inicialzar el objeto 'mesh' de este nodo 
	var mesh = ArrayMesh.new() ## crea malla en modo diferido, vacía
	mesh.add_surface_from_arrays( Mesh.PRIMITIVE_TRIANGLES, tablas )
	
	## crear un material
	var mat := StandardMaterial3D.new() 
	mat.albedo_color = Color(1,1,1)
	mat.shading_mode = BaseMaterial3D.SHADING_MODE_UNSHADED		# Sin iluminacion
	mat.vertex_color_use_as_albedo = true						# Difuminado de colores segun vertices
	
	mesh.surface_set_material(0, mat)
	
	return mesh
