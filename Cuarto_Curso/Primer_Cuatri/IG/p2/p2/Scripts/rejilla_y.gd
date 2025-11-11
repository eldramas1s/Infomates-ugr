## Nombre: Lucas, Apellidos: Hidalgo Herrera, Titulación: GIM
## email: lucashidalgo@correo.ugr.es, DNI o pasaporte: 26512990Q
extends MeshInstance3D

@export var n : int = 10		# numero de divisiones en el eje x
@export var m : int = 10		# numero de divisiones en el eje y
@export var eje : int = 0	# indica si z=0, y=0, x=0 en ese orden de 0 a 2
@export var inferiorIzquierda : Vector3 = Vector3(0,0,0)
@export var longitudInferior : float = 1.0		# Longitud del lado inferior
@export var longitudIzquierda : float = 1.0		# Longitud del lado izquierdo

func _ready():
	var vertex : PackedVector3Array = []
	var indexes : PackedInt32Array = []
	var colors : PackedColorArray = []
	var normales : PackedVector3Array = []

	CrearRejilla(n,m,eje,vertex,indexes,colors,inferiorIzquierda,longitudInferior,longitudIzquierda)
	
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
	
	## crear un material
	var mat := StandardMaterial3D.new() 
	mat.vertex_color_use_as_albedo = true
	mat.shading_mode = BaseMaterial3D.SHADING_MODE_UNSHADED
	mat.cull_mode = BaseMaterial3D.CULL_DISABLED
	material_override = mat
	
func CrearRejilla(n : int, m : int, eje : int, vertex : PackedVector3Array, indexes : PackedInt32Array, colors : PackedColorArray, inferiorIzquierda : Vector3 = Vector3(0,0,0), longitudInferior : float=1.0, longitudIzquierda : float=1.0):
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
