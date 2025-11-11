## Nombre: Lucas, Apellidos: Hidalgo Herrera, Titulación: GIM
## email: lucashidalgo@correo.ugr.es, DNI o pasaporte: 26512990Q

extends MeshInstance3D

@export var n : int = 5
@export var pto : Vector3 = Vector3(-0.25,0,-0.25)
@export var base : float = 0.5
@export var altura : float = 0.5
@export var eje : int = 1

func _ready():
	var vertex : PackedVector3Array = []
	var indexes : PackedInt32Array = []
	var normales : PackedVector3Array = []

	CrearTorre(pto,base,altura,n,eje,vertex,indexes)
		
	normales = Utilidades.calcNormales(vertex,indexes)
	
	var tablas : Array = []   ## tabla vacía incialmente
	tablas.resize( Mesh.ARRAY_MAX ) ## redimensionar al tamaño adecuado
	tablas[ Mesh.ARRAY_VERTEX ] = vertex
	tablas[ Mesh.ARRAY_INDEX  ] = indexes
	tablas[ Mesh.ARRAY_NORMAL ] = normales
	
	## crear e inicialzar el objeto 'mesh' de este nodo 
	mesh = ArrayMesh.new() ## crea malla en modo diferido, vacía
	mesh.add_surface_from_arrays( Mesh.PRIMITIVE_TRIANGLES, tablas )
	
	## crear un material
	var mat := StandardMaterial3D.new() 
	mat.albedo_color = Color(1,1,1)
	mat.shading_mode = BaseMaterial3D.SHADING_MODE_UNSHADED
	mat.cull_mode = BaseMaterial3D.CULL_DISABLED
	material_override = mat

func CrearTorre(pto : Vector3, base:float, altura : float, n : int, eje : int, vertex : PackedVector3Array, indexes : PackedInt32Array):
	assert(n>0, "necesito plantas para crear la torre")
	assert(altura != 0 and base != 0, "No puedo crear una torre sin base o sin altura")
	assert(eje == 0 or eje == 1 or eje == 2, "Eje erroneo")
	
	vertex.clear()
	indexes.clear()
	
	var vertex_p : PackedVector3Array = []
	var indexes_p : PackedInt32Array = []
	
	match eje:
		0: #Apoyada en z=0
			for i in range(n):
				CrearPlanta(pto+Vector3(0,0,i*altura),base,altura,eje,vertex_p,indexes_p)
				Utilidades.uneMallas(vertex,indexes,vertex_p,indexes_p)
		1:	#Apoyada en y=0
			for i in range(n):
				CrearPlanta(pto+Vector3(0,i*altura,0),base,altura,eje,vertex_p,indexes_p)
				Utilidades.uneMallas(vertex,indexes,vertex_p,indexes_p)
		2:	#Apoyada en x=0
			for i in range(n):
				CrearPlanta(pto+Vector3(i*altura,0,0),base,altura,eje,vertex_p,indexes_p)
				Utilidades.uneMallas(vertex,indexes,vertex_p,indexes_p)


func CrearPlanta(pto : Vector3, base : float, altura : float, eje : int, vertex : PackedVector3Array, indexes : PackedInt32Array):
	assert(eje == 0 or eje == 1 or eje == 2,"Eje erroneo")
	assert(altura != 0 and base != 0, "No puedo crear una planta sin base o sin altura")
	
	vertex.clear()
	indexes.clear()
	
	var vertex_c : PackedVector3Array = []
	var indexes_c : PackedInt32Array = []
	
	match eje:
		0:	# Apoyada sobre el plano z=0
			
			Propio.CrearCuadrilatero(pto,altura,base,eje+2,vertex,indexes)
			Propio.CrearCuadrilatero(pto+Vector3(0,base,0),base,altura,eje+1,vertex_c,indexes_c)
			Propio.uneMallas(vertex,indexes,vertex_c,indexes_c)
			Propio.CrearCuadrilatero(pto+Vector3(base,0,0),altura,base,eje+2,vertex_c,indexes_c)
			Propio.uneMallas(vertex,indexes,vertex_c,indexes_c)
			Propio.CrearCuadrilatero(pto,base,altura,eje+1,vertex_c,indexes_c)
			Propio.uneMallas(vertex,indexes,vertex_c,indexes_c)
			
		1:	#Apoyada sobre el plano y=0
			Propio.CrearCuadrilatero(pto,altura,base,eje-1,vertex,indexes)
			Propio.CrearCuadrilatero(pto+Vector3(base,0,0),base,altura,eje+1,vertex_c,indexes_c)
			Propio.uneMallas(vertex,indexes,vertex_c,indexes_c)
			Propio.CrearCuadrilatero(pto,base,altura,eje+1,vertex_c,indexes_c)
			Propio.uneMallas(vertex,indexes,vertex_c,indexes_c)
			Propio.CrearCuadrilatero(pto+Vector3(0,0,base),altura,base,eje-1,vertex_c,indexes_c)
			Propio.uneMallas(vertex,indexes,vertex_c,indexes_c)
		
		2: # Apoyada sobre el plano x=0
			
			Propio.CrearCuadrilatero(pto,altura,base,eje-1,vertex,indexes)
			Propio.CrearCuadrilatero(pto+Vector3(0,0,base),base,altura,eje-2,vertex_c,indexes_c)
			Propio.uneMallas(vertex,indexes,vertex_c,indexes_c)
			Propio.CrearCuadrilatero(pto,base,altura,eje-2,vertex_c,indexes_c)
			Propio.uneMallas(vertex,indexes,vertex_c,indexes_c)
			Propio.CrearCuadrilatero(pto+Vector3(0,base,0),altura,base,eje-1,vertex_c,indexes_c)
			Propio.uneMallas(vertex,indexes,vertex_c,indexes_c)
