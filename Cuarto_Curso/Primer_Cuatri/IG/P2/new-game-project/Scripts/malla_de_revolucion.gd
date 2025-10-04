extends MeshInstance3D

func _ready():
	var perfil : PackedVector2Array
	var n : int = 2
	const x0 : int = 1
	const y0 : int = 0
	
	for i in range(n):
		perfil.append(Vector2(x0,y0+n))
		
	var indexes : PackedInt32Array = []
	var vertex : PackedVector3Array = []
	
	
	Revolucion.revoluciona(perfil,n,vertex,indexes)
	
	var normales := Utilidades.calcNormales( vertex, indexes )
	
	Normales.genSegNormales(vertex,normales,1.0,Color(0,0,0))	
	
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
	
