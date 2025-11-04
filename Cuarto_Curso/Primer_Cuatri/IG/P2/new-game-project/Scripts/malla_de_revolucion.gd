extends MeshInstance3D

var mostrar_normales : bool=true
var normales : PackedVector3Array=([])
var indexes : PackedInt32Array = []
var vertex : PackedVector3Array = []

func _ready():
	var perfil = PackedVector2Array([Vector2(1,1),Vector2(1,0),Vector2(0,-1)])
	var n : int = 20
	const x0 : int = 1
	const y0 : int = 0
	
	Revolucion.revoluciona(perfil,n,vertex,indexes,true, false, 2 , Vector3(1,0,0))
	
	var normales := Utilidades.calcNormales( vertex, indexes )
	
	Normales.genSegNormales(vertex,normales,1.0,Color(0,0,0))	 # Llama a la función global para mostrar normales

	var tablas : Array = []
	tablas.resize( Mesh.ARRAY_MAX )
	tablas[mesh.ARRAY_VERTEX] = vertex
	tablas[mesh.ARRAY_INDEX] = indexes
	
	mesh = ArrayMesh.new() ## crea malla en modo diferido, vacía
	mesh.add_surface_from_arrays( Mesh.PRIMITIVE_TRIANGLES, tablas )
	
	var mat := StandardMaterial3D.new() 
	mat.albedo_color = Color( 1.0, 0.5, 0.2 )
	mat.metallic = 0.3
	mat.roughness = 0.2
	mat.shading_mode = BaseMaterial3D.SHADING_MODE_PER_PIXEL
	
	material_override = mat
	
