extends MeshInstance3D

@export var n : int = 8
@export var rad1 : float = 0.5
@export var rad2 : float = 0.25
@export var eje : int = 0
@export var centro : Vector3 = Vector3(0.5,0.5,0)
@export var altura : float = 0.5


func _ready():
	
	## Material a usar
	var mat := StandardMaterial3D.new() 
	mat.shading_mode = BaseMaterial3D.SHADING_MODE_UNSHADED		# Sin iluminacion
	mat.vertex_color_use_as_albedo = true						# Difuminado de colores segun vertices
	
	## Creacion de la malla
	var vertex : PackedVector3Array = []
	var indexes : PackedInt32Array = []
	var colors : PackedColorArray = []
	
	Propio.EstrellaZ(n,rad1,rad2,eje, vertex,indexes,colors, centro)
	
	# Por la construccion de la estrellaZ es necesario invertir la orientacion de las caras
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
	
	## Asignacion del material
	material_override = mat

# Necesito el eje como parametro porque permito cualquier centro, si solo permitiera en los planos x=0, y=0 o z=0 podria obviarlo

	

			
