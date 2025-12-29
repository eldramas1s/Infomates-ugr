## Nombre: Lucas, Apellidos: Hidalgo Herrera, Titulación: GIM
## email: lucashidalgo@correo.ugr.es, DNI o pasaporte: 26512990Q
extends MeshInstance3D

func _ready():
	
	var cubo_mesh =MeshInstance3D.new()
	cubo_mesh.mesh= Propio.CrearCubo24();
	
	cubo_mesh.transform = Transform3D().translated(Vector3(2,0.5,0.5))*Transform3D().scaled(Vector3(0.5,0.5,0.5))
	
	var material = StandardMaterial3D.new()
	material.albedo_color = Color(0.5,0,0.6)
	material.roughness = 0.7
	material.metallic = 0.5
	
	cubo_mesh.material_override = material
	
	add_child(cubo_mesh)
