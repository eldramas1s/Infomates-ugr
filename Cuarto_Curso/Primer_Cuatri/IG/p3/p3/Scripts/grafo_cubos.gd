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

func _ready():
	
	var cubo_grande = Node3D.new()
	add_child(cubo_grande)
	
	## crear un material
	var mat := StandardMaterial3D.new() 
	mat.albedo_color = Color( 1, 1, 1 )
	mat.shading_mode = BaseMaterial3D.SHADING_MODE_UNSHADED
	mat.cull_mode = BaseMaterial3D.CULL_DISABLED
	
	var vertex : PackedVector3Array = []
	var indexes : PackedInt32Array = []
	var colors : PackedColorArray = []
	
	var cubo = CrearCubo24()	#Esta centrado en (0,0,0)
	var caracubo = CrearRejilla(n,n,0,vertex,indexes,colors,Vector3(-0.5,-0.5,-0.5),longitudInferior,longitudIzquierda)
	
	#!!!! hay que tener cuidado en como aplicamos las transformaciones
	
	#Cara trasera
	var trasera = MeshInstance3D.new()
	trasera.mesh = caracubo
	#cubo trasera
	var c_trasero = MeshInstance3D.new()
	c_trasero.mesh=cubo
	c_trasero.material_override=mat
	trasera.add_child(c_trasero)
	c_trasero.scale = Vector3(0.25,0.5,0.25)
	c_trasero.rotate_x(PI/2)
	c_trasero.position = Vector3(0,0,-1)
	cubo_grande.add_child(trasera)
	
	# Cara delantera
	var delantera = MeshInstance3D.new()
	delantera.mesh = caracubo
	#cubo delantera
	var c_delantera = MeshInstance3D.new()
	c_delantera.mesh=cubo
	c_delantera.material_override=mat
	delantera.add_child(c_delantera)
	c_delantera.scale = Vector3(0.25,0.5,0.25)
	c_delantera.rotate_x(PI/2)
	cubo_grande.add_child(delantera)
	delantera.position = Vector3(0,0,1)
	
	# Cara inferior
	var inferior = MeshInstance3D.new()
	inferior.mesh = caracubo
	#cubo inferior
	var c_inferior = MeshInstance3D.new()
	c_inferior.mesh=cubo
	c_inferior.material_override=mat
	inferior.add_child(c_inferior)
	c_inferior.scale = Vector3(0.25,0.5,0.25)
	c_inferior.rotate_x(PI/2)
	c_inferior.position = Vector3(0,0,-1)
	cubo_grande.add_child(inferior)
	#Primero escalariamos pero no hace falta
	inferior.rotate_x(-PI/2)
	#
	
	# Cara superior
	var superior = MeshInstance3D.new()
	superior.mesh = caracubo
	#cubo superior
	var c_superior = MeshInstance3D.new()
	c_superior.mesh=cubo
	c_superior.material_override=mat
	superior.add_child(c_superior)
	c_superior.scale = Vector3(0.25,0.5,0.25)
	c_superior.rotate_x(-PI/2)
	c_superior.position = Vector3(0,0,-1)
	cubo_grande.add_child(superior)
	#Primero escalariamos pero no hace falta
	superior.rotate_x(PI/2)
	
	#Cara izquierda
	var izquierda = MeshInstance3D.new()
	izquierda.mesh = caracubo
	#cubo izquierda
	var c_izquierda = MeshInstance3D.new()
	c_izquierda.mesh=cubo
	c_izquierda.material_override=mat
	izquierda.add_child(c_izquierda)
	c_izquierda.scale = Vector3(0.25,0.5,0.25)
	c_izquierda.rotate_x(-PI/2)
	c_izquierda.position = Vector3(0,0,-1)
	cubo_grande.add_child(izquierda)
	#Primero escalariamos pero no hace falta
	izquierda.rotate_y(PI/2)
#
	#Cara derecha
	var derecha = MeshInstance3D.new()
	derecha.mesh = caracubo
	#cubo derecha
	var c_derecha = MeshInstance3D.new()
	c_derecha.mesh=cubo
	c_derecha.material_override=mat
	derecha.add_child(c_derecha)
	c_derecha.scale = Vector3(0.25,0.5,0.25)
	c_derecha.rotate_x(-PI/2)
	c_derecha.position = Vector3(0,0,-1)
	cubo_grande.add_child(derecha)
	#Primero escalariamos pero no hace falta
	derecha.rotate_y(-PI/2)
	
func _process(delta:float):
	# Si se pulsa "1" rotamos a derecha
	if Input.is_action_just_pressed("Rotarderecha") and !activa_izquierda:
		activa_drcha = !activa_drcha
	if activa_drcha:
		#cubo.rotate(Vector3(1, 0, 0), angulo)  para eje X global
		#cubo.rotate(Vector3(0, 1, 0), angulo)  para eje Y global
		#cubo.rotate(Vector3(0, 0, 1), angulo)  para eje Z global

		for i in range(6):
			get_child(0).get_child(i).get_child(0).rotate(Vector3(0,0,1),rotation_speed*delta)
		
		
	# Si se pulsa "2" rotamos a izquierda
	if Input.is_action_just_pressed("RotarIzquierda") and !activa_drcha:
		activa_izquierda = !activa_izquierda
	if activa_izquierda:
		for i in range(6):
			get_child(0).get_child(i).get_child(0).rotate(Vector3(0,0,1),-rotation_speed*delta)
		
