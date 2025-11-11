## Nombre: Lucas, Apellidos: Hidalgo Herrera, Titulación: GIM
## email: lucashidalgo@correo.ugr.es, DNI o pasaporte: 26512990Q
extends MeshInstance3D

func _ready() -> void:
	
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
