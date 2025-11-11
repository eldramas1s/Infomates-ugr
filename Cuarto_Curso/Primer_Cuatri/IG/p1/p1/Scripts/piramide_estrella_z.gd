extends MeshInstance3D

@export var n : int = 8
@export var rad1 : float = 0.5
@export var rad2 : float = 0.25
@export var eje : int = 0
@export var centro : Vector3 = Vector3(0.5,0.5,0)
@export var altura : float = 0.5


func _ready():
	
	var vertex : PackedVector3Array = []
	var indexes : PackedInt32Array = []
	var colors : PackedColorArray = []
	
	EstrellaZ(n,rad1,rad2,eje, vertex,indexes,colors, centro)
	
	# Por construccion de la estrellaZ es necesario invertir la orientacion de las caras
	var newindexes : PackedInt32Array = []
	
	Propio.invertMesh(indexes,newindexes)
	
	# Añadimos el apex y sus correspondientes triangulos
	
	var apex_index = vertex.size()
	
	match eje:
		0:	#z=0
			vertex.append(centro+Vector3(0,0,altura))
		1:	#y=0
			vertex.append(centro+Vector3(0,altura,0))
		2:	#x=0
			vertex.append(centro+Vector3(altura,0,0))
		
	# Aniadimos los triangulos
	
	for i in range(2 * n):
		newindexes.append(i)
		newindexes.append(apex_index)
		newindexes.append((i + 1) % (2 * n))
		
	# Aniadimos el color al apex
	
	colors.append(Color(1,1,1))	
	
	#Creamos las tablas, las normales y todo.
	
	var tablas : Array = []   ## tabla vacía incialmente
	tablas.resize( Mesh.ARRAY_MAX ) ## redimensionar al tamaño adecuado
	tablas[ Mesh.ARRAY_VERTEX ] = vertex
	tablas[ Mesh.ARRAY_INDEX  ] = newindexes
	tablas[ Mesh.ARRAY_NORMAL ] = Utilidades.calcNormales(vertex, indexes)
	tablas[ Mesh.ARRAY_COLOR ] = colors
	
	## crear e inicialzar el objeto 'mesh' de este nodo 
	mesh = ArrayMesh.new() ## crea malla en modo diferido, vacía
	mesh.add_surface_from_arrays( Mesh.PRIMITIVE_TRIANGLES, tablas )
	
	## crear un material
	var mat := StandardMaterial3D.new() 
	mat.shading_mode = BaseMaterial3D.SHADING_MODE_UNSHADED		# Sin iluminacion
	mat.vertex_color_use_as_albedo = true						# Difuminado de colores segun vertices
	
	material_override = mat

# Necesito el eje como parametro porque permito cualquier centro, si solo permitiera en los planos x=0, y=0 o z=0 podria obviarlo
func EstrellaZ(n: int, rad1 : float, rad2 : float, eje:int, vertex : PackedVector3Array, indexes : PackedInt32Array, colors : PackedColorArray, centro : Vector3 = Vector3(0,0,0)):
	
	# Limpiamos zona de trabajo
	vertex.clear()
	indexes.clear()
	colors.clear()
	
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
	

			
