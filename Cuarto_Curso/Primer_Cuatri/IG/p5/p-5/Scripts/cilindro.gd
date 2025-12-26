extends MeshInstance3D

func _ready():
	var perfil := [Vector2(0.5,1),Vector2(0.5,0)]
	
	var vertex = PackedVector3Array([])
	var indexes = PackedInt32Array([])
	var cilindro_mesh = MeshInstance3D.new()
	cilindro_mesh.mesh = Propio.revolucionaUV(perfil,30,true,true)
	
	var material = StandardMaterial3D.new()
	material.albedo_texture = Utilidades.CargarTextura("res://texturas/textura_lana.jpg")
	material.roughness = 0.0
	material.metallic = 0.5
	
	cilindro_mesh.material_override = material
	
	add_child(cilindro_mesh)
