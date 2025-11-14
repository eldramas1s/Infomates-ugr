## Nombre: Lucas, Apellidos: Hidalgo Herrera, Titulación: GIM
## email: lucashidalgo@correo.ugr.es, DNI o pasaporte: 26512990Q

extends MeshInstance3D
@export var n : int = 8
@export var rad : float = 0.5
@export var eje : int = 0
@export var centro : Vector3 = Vector3(0.5,0.5,0)
func _ready():
	var poligonon = ArrayMeshPoligonoRegular(n,rad,eje,centro)
	var mesh_instance = MeshInstance3D.new()
	var material = StandardMaterial3D.new()
	mesh_instance.mesh = poligonon
	add_child(mesh_instance)

func ArrayMeshPoligonoRegular( n: int, rad : float, eje:int, centro : Vector3 = Vector3(0,0,0) ) -> ArrayMesh :
	
	var indexes : PackedInt32Array = []
	var vertex : PackedVector3Array = []
	var colors : PackedColorArray = []
	
	assert(eje==0 or eje == 1 or eje==2, "No ha seleccionado ningun eje")
	
	match eje:
		0:
			#Eje z = 0
			#assert(centro.z==0, "z=0")	# Esta linea sirve para forzar que sea el plano z=0
			for i in range(n):
				vertex.append(rad*Vector3(cos((2*PI*i)/n),sin((2*PI*i)/n),0))
	
		1: 	
			# Eje y = 0
			#assert(centro.y==0, "y=0") # Esta linea sirve para forzar que sea el plano z=0
			for i in range(n):
				vertex.append(rad*Vector3(sin((2*PI*i)/n),0,cos((2*PI*i)/n)))
		
		2: 
			# Eje x = 0
			#assert(centro.x==0, "x=0") # Esta linea sirve para forzar que sea el plano z=0
			for i in range(n):
				vertex.append(rad*Vector3(0,cos((2*PI*i)/n), sin((2*PI*i)/n)))
	
	# Trasladamos los vertices al centro correspondiente
	for i in range(n):
		vertex[i] = vertex[i] + centro
	
	vertex.append(centro)	# Esta en la posicion n del array de vertices.
	
	
	# Triangulos
	for i in range(n):
		indexes.append(i%n)
		indexes.append(n)
		indexes.append((i+1)%n)
	
	# Añadimos los colores
	for i in range(n):
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
	mesh = ArrayMesh.new() ## crea malla en modo diferido, vacía
	mesh.add_surface_from_arrays( Mesh.PRIMITIVE_TRIANGLES, tablas )
	
	## crear un material
	var mat := StandardMaterial3D.new() 
	mat.shading_mode = BaseMaterial3D.SHADING_MODE_UNSHADED  # Sin iluminacion
	mat.cull_mode = BaseMaterial3D.CULL_DISABLED
	mat.vertex_color_use_as_albedo = true		# Permite difuminado de colores
	
	material_override = mat
	
	return mesh
