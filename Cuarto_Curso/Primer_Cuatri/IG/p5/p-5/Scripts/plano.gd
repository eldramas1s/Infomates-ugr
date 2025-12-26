extends MeshInstance3D


func _ready():
	var plano_mesh = MeshInstance3D.new()
	
	plano_mesh.mesh = Propio.ArrayMeshRejilla(20,20,1,Vector3(-10,0,-10),20,20)
	plano_mesh.transform = Transform3D().rotated(Vector3(1,0,0),PI)
	var material = StandardMaterial3D.new()
	material.albedo_color = Color(0.5,0.7,0.5)
	material.metallic = 0.0
	material.roughness = 1.0
	material.cull_mode = BaseMaterial3D.CULL_DISABLED
	
	plano_mesh.material_override = material

	add_child(plano_mesh)
	
