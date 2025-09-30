extends MeshInstance2D

const index : bool = true
const n : int = 8
const r : float = 0.8
const WHITE_COLOR : Color= Color(255,255,255)
const LIGHT_GREY_COLOR : Color = Color(0.76, 0.76, 0.76)
const GREY_COLOR : Color = Color(0.31,0.31,0.31)

func _ready():
	
	var tables : Array=[]
	tables.resize(Mesh.ARRAY_MAX)
	var colours = PackedColorArray([])
	var vertex = PackedVector2Array([])
	
	if index:
		var indexes = PackedInt32Array([])
		vertex.append(Vector2(0,0)) # Añadimos el vertice central que no se cumple con la formula
		for i in range(1,n+1):
			vertex.append(Vector2(r*cos(i*2*PI/n),r*sin(i*2*PI/n)))
			vertex.append(Vector2(r*cos((i+1)*2*PI/n),r*sin((i+1)*2*PI/n)))
		
		#Esto hay que revisarlo y ponerle los colores
		var numTri = 0
		for i in range(0,n):
			for j in range(0,3):
				if j==0:
					indexes.append(0)
				else:
					indexes.append(2*i+j)
		
		colours.append(WHITE_COLOR)
		for i in range(1,2*n+1):
			match i%2:
				0:
					colours.append(LIGHT_GREY_COLOR)
				1: 
					colours.append(GREY_COLOR)
			
		tables[Mesh.ARRAY_INDEX] = indexes
		
	else:
		for i in range(1,n+1):
			vertex.append(Vector2(r*cos(i*2*PI/n),r*sin(i*2*PI/n)))
			vertex.append(Vector2(r*cos((i+1)*2*PI/n),r*sin((i+1)*2*PI/n)))
			vertex.append(Vector2(0.0,0.0))

		for i in range(3*n):
			match (i%3):
				0:
					colours.append(LIGHT_GREY_COLOR)
				1:
					colours.append(GREY_COLOR)
				2: 
					colours.append(WHITE_COLOR)
					
	tables[Mesh.ARRAY_VERTEX] = vertex
	tables[Mesh.ARRAY_COLOR] = colours
	
	mesh = ArrayMesh.new()
	mesh.add_surface_from_arrays(Mesh.PRIMITIVE_TRIANGLES,tables)
