## Nombre: Lucas, Apellidos: Hidalgo Herrera, Titulación: GIM
## email: lucashidalgo@correo.ugr.es, DNI o pasaporte: 26512990Q
extends Node

## -----------------------------------------------------------------------------
## Función que calcula las normales promedio de los vértices de una malla, 
## a partir de la tabla de posiciones de vértices y la tabla de triángulos

func calcNormales( verts : PackedVector3Array, 
				   tris  : PackedInt32Array ) -> PackedVector3Array :

	## Paso 1: comprobar precondiciones
	assert( verts.size() >= 3 , "CalcNormales: la malla debe tener al menos 3 vértices" )
	assert( tris.size() % 3 == 0 , "CalcNormales: el número de enteros en 'tris' debe ser múltiplo de 3")
	
	var nv : int = verts.size()  ## número de vértices
	var nt : int = tris.size()/3 ## número de triángulos
	
	# Paso 2: inicializa normales a cero
	var normales := PackedVector3Array([]) 
	for i in nv:
		normales.append( Vector3.ZERO )
	
	# Paso 3: sumar en cada vértice las normales de sus tris. adyacentes
	for it in nt :
		var t := Vector3i( tris[3*it+0], tris[3*it+1], tris[3*it+2] )
		var a := verts[t[0]] ; 
		var b := verts[t[1]] ; 
		var c := verts[t[2]] ; 
		var normalv := (c-a).cross(b-a).normalized()
		for iv in 3 :
			normales[t[iv]] += normalv
	
	# Paso 4: normalizar normales
	for iv in nv:
		normales[iv] = normales[iv].normalized()
	
	# Hecho
	return normales

## -----------------------------------------------------------------------------
##
## Función de parametrización de un toroide o donut 
##
##    u = 1er parámetro (entre 0 y 1)
##    v = 2o parámetro (entre 0 y 1)
##    R  = radio mayor 
##    r  = radio menor

func ParamDonut( u,v, r, R : float ) -> Vector3:

		var cu := cos(2.0*PI*u); var su := sin(2.0*PI*u)
		var cv := cos(2.0*PI*v); var sv := sin(2.0*PI*v)
		return Vector3( (R+r*cv)*cu, (R+r*cv)*su, r*sv )

## -----------------------------------------------------------------------------
## 
## Genera una tabla de triángulos (indices) con topología toroidal
## los añade a 'indices', 
##
##    nu = numero de divisiones del 1er parámetro
##    nv = numero de divisiones del 2o parámetro	
##    indices = tabla donde se añaden los triángulos 

func GenTriToroidal( nu, nv : int , indices : PackedInt32Array )  :
	
	for i in nu: 
		var isig = (i + 1) % nu
		for j in nv:
			var jsig = (j + 1) % nv
			var i00 = i    * nv + j
			var i01 = i    * nv + jsig
			var i10 = isig * nv + j
			var i11 = isig * nv + jsig
			
			indices.append(i00); indices.append(i11); indices.append(i10)
			indices.append(i00); indices.append(i01); indices.append(i11)
					
## -----------------------------------------------------------------------------
## 
## Función que genera un toroide (Donut), con 'nu x nv' vértices 
## (como una malla indexada con vértices compartidos entre triángulos adyacentes)
##
##    vertices : tabla de vértices (añade)
##    indices : tabla de índices (añade)
##    nu = numero de divisiones del 1er parámetro
##    nv = numero de divisiones del 2o parámetro	
##    R  = radio mayor 
##    r  = radio menor

func generarDonut( vertices: PackedVector3Array, 
 					indices: PackedInt32Array, 
					nu: int = 128, nv: int = 32,   
					R: float = 1.2, r: float = 0.4):			
	
	## Genera vértices con la geometría de un donut
	for i in nu: 
		for j in nv:
			vertices.append( ParamDonut( float(i)/nu, float(j)/nv, r, R )) 

	## Genera los triángulos con topología toroidal (la de un donut)	
	GenTriToroidal( nu, nv, indices )

