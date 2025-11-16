## Nombre: Lucas, Apellidos: Hidalgo Herrera, Titulación: GIM
## email: lucashidalgo@correo.ugr.es, DNI o pasaporte: 26512990Q

extends MeshInstance3D

var mostrar_normales : bool=true
var normales : PackedVector3Array=([])
var indexes : PackedInt32Array = []
var vertex : PackedVector3Array = []

func _ready():
	var perfil = PackedVector2Array([Vector2(1,1),Vector2(1,0)])
	var n : int = 20
	
	Propio.revoluciona(perfil,n,vertex,indexes,true, true, 1 , Vector3(0,0,0))
	
	normales = Utilidades.calcNormales( vertex, indexes )
	
	#Normales.genSegNormales(vertex,normales,1.0,Color(0,0,0))	 # Llama a la función global para mostrar normales

	var tablas : Array = []
	tablas.resize( Mesh.ARRAY_MAX )
	tablas[mesh.ARRAY_VERTEX] = vertex
	tablas[mesh.ARRAY_INDEX] = indexes
	tablas[mesh.ARRAY_NORMAL] = normales
	
	mesh = ArrayMesh.new() ## crea malla en modo diferido, vacía
	mesh.add_surface_from_arrays( Mesh.PRIMITIVE_TRIANGLES, tablas )
	
	var mat := StandardMaterial3D.new() 
	mat.albedo_color = Color( 1.0, 0.5, 0.2 )
	mat.metallic = 0.3
	mat.roughness = 0.2
	mat.shading_mode = BaseMaterial3D.SHADING_MODE_PER_PIXEL
	
	material_override = mat
	
