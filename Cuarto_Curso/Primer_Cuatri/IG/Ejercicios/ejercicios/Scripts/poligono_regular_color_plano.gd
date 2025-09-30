extends MeshInstance2D

const index : bool = true
const n : int = 5
const r : float = 0.8
const ORANGE_COLOR = Color(1,0.7,0)

func _ready():
	var tables : Array=[]
	tables.resize(Mesh.ARRAY_MAX)
	var vertex = PackedVector2Array([])
	
	if index:
		var indexes = PackedInt32Array([])
		vertex.append(Vector2(0,0)) # Añadimos el vertice central que no se cumple con la formula
		for i in range(0,n):
			vertex.append(Vector2(r*cos(i*2*PI/n),r*sin(i*2*PI/n)))
		var numTri = 0;
		for i in range(0,3*n):
			var k = numTri - 1 
			if i%3==0:
				indexes.append(0)
				numTri+=1
			if i % 3 == 1:
				indexes.append(k + 1)
			if i%3 == 2:
				var next_index = (k + 1) % n + 1 
				indexes.append(next_index)
				
		tables[Mesh.ARRAY_INDEX] = indexes
	else:
		for i in range(1,n+1):
			vertex.append(Vector2(r*cos(i*2*PI/n),r*sin(i*2*PI/n)))
			vertex.append(Vector2(r*cos((i+1)*2*PI/n),r*sin((i+1)*2*PI/n)))
			vertex.append(Vector2(0.0,0.0))
	
	modulate = ORANGE_COLOR
	tables[Mesh.ARRAY_VERTEX] = vertex
	
	mesh = ArrayMesh.new()
	mesh.add_surface_from_arrays(Mesh.PRIMITIVE_TRIANGLES,tables)
	
	
	