## -----------------------------------------------------------------------------
## 
## Función que calcula las coordenadas de textura de una malla de vertices en funcion del perfil
##
##
##    vertices : vertices de la malla
static func calcUVPerfil(vertices: PackedVector3Array) -> PackedVector2Array:
	var uvs := PackedVector2Array()

	# Obtenemos los radios del toroide, R y rho
	var min_radio_xy = INF
	var max_radio_xy = 0.0
	var min_y = INF
	var max_y = -INF

	for v in vertices:
		var radio = sqrt(v.x*v.x + v.y*v.y)  # distancia en plano XY
		min_radio_xy = min(radio, min_radio_xy)
		max_radio_xy = max(radio, max_radio_xy)
		min_y = min(v.y, min_y)
		max_y = max(v.y, max_y)

	var R = (min_radio_xy + max_radio_xy) / 2.0      # radio mayor
	var rho = (max_radio_xy - min_radio_xy) / 2.0    # radio menor
	var centro_y = (min_y + max_y) / 2.0             # centro en Y

	## Aunque es un caso trivial debemos evitar divisiones por cero
	if rho == 0.0:
		rho = 1.0

	## Calculo de las UV
	for vertex in vertices:
		# u: ángulo de revolución (en plano XY alrededor de Z)
		var phi = atan2(vertex.y, vertex.x)
		var u = (phi + PI) / TAU              # Normalizar [-π, π] → [0,1]
		if u > 0.999:
			u = 0.0
		
		# v: ángulo del perfil (círculo local del tubo)
		# El perfil está en el plano que contiene el eje Z y el radio
		var radio_actual = sqrt(vertex.x*vertex.x + vertex.y*vertex.y)
		var dy = vertex.y - centro_y          # desplazamiento vertical desde el centro
		var dx_perfil = radio_actual - R      # desplazamiento radial desde el radio mayor
		
		var theta_perfil = atan2(dy, dx_perfil)  # ángulo en el plano del perfil
		var v = (theta_perfil + PI) / TAU         # Normalizar [-π, π] → [0,1]
		if v > 0.999:
			v = 0.0
		
		uvs.append(Vector2(u, v))


	return uvs
	
## -----------------------------------------------------------------------------
## 
## Función que calcula las coordenadas de textura de una malla de vertices en funcion de la altura
##
##
##    vertices : vertices de la malla
static func calcUVProfundo(vertices: PackedVector3Array) -> PackedVector2Array:
	var uvs := PackedVector2Array()
	var max_u = 1.0
	var max_v = 1.0
	# Encontramos el min y el max de Y para normalizar v
	var min_z = vertices[0].z
	var max_z = vertices[0].z
	
	## Asignamos los bordes mediante una retraccion
	for vertex in vertices:
		if vertex.z < min_z:
			min_z = vertex.z
		if vertex.z > max_z:
			max_z = vertex.z
	
	## Calculamos el rango de valores de y
	## Cuando el maximo y el minimo coinciden asumimos como rango el valor 1
	var range_z = max_z- min_z
	if range_z == 0:
		range_z = 1.0  # Evita división por cero
		
	for vertex in vertices:
		# 1. Calcular el valor del parámetro u
		var phi = atan2(vertex.y, vertex.x)
		var u = max_u*((phi / (2*PI)+0.5))
		# 2. Calcular el valor del parámetro v
		
		## Opcion basada en la altura, es decir, de forma aproximada en funcion de y
		var v = max_v * ((vertex.z - min_z) / range_z)
		
		#Puedes calcularlo en función del desplazaniento en el perfil
		# o de forma aproximada en función de y
		var uv_coords = Vector2(u, v)
		uvs.append(uv_coords)
		
	return uvs
## -----------------------------------------------------------------------------
## 
## Función que calcula las coordenadas de textura de una malla de vertices enfuncion del Radio
##
##
##    vertices : vertices de la malla
static func calcUVAltura(vertices: PackedVector3Array) -> PackedVector2Array:
	var uvs := PackedVector2Array()
	var max_u = 1.0
	var max_v = 1.0
	# Encontramos el min y el max de Y para normalizar v
	var min_y = vertices[0].y
	var max_y = vertices[0].y
	
	## Asignamos los bordes mediante una retraccion
	for vertex in vertices:
		if vertex.y < min_y:
			min_y = vertex.y
		if vertex.y > max_y:
			max_y = vertex.y
	
	## Calculamos el rango de valores de y
	## Cuando el maximo y el minimo coinciden asumimos como rango el valor 1
	var range_y = max_y- min_y
	if range_y == 0:
		range_y = 1.0  # Evita división por cero
		
	for vertex in vertices:
		# 1. Calcular el valor del parámetro u
		var phi = atan2(vertex.y, vertex.x)
		var u = max_u*((phi / (2*PI)+0.5))
		# 2. Calcular el valor del parámetro v
		
		## Opcion basada en la altura, es decir, de forma aproximada en funcion de y
		var v = max_v * ((vertex.y - min_y) / range_y)
		
		#Puedes calcularlo en función del desplazaniento en el perfil
		# o de forma aproximada en función de y
		var uv_coords = Vector2(u, v)
		uvs.append(uv_coords)
		
	return uvs

## -----------------------------------------------------------------------------
## 
## Crea un objeto ImageTexture a raiz de la ruta dentro del proyecto
##
##
##    arch : ruta en el proyecto.
func CargarTextura( arch : String ) -> ImageTexture :
	## crear un objeto 'Image' con la imgen
	var imagen := Image.new()
	assert( imagen.load(arch) == OK, "Error cargando '"+arch+"'." )
	## crear un objeto 'ImageTexture' a partir del objeto 'Image'
	var textura := ImageTexture.create_from_image( imagen )
	#print("Textura cargada desde archivo: '",arch,"'.")
	## devolver la textura
	return textura
