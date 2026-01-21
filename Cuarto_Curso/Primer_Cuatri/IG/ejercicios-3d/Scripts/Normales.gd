extends Node

## Para usar esta funcion es simplemente llamarla y obtenemos una mesh instance, por lo que solo hay que añadirla
## como hijo del objeto en cuesti
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

## Para el ejercicio 3.6 simplemente hay que calcular, para una malla sin discontinuidades en la normal
## es decir, con duplicacion de vertices, el area del triangulo correspondiente, para ello podemos usar esta funcion

func get_triangle_area_3d(a: Vector3, b: Vector3, c: Vector3) -> float:
	var ab = b - a
	var ac = c - a
	# Obtenemos el vector perpendicular y calculamos su magnitud
	return ab.cross(ac).length() / 2.0
	# Otra forma de hacerlo es calcular la norma euclidea que sera mejor de ab y de ac y tenemos base por altura
	# dividimos por dos y ya.
	
## Para despues ponderar no es mas que tomar el maximo, despues el minimo y hacer una ponderacion respescto a eso
