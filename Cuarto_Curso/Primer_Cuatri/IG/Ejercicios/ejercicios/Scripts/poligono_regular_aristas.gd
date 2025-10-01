extends MeshInstance2D


# Buscamos crear un poligono regular de radio r y de n lados de manera que aparezcan
# todas las aristas entre el centro y cado uno de los vertices del poligono.

const index : bool = false
const n : int = 8
const r : float = 0.8
const BLACK_COLOR = Color(0,0,0)

func _ready():
	var tables : Array=[]
	tables.resize(Mesh.ARRAY_MAX)
	var vertex = PackedVector2Array([])
	
	if index:
		var indexes = PackedInt32Array([])
		vertex.append(Vector2(0,0)) # Añadimos el vertice central que no se cumple con la formula
		for i in range(0,n):
			vertex.append(Vector2(r*cos(i*2*PI/n),r*sin(i*2*PI/n)))
		
		for i in range(1,n+1):
			indexes.append(0)
			indexes.append(i)
		for i in range(1,n+1):	# En cada iteracion añado una linea
			indexes.append(i)
			indexes.append(i%n +1 )
			
				
		tables[Mesh.ARRAY_INDEX] = indexes
	else:
		
		#Añado el centro
		for i in range(1,n+1):
			vertex.append(Vector2(r*cos(i*2*PI/n),r*sin(i*2*PI/n)))
			vertex.append(Vector2(0.0,0.0))
			
		# Creo el perimetro
		for i in range(1,n+1):
			vertex.append(Vector2(r*cos(i*2*PI/n),r*sin(i*2*PI/n)))
			vertex.append(Vector2(r*cos((i+1)*2*PI/n),r*sin((i+1)*2*PI/n)))
	
	modulate = BLACK_COLOR
	tables[Mesh.ARRAY_VERTEX] = vertex
	
	mesh = ArrayMesh.new()
	mesh.add_surface_from_arrays(Mesh.PRIMITIVE_LINES,tables)