## -----------------------------------------------------------------------------
## 
## Función que calcula las coordenadas de textura de una malla de vertices enfuncion del Radio
##
##
##    vertices : vertices de la malla
static func calcUVParalelos(vertices: PackedVector3Array) -> PackedVector2Array:
	var uvs := PackedVector2Array()

	var min_radio_xy = INF
	var max_radio_xy = 0.0
	var min_y = INF
	var max_y = -INF

	for v in vertices:
		var radio = sqrt(v.x*v.x + v.y*v.y)
		min_radio_xy = min(radio, min_radio_xy)
		max_radio_xy = max(radio, max_radio_xy)
		min_y = min(v.y, min_y)
		max_y = max(v.y, max_y)

	var range_radio = max_radio_xy - min_radio_xy
	var range_y = max_y - min_y

	if range_radio == 0.0:
		range_radio = 1.0
	if range_y == 0.0:
		range_y = 1.0

	for vertex in vertices:
		# u: normalizar radio (de centro hacia afuera)
		var radio = sqrt(vertex.x*vertex.x + vertex.y*vertex.y)
		var u = (radio - min_radio_xy) / range_radio

		# v: normalizar altura Y
		var v = (vertex.y - min_y) / range_y

		uvs.append(Vector2(u, v))

	return uvs

static func calcUVVerticales(vertices: PackedVector3Array) -> PackedVector2Array:
	var uvs := PackedVector2Array()
	var max_u = 1.0
	var max_v = 1.0
	# Encontramos el min y el max de Y para normalizar v
	var min_z = vertices[0].z
	var max_z = vertices[0].z
	
	## Asignamos los bordes mediante una retraccion
	for vertex in vertices:
		if vertex.z < min_z:
			min_z = vertex.z
		if vertex.z > max_z:
			max_z = vertex.z
	
	## Calculamos el rango de valores de y
	## Cuando el maximo y el minimo coinciden asumimos como rango el valor 1
	var range_z = max_z- min_z
	if range_z == 0:
		range_z = 1.0  # Evita división por cero
		
	for vertex in vertices:
		# 1. Calcular el valor del parámetro u
		var phi = atan2(vertex.y, vertex.x)
		var u = max_u*((phi / (2*PI/4)+0.5))
		# 2. Calcular el valor del parámetro v
		
		## Opcion basada en la altura, es decir, de forma aproximada en funcion de y
		var v = max_v * ((vertex.z - min_z) / (range_z))
		
		#Puedes calcularlo en función del desplazaniento en el perfil
		# o de forma aproximada en función de y
		var uv_coords = Vector2(v, u)
		uvs.append(uv_coords)
		
	return uvs

## -----------------------------------------------------------------------------
## 
## Función que genera un toroide (Donut), con 'nu x nv' vértices 
## (como una malla indexada con vértices compartidos entre triángulos adyacentes)
##
##    vertices : tabla de vértices (añade)
##    indices : tabla de índices (añade)
## 	  tipo_uv : 0 -> con coordenadas xy
##	  			1 -> con coordenadas xz
##    nu = numero de divisiones del 1er parámetro
##    nv = numero de divisiones del 2o parámetro	
##    R  = radio mayor 
##    r  = radio menor

func generarDonutUV( tipo_uv = 0, nu: int = 128, nv: int = 32, R: float = 1.2, r: float = 0.4)->ArrayMesh:			
	
	var vertices := PackedVector3Array([])
	var indices := PackedInt32Array([])
	## Genera vértices con la geometría de un donut
	for i in nu: 
		for j in nv:
			vertices.append( ParamDonut( float(i)/nu, float(j)/nv, r, R )) 

	## Genera los triángulos con topología toroidal (la de un donut)	
	GenTriToroidal( nu, nv, indices )
	var normales := calcNormales(vertices, indices)
	
	var uvs := calcUVVerticales(vertices)
	if tipo_uv == 1:
		uvs = calcUVVerticales(vertices)
		
	var tablas : Array = []
	tablas.resize(Mesh.ARRAY_MAX)
	tablas[Mesh.ARRAY_VERTEX]   = vertices
	tablas[Mesh.ARRAY_INDEX]    = indices
	tablas[Mesh.ARRAY_NORMAL]   = normales
	tablas[Mesh.ARRAY_TEX_UV]   = uvs

	var mesh := ArrayMesh.new()
	mesh.add_surface_from_arrays(Mesh.PRIMITIVE_TRIANGLES, tablas)
	return mesh
