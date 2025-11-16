## Nombre: Lucas, Apellidos: Hidalgo Herrera, Titulación: GIM
## email: lucashidalgo@correo.ugr.es, DNI o pasaporte: 26512990Q

extends MeshInstance3D

@export var n : int = 5
@export var pto : Vector3 = Vector3(-0.25,0,-0.25)
@export var base : float = 0.5
@export var altura : float = 0.5
@export var eje : int = 1

func _ready():
	
	## Material a usar
	var mat := StandardMaterial3D.new() 
	mat.albedo_color = Color(1,1,1)
	mat.shading_mode = BaseMaterial3D.SHADING_MODE_UNSHADED
	mat.cull_mode = BaseMaterial3D.CULL_DISABLED
	
	## Creacion de la malla (realmente hemos creado una instancia en el editor)
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
	
	## Asignacion del material
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
				Propio.CrearPlanta(pto+Vector3(0,0,i*altura),base,altura,eje,vertex_p,indexes_p)
				Propio.uneMallas(vertex,indexes,vertex_p,indexes_p)
		1:	#Apoyada en y=0
			for i in range(n):
				Propio.CrearPlanta(pto+Vector3(0,i*altura,0),base,altura,eje,vertex_p,indexes_p)
				Propio.uneMallas(vertex,indexes,vertex_p,indexes_p)
		2:	#Apoyada en x=0
			for i in range(n):
				Propio.CrearPlanta(pto+Vector3(i*altura,0,0),base,altura,eje,vertex_p,indexes_p)
				Propio.uneMallas(vertex,indexes,vertex_p,indexes_p)
