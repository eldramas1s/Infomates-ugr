extends Node

func genSegNormales( verts : PackedVector3Array , norms : PackedVector3Array, lon : float, color : Color ) -> MeshInstance3D :
	
	var meshinstance = MeshInstance3D.new()
	var mesh = ArrayMesh.new()
	# Como me estan dando los vertices y las normales, debo obtener un nuevo punto usando la longitud
	# dada por el parametro lon.
	
	var vertex = PackedVector3Array([])
	var colors = PackedColorArray([])
	
	#Obtengo los vertices ordenados por parejas
	for i in range(verts.size()):
		vertex.append(verts[i])
		vertex.append(getNormalVertex(verts[i],norms[i],lon))
		colors.append(color)
		colors.append(color)
		
	# Construimos la superficie sin indexar
	
	var arrays = []
	arrays.resize(Mesh.ARRAY_MAX)
	arrays[Mesh.ARRAY_VERTEX] = vertex
	arrays[Mesh.ARRAY_COLOR] = colors
	
	mesh.add_surface_from_arrays(Mesh.PRIMITIVE_LINES,arrays)
	
	# Material que no se ve afectado por iluminación
	var mat = StandardMaterial3D.new()
	mat.vertex_color_use_as_albedo = true
	mat.shading_mode = StandardMaterial3D.SHADING_MODE_UNSHADED
	
	meshinstance.mesh = mesh
	meshinstance.material_override = mat
	
	add_child(meshinstance)
	
	return meshinstance
	

func getNormalVertex( vertex : Vector3, normal : Vector3, lon : float) -> Vector3 :
	return vertex + lon*normal
