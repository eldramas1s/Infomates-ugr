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
## Función que calcula las coordenadas de textura de una malla de vertices en funcion de la altura
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
	var range_y = max_y - min_y
	if range_y == 0:
		range_y = 1.0  # Evita división por cero
		
	for vertex in vertices:
		# 1. Calcular el valor del parámetro u
		var phi = atan2(vertex.z, vertex.x)
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
## Función que calcula las coordenadas de textura de una malla de vertices enfuncion del Radio
##
##
##    vertices : vertices de la malla
static func calcUVRadio(vertices: PackedVector3Array) -> PackedVector2Array:
	var uvs := PackedVector2Array()
	var max_u = 1.0
	var max_v = 1.0
	# Encontramos el min y el max de Y para normalizar v
	var min_radius = sqrt(vertices[0].x * vertices[0].x + vertices[0].z * vertices[0].z)
	var max_radius = min_radius
	
	
	## Asignamos los bordes mediante una retraccion
	for vertex in vertices:
		var radius = sqrt(vertex.x * vertex.x + vertex.z * vertex.z)
		if radius < min_radius:
			min_radius = radius
		if radius > max_radius:
			max_radius = radius
	
	## Calculamos el rango de valores de y
	## Cuando el maximo y el minimo coinciden asumimos como rango el valor 1
	var range_radius = max_radius - min_radius
	if range_radius == 0:
		range_radius = 1.0  # Evita división por cero
		
	for vertex in vertices:
		# 1. Calcular el valor del parámetro u
		var phi = atan2(vertex.z, vertex.x)
		var u = max_u*((phi / (2*PI)+0.5))
		# 2. Calcular el valor del parámetro v
		
		## Opcion basada en funcion del desplazamiento del perfil
		var radius = sqrt(vertex.x * vertex.x + vertex.z * vertex.z)
		var v = max_v * ((radius - min_radius) / range_radius)
		
		#Puedes calcularlo en función del desplazamiento en el perfil
		# o de forma aproximada en función de y
		var uv_coords = Vector2(u, v)
		uvs.append(uv_coords)
		
	return uvs
