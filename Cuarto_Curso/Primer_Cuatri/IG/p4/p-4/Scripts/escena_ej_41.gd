extends Node3D

@export var n : int = 3		## Numero de donuts por lado
@export var m : int = 3
@export var textura1 : Texture2D = load("res://texturas/ladrillos2.jpeg")
@export var textura2 : Texture2D = load("res://texturas/mosaico.jpeg")
@export var textura3 : Texture2D = load("res://texturas/mapanormales.jpg")

func _ready():
	
	var arrayTexts := [textura1,textura2,textura3]
	
	##var cubos_tranform = Transform3D().translated(Vector3(0.5,0.5,-0.5))* Transform3D().rotated(Vector3(1,0,0),PI/2) *  Transform3D().scaled(Vector3(0.25,0.5,0.25))
	var sueloMat : StandardMaterial3D = StandardMaterial3D.new()
	sueloMat.albedo_color = Color(0.518, 0.0, 0.0, 1.0)
	sueloMat.cull_mode = BaseMaterial3D.CULL_DISABLED
	sueloMat.shading_mode = BaseMaterial3D.SHADING_MODE_PER_PIXEL
	
	var padre : Node3D = Node3D.new()
	add_child(padre)
	
	var ancho_total = 3 * (n - 1)      # Distancia total en X
	var profundidad_total = 3 * (m - 1) # Distancia total en Z
	var centro_malla = Vector3(ancho_total / 2.0, 0, profundidad_total / 2.0)


	var meshDonut : ArrayMesh = meshDonut()
	
	for i in range (n):
		for j in range(m):
			## Creacion del material segun la practica
			var donutMat : StandardMaterial3D = StandardMaterial3D.new()
			if(i!=n-1):
				donutMat.albedo_color = Color( 1.0-float(i)/float(n), 1.0-float(i)/float(n), 1.0-float(i)/float(n),1.0-float(i)/float(n))
				# Activamos la transparencia en el canal alpha del albedo color
				donutMat.transparency = BaseMaterial3D.TRANSPARENCY_ALPHA
			else:
				donutMat.albedo_texture = arrayTexts[j]
			donutMat.shading_mode = BaseMaterial3D.SHADING_MODE_PER_PIXEL
			donutMat.metallic = 1.0-(m-j)/float(m)
			donutMat.roughness = j/float(m)			
			
			var pos_donut = Vector3(3*i, 0, 3*j) - centro_malla
			
			## Creacion de la malla de uno de los donuts
			var donut : MeshInstance3D = MeshInstance3D.new()
			donut.mesh = meshDonut
			donut.material_override = donutMat
			donut.transform = Transform3D().translated(pos_donut)*Transform3D().rotated(Vector3(1,0,0),PI/2)*Transform3D().scaled(Vector3(1/1.2,1/1.2,1))
			get_child(0).add_child(donut)

	var suelo := MeshInstance3D.new()
	suelo.mesh = Propio.ArrayMeshCuadrilatero(Vector3(0,-0.5,0),3*n,3*m,1)
	suelo.material_override = sueloMat
	suelo.position = -1.5*centro_malla
	get_child(0).add_child(suelo)
	
## Genera una mesh de un donut centrado en el (0,0,0)
func meshDonut() -> ArrayMesh:
	## crear las tablas de vértices y triángulos de un Donut 
	var vertices   := PackedVector3Array([])
	var triangulos := PackedInt32Array([])
	
	Utilidades.generarDonut( vertices, triangulos )
	
	var uvs := Utilidades.calcUVPerfil(vertices)
	
	var normales := Utilidades.calcNormales( vertices, triangulos )
			
	## inicializar el array con las tablas
	var tablas : Array = []   ## tabla vacía incialmente
	tablas.resize( Mesh.ARRAY_MAX ) ## redimensionar al tamaño adecuado
	tablas[ Mesh.ARRAY_VERTEX ] = vertices
	tablas[ Mesh.ARRAY_INDEX  ] = triangulos
	tablas[ Mesh.ARRAY_NORMAL ] = normales
	tablas[ Mesh.ARRAY_TEX_UV ] = uvs
	
	## crear e inicialzar el objeto 'mesh' de este nodo 
	var mesh = ArrayMesh.new() ## crea malla en modo diferido, vacía
	mesh.add_surface_from_arrays( Mesh.PRIMITIVE_TRIANGLES, tablas )
	
	return mesh
	