func CrearCubo24()->ArrayMesh:
	## crear las tablas de vértices y triángulos de un Donut 
	var vertices   := PackedVector3Array([])
	var triangulos := PackedInt32Array([])
	
	const D=1
	
	#Vertices de abajo
	
	# Adelante-Izquierda-Abajo (0)
	vertices.append(Vector3(-D, -D, D))  # 0: frontal
	vertices.append(Vector3(-D, -D, D))	 # 1: inferior
	vertices.append(Vector3(-D, -D, D))  # 2: izquierda
	
	# Adelante-Derecha-Abajo (1)
	vertices.append(Vector3( D, -D, D))  # 3: frontal
	vertices.append(Vector3( D, -D, D))  # 4: inferior
	vertices.append(Vector3( D, -D, D))  # 5: derecha
	
	# Atras-Derecha-Abajo (2)
	vertices.append(Vector3( D, -D,-D))  # 6: trasera
	vertices.append(Vector3( D, -D,-D))	 # 7: inferior
	vertices.append(Vector3( D, -D,-D))  # 8: derecha
	
	# Atras-Izquierda-Abajo (3)
	vertices.append(Vector3(-D, -D,-D))  # 9: trasera
	vertices.append(Vector3(-D, -D,-D))  # 10: inferior
	vertices.append(Vector3(-D, -D,-D))  # 11: izquierda
	
	# Vertices de arriba
	
	# Adelante-Izquierda-Arriba (4)
	vertices.append(Vector3(-D,  D, D))  # 12: frontal
	vertices.append(Vector3(-D,  D, D))	 # 13: superior
	vertices.append(Vector3(-D,  D, D))	 # 14: izquierda
	
	# Adelante-Derecha-Arriba (5)
	vertices.append(Vector3( D,  D, D))  # 15: frontal
	vertices.append(Vector3( D,  D, D))  # 16: superior
	vertices.append(Vector3( D,  D, D))  # 17: derecha 
	
	# Atras-Derecha-Arriba (6)
	vertices.append(Vector3( D,  D,-D))  # 18: trasera
	vertices.append(Vector3( D,  D,-D))	 # 19: superior
	vertices.append(Vector3( D,  D,-D))  # 20: derecha
	
	# Atras-Izquierda-Arriba (7)
	vertices.append(Vector3(-D,  D,-D))  # 21: trasera
	vertices.append(Vector3(-D,  D,-D))  # 22: superior
	vertices.append(Vector3(-D,  D,-D))  # 23: izquierda
	
	#Cara frontal
	triangulos.append_array([0,15,3,0,12,15])
	
	#Cara derecha
	triangulos.append_array([5,20,8,5,17,20])
	
	#Cara trasera
	triangulos.append_array([6,21,9,6,18,21])
	
	#Cara izquierda
	triangulos.append_array([11,14,2,11,23,14])
	
	#Cara superior
	triangulos.append_array([16,22,19,16,13,22])
	
	#Cara inferior
	triangulos.append_array([10,1,4,10,4,7])	
		
	var normales := Utilidades.calcNormales( vertices, triangulos )
	
	#var norm : MeshInstance3D = Normales.genSegNormales(vertices,normales,1.0,Color(0,0,0))	
	
	## inicializar el array con las tablas
	var tablas : Array = []   ## tabla vacía incialmente
	tablas.resize( Mesh.ARRAY_MAX ) ## redimensionar al tamaño adecuado
	tablas[ Mesh.ARRAY_VERTEX ] = vertices
	tablas[ Mesh.ARRAY_INDEX  ] = triangulos
	tablas[ Mesh.ARRAY_NORMAL ] = normales
	
	## crear e inicialzar el objeto 'mesh' de este nodo 
	var mesh = ArrayMesh.new() ## crea malla en modo diferido, vacía
	mesh.add_surface_from_arrays( Mesh.PRIMITIVE_TRIANGLES, tablas )
	
	return mesh
	
	
func CrearRejilla(n : int, m : int, eje : int, vertex : PackedVector3Array, indexes : PackedInt32Array, colors : PackedColorArray, inferiorIzquierda : Vector3 = Vector3(0,0,0), longitudInferior : float=1.0, longitudIzquierda : float=1.0)->ArrayMesh:
	assert(eje == 0 or eje == 1 or eje == 2, "Eje erroneo")
	assert(longitudInferior > 0, "longitudInferior no puede ser 0")
	assert(longitudIzquierda > 0, "longitudIzquierda no puede ser 0")
	assert(n>0 and m>0, "No puedo crear una rejilla con una linea o un punto")
	
	var base_sep : float = longitudInferior/float(n)
	var altura_sep : float = longitudIzquierda/float(m)
	var vertex_c : PackedVector3Array = []
	var indexes_c : PackedInt32Array = []
	
	for i in range(n):
		for j in range(m):
			match eje:
				0:
					Propio.CrearCuadrilatero(inferiorIzquierda+Vector3(i*base_sep,j*altura_sep,0),altura_sep,base_sep,eje,vertex_c,indexes_c)
				1:
					Propio.CrearCuadrilatero(inferiorIzquierda + Vector3(i * base_sep, 0, j * altura_sep), base_sep, altura_sep, eje, vertex_c, indexes_c)
				2:
					Propio.CrearCuadrilatero(inferiorIzquierda+Vector3(0,i*base_sep,j*altura_sep),altura_sep,base_sep,eje,vertex_c,indexes_c)
			# Unimos con la mala global
			Propio.uneMallas(vertex,indexes,vertex_c,indexes_c)	
	
	for i in range(vertex.size()):
		colors.append(Color(vertex[i].x,vertex[i].y,vertex[i].z))
	
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
