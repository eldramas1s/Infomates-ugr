extends Node2D

func _ready():
	
	var meshTriangulo = arraymeshTriandulo()
	var meshInstancetriangulo = MeshInstance2D.new()
	meshInstancetriangulo.mesh=meshTriangulo
	meshInstancetriangulo.self_modulate=Color(0,0,0)
	
	var meshCuadrado = arrayMeshCuadradoTriangulo()
	var mesh = MeshInstance2D.new()
	mesh.mesh=meshCuadrado
	mesh.self_modulate=Color(1,1,0)
	
	## Añadimos el triangulo al cuadrado y lo ponemos en su lugar.
	
	meshInstancetriangulo.transform=Transform2D()*Transform2D().translated(Vector2(-0.25,-0.25))*Transform2D().scaled(Vector2(0.5,0.5))
	mesh.add_child(meshInstancetriangulo)
	
	mesh.transform=Transform2D()*Transform2D().translated(Vector2(1,1))
	add_child(mesh)
func arrayMeshCuadradoTriangulo() -> ArrayMesh:
	var vertices = PackedVector2Array([Vector2(-1,-1),Vector2(-1,1),Vector2(1,-1),Vector2(1,1)])
	var indexes = PackedInt32Array([0,1,2,2,1,3])
	
	var tables = []
	tables.resize(Mesh.ARRAY_MAX)
	
	tables[Mesh.ARRAY_VERTEX]=vertices
	tables[Mesh.ARRAY_INDEX]=indexes
	
	var mesh = ArrayMesh.new()
	mesh.add_surface_from_arrays(Mesh.PRIMITIVE_TRIANGLES,tables)
	return mesh
	
	
	
func arraymeshTriandulo() -> ArrayMesh:
	
	var vertices = PackedVector2Array([Vector2(-1,-1),Vector2(1,-1),Vector2(0,1)])
	var indexes = PackedInt32Array([0,1,2])
	
	var tablas = []
	tablas.resize(Mesh.ARRAY_MAX)
	
	tablas[Mesh.ARRAY_VERTEX]=vertices
	tablas[Mesh.ARRAY_INDEX]=indexes
	
	var mesh = ArrayMesh.new()
	mesh.add_surface_from_arrays(Mesh.PRIMITIVE_TRIANGLES,tablas)
	return mesh
	
## La generacion de las aristas no supone ningun aprendizaje, este tio hace ejercicios por hacer. Para 
## generarlas simplemente hay que usar primitive_lines y al asignarles un material usar modulate.
