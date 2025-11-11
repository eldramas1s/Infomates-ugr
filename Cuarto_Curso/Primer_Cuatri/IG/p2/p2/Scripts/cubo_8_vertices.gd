## Nombre: Lucas, Apellidos: Hidalgo Herrera, Titulación: GIM
## email: lucashidalgo@correo.ugr.es, DNI o pasaporte: 26512990Q
extends MeshInstance3D

func _ready() -> void:
	
	## crear las tablas de vértices y triángulos de un Donut 
	var vertices   := PackedVector3Array([])
	var triangulos := PackedInt32Array([])
	
	const D=1
	#Vertices de abajo
	
	vertices.append(Vector3(-D, -D, D))  # 0: Adelante-Izquierda-Abajo
	vertices.append(Vector3( D, -D, D))  # 1: Adelante-Derecha-Abajo
	vertices.append(Vector3( D, -D,-D))  # 2: Atrás-Derecha-Abajo
	vertices.append(Vector3(-D, -D,-D))  # 3: Atrás-Izquierda-Abajo
	
	# Vertices de arriba
	
	vertices.append(Vector3(-D,  D, D))  # 4: Adelante-Izquierda-Arriba
	vertices.append(Vector3( D,  D, D))  # 5: Adelante-Derecha-Arriba
	vertices.append(Vector3( D,  D,-D))  # 6: Atrás-Derecha-Arriba
	vertices.append(Vector3(-D,  D,-D))  # 7: Atrás-Izquierda-Arriba
	
	#Cara frontal
	triangulos.append_array([0,5,1,0,4,5])
	
	#Cara derecha
	triangulos.append_array([1,6,2,1,5,6])
	#
	##Cara trasera
	triangulos.append_array([2,7,3,2,6,7])
	#
	##Cara izquierda
	triangulos.append_array([3,4,0,3,7,4])
	#
	##Cara superior
	triangulos.append_array([5,7,6,5,4,7])
	#
	##Cara inferior
	triangulos.append_array([3,0,1,3,1,2])	
		
	var normales = Utilidades.calcNormales( vertices, triangulos )
				#
	#var norm : MeshInstance3D = Normales.genSegNormales(vertices,normales,1.0,Color(0,0,0))
	## inicializar el array con las tablas
	var tablas : Array = []   ## tabla vacía incialmente
	tablas.resize( Mesh.ARRAY_MAX ) ## redimensionar al tamaño adecuado
	tablas[ Mesh.ARRAY_VERTEX ] = vertices
	tablas[ Mesh.ARRAY_INDEX  ] = triangulos
	tablas[ Mesh.ARRAY_NORMAL ] = normales
	
	## crear e inicialzar el objeto 'mesh' de este nodo 
	mesh = ArrayMesh.new() ## crea malla en modo diferido, vacía
	mesh.add_surface_from_arrays( Mesh.PRIMITIVE_TRIANGLES, tablas )
	
	## crear un material
	var mat := StandardMaterial3D.new() 
	mat.albedo_color = Color( 1.0, 0.5, 0.2 )
	mat.metallic = 0.3
	mat.roughness = 0.2
	mat.shading_mode = BaseMaterial3D.SHADING_MODE_PER_PIXEL
	mat.cull_mode = BaseMaterial3D.CULL_DISABLED
	
	material_override = mat
