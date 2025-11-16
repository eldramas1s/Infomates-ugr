## Nombre: Lucas, Apellidos: Hidalgo Herrera, Titulación: GIM
## email: lucashidalgo@correo.ugr.es, DNI o pasaporte: 26512990Q
extends MeshInstance3D

@export var n : int = 10		# numero de divisiones en el eje x
@export var m : int = 10		# numero de divisiones en el eje y
@export var eje : int = 1	# indica si z=0, y=0, x=0 en ese orden de 0 a 2
@export var inferiorIzquierda : Vector3 = Vector3(0,0,0)
@export var longitudInferior : float = 1.0		# Longitud del lado inferior
@export var longitudIzquierda : float = 1.0		# Longitud del lado izquierdo

func _ready():
	
	## material a usar
	var mat := StandardMaterial3D.new() 
	mat.vertex_color_use_as_albedo = true
	mat.shading_mode = BaseMaterial3D.SHADING_MODE_UNSHADED
	mat.cull_mode = BaseMaterial3D.CULL_DISABLED
	
	## Creacion de la instancia de la malla 
	var vertex : PackedVector3Array = []
	var indexes : PackedInt32Array = []
	var colors : PackedColorArray = []
	var normales : PackedVector3Array = []

	Propio.CrearRejilla(n,m,eje,vertex,indexes,colors,inferiorIzquierda,longitudInferior,longitudIzquierda)
	
	for i in range(vertex.size()):
		colors.append(Color(vertex[i].x,vertex[i].y,vertex[i].z))
		
	normales = Utilidades.calcNormales(vertex,indexes)
	
	var tablas : Array = []   ## tabla vacía incialmente
	tablas.resize( Mesh.ARRAY_MAX ) ## redimensionar al tamaño adecuado
	tablas[ Mesh.ARRAY_VERTEX ] = vertex
	tablas[ Mesh.ARRAY_INDEX  ] = indexes
	tablas[ Mesh.ARRAY_NORMAL ] = normales
	tablas[ Mesh.ARRAY_COLOR  ] = colors
	
	## crear e inicialzar el objeto 'mesh' de este nodo 
	mesh = ArrayMesh.new() ## crea malla en modo diferido, vacía
	mesh.add_surface_from_arrays( Mesh.PRIMITIVE_TRIANGLES, tablas )
	
	## Asignacion del material
	material_override = mat
	
