## Nombre: Lucas, Apellidos: Hidalgo Herrera, Titulación: GIM
## email: lucashidalgo@correo.ugr.es, DNI o pasaporte: 26512990Q

extends MeshInstance3D

@export var altura: float = 0.25

var material = StandardMaterial3D.new()

func _ready():
	#var piramide = crear_piramide(altura)
	#var mesh_instance = MeshInstance3D.new()
	#mesh_instance.mesh = piramide
	#material.albedo_color = Color(1.0, 0.1, 0.2)  # Naranja claro
	#mesh_instance.material_override = material
	#add_child(mesh_instance)
	
	var casa = crear_casaX(altura)
	var mesh_instance = MeshInstance3D.new()
	var mat := StandardMaterial3D.new() 
	mat.shading_mode = BaseMaterial3D.SHADING_MODE_UNSHADED		# Sin iluminacion
	mat.vertex_color_use_as_albedo = true						# Difuminado de colores segun vertices
	mesh_instance.material_override = mat
	mesh_instance.mesh = casa
	add_child(mesh_instance)

func crear_casaX(h: float) -> ArrayMesh:
	var st = SurfaceTool.new()
	st.begin(Mesh.PRIMITIVE_TRIANGLES)

	# Coordenadas de la base (cuadrado centrado en el origen, lado 1)
	var p1 = Vector3(0, 0.75, 0)
	var p2 = Vector3( 1, 0.75, 0)
	var p3 = Vector3( 1, 0.75,0.75)
	var p4 = Vector3(0, 0.75,0.75)
	
	
	var c1 = Vector3(0, 0, 0)  # 0: Adelante-Izquierda-Abajo
	var c2 = Vector3( 1, 0, 0)  # 1: Adelante-Derecha-Abajo
	var c3 = Vector3( 1, 0,0.75)  # 2: Atrás-Derecha-Abajo
	var c4 = Vector3(0, 0,0.75)  # 3: Atrás-Izquierda-Abajo
	
	# Vertices de arriba
	
	var c5 = Vector3(0,  0.75, 0)  # 4: Adelante-Izquierda-Arriba
	var c6 = Vector3( 1,  0.75, 0)  # 5: Adelante-Derecha-Arriba
	var c7 = Vector3( 1,  0.75,0.75)  # 6: Atrás-Derecha-Arriba
	var c8 = Vector3(0,  0.75,0.75)  # 7: Atrás-Izquierda-Arriba

	var apex1 = Vector3(0, 0.75+h, 0.37)  # cúspide izquierda
	var apex2 = Vector3(1, 0.75+h, 0.37)	# cuspide derecha


	# Paredes tejado 
	_add_triangulowithcolor(st,p4,p1,apex1)
	_add_triangulowithcolor(st,p2,p3,apex2)

	# Tejado (triángulos)
	_add_triangulowithcolor(st, p1, p2, apex2)
	_add_triangulowithcolor(st, p1, apex2, apex1)
	_add_triangulowithcolor(st, p3, p4, apex1)
	_add_triangulowithcolor(st, p3, apex1, apex2)

	# Base (dos triángulos)
	#_add_triangulowithcolor(st, p1, p3, p2, Vector3.DOWN)
	#_add_triangulowithcolor(st, p1, p4, p3, Vector3.DOWN)
	
	#Cara frontal
	#triangulos.append_array([0,5,1,0,4,5])
	_add_triangulowithcolor(st,c1,c2,c6)
	_add_triangulowithcolor(st,c1,c6,c5)	
	
	#Cara derecha
	#triangulos.append_array([1,6,2,1,5,6])
	_add_triangulowithcolor(st,c2,c3,c7)
	_add_triangulowithcolor(st,c2,c7,c6)
	
	#Cara trasera
	#triangulos.append_array([2,7,3,2,6,7])
	_add_triangulowithcolor(st,c3,c4,c8)
	_add_triangulowithcolor(st,c3,c8,c7)
	
	#Cara izquierda
	#triangulos.append_array([3,4,0,3,7,4])
	_add_triangulowithcolor(st,c4,c1,c5)
	_add_triangulowithcolor(st,c4,c5,c8)
	
	##Cara superior (no necesaria)
	#triangulos.append_array([5,7,6,5,4,7])
	#_add_triangulowithcolor(st,c6,c8,c7)
	#_add_triangulowithcolor(st,c6,c5,c8)
	
	#Cara inferior
	#triangulos.append_array([3,0,1,3,1,2])
	_add_triangulowithcolor(st,c4,c2,c1)
	_add_triangulowithcolor(st,c4,c3,c2)

	return st.commit()

# Añade triángulo y calcula normal automáticamente
func _add_triangulowithcolor(st: SurfaceTool, a: Vector3, b: Vector3, c: Vector3, normal_override: Vector3 = Vector3.ZERO):
	var normal = normal_override
	if normal == Vector3.ZERO:
		normal = Plane(a, b, c).normal
	st.set_normal(normal)
	st.set_color(Color(a.x,a.y,a.z))
	st.add_vertex(a)
	st.set_color(Color(b.x,b.y,b.z))
	st.add_vertex(b)
	st.set_color(Color(c.x,c.y,c.z))
	st.add_vertex(c)
	
