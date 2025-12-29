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
	@warning_ignore("integer_division")
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
## Calcula las coordenadas de textura usando funciones lineales
## vertices : vertices del perfil
func CalcUVLineal(vertices : PackedVector3Array)->PackedVector2Array:
	assert(vertices.size()!=0, "necesito mas de 0 vertices")
	
	var uvs := PackedVector2Array([])
	
	return uvs
	
## -----------------------------------------------------------------------------
## Calcula las coordenadas de textura usando campos de alturas
## Realmente lo interpreto como una proyeccion en el eje y
## vertices : vertices del perfil
func CalcUVCamposAlturas(vertices : PackedVector3Array,eps:float=0.001, reps_u : float = 1.0, reps_v : float = 1.0)->PackedVector2Array:
	assert(vertices.size()!=0, "necesito mas de 0 vertices")
	assert(reps_u!=0 or reps_v!=0 , "No puedo poner texturas si no pongo una vez")
	var uvs := PackedVector2Array([])
	
	var min_x = INF; var max_x = -INF
	var min_z = INF; var max_z = -INF
	
	for v in vertices:
		min_x = min(min_x, v.x)
		max_x = max(max_x, v.x)
		min_z = min(min_z, v.z)
		max_z = max(max_z, v.z)
	
	var range_x = max_x - min_x
	var range_z = max_z - min_z
	if range_x == 0.0:
		range_x = 1.0
	if range_z == 0.0:
		range_z = 1.0
	for v in vertices:
		var u_norm = (v.x - min_x) / range_x
		var v_norm = (v.z - min_z) / range_z
		
		## Imponemos el numero de repeticiones reps_u y reps_v
		var u = u_norm * reps_u
		if u < eps:
			u += 0.0
		var vv = v_norm * reps_v
		if vv < eps:
			vv += 0.0
		uvs.append(Vector2(u,vv))
	return uvs

## -----------------------------------------------------------------------------
## Calcula las coordenadas de textura usando campos de alturas
## Realmente lo interpreto como una proyeccion en el eje x
## vertices : vertices del perfil
func CalcUVCamposAnchuras(vertices : PackedVector3Array, eps : float=0.001, reps_u : float = 1.0, reps_v : float = 1.0)->PackedVector2Array:
	assert(vertices.size()!=0, "necesito mas de 0 vertices")
	assert(reps_u!=0 or reps_v!=0 , "No puedo poner texturas si no pongo una vez")
	var uvs := PackedVector2Array([])
	var min_y = INF; var max_y = -INF
	var min_z = INF; var max_z = -INF
	
	for v in vertices:
		min_y = min(min_y, v.y)
		max_y = max(max_y, v.y)
		min_z = min(min_z, v.z)
		max_z = max(max_z, v.z)
	
	var range_y = max_y - min_y
	var range_z = max_z - min_z
	if range_z == 0.0:
		range_z = 1.0
	if range_y == 0.0:
		range_y = 1.0
	for v in vertices:
		var u_norm = (v.z - min_z) / range_z
		var v_norm = (v.y - min_y) / range_y
		
		## Imponemos el numero de repeticiones que difa reps_u y reps_v
		var u = u_norm * reps_u
		if u < eps:
			u += 0.0
		var vv = v_norm * reps_v
		if vv < eps:
			vv += 0.0
		uvs.append(Vector2(u,vv))
		
	return uvs
## -----------------------------------------------------------------------------
## Calcula las coordenadas de textura usando campos de alturas
## Realmente lo interpreto como una proyeccion en el eje z
## vertices : vertices del perfil
func CalcUVCamposProfundidad(vertices : PackedVector3Array, eps: float=0.001, reps_u : float = 1.0, reps_v : float = 1.0)->PackedVector2Array:
	assert(vertices.size()!=0, "necesito mas de 0 vertices")
	assert(reps_u!=0.0 or reps_v!=0.0 , "No puedo poner texturas si no pongo una vez")
	var uvs := PackedVector2Array([])
	
	var min_x = INF; var max_x = -INF
	var min_y = INF; var max_y = -INF
	
	for v in vertices:
		min_x = min(min_x, v.x)
		max_x = max(max_x, v.x)
		min_y = min(min_y, v.y)
		max_y = max(max_y, v.y)
	
	var range_x = max_x - min_x
	var range_y = max_y - min_y
	if range_x == 0.0:
		range_x = 1.0
	if range_y == 0.0:
		range_y = 1.0
	for v in vertices:
		var u_norm = (v.x - min_x) / range_x
		var v_norm = (v.y - min_y) / range_y
		if v_norm < eps:
			v_norm += 0.0
		if u_norm < eps:
			u_norm += 0.0
		## Imponemos el numero de repeticiones que difa reps_u y reps_v
		var u = u_norm * reps_u
		var vv = v_norm * reps_v
		
			
		uvs.append(Vector2(u,vv))
		
	return uvs
	
## -----------------------------------------------------------------------------
## Calcula las coordenadas de textura usando coordenadas esfericas
## Visualmente es introducir la figura o parte de ella en una esfera y absorber el aire de dentro
## (probablemente segun su normal)
## vertices : vertices del perfil
func CalcUVEsfericas(vertices : PackedVector3Array,eps : float=0.001,reps_u : float = 1.0, reps_v : float = 1.0)->PackedVector2Array:
	assert(reps_u!=0 or reps_v!=0 , "No puedo poner texturas si no pongo una vez")
	var uvs := PackedVector2Array()
	var max_u = 1.0
	var max_v = 1.0

	for v in vertices:
		# 1. Calcular el valor del parámetro u
		var phi = atan2(v.z, v.x)
		var u_base = max_u*((phi / (2*PI)+0.5))
		
		if u_base < eps:
			u_base += 0.0
		# 2. Calcular el valor del parámetro v
		var beta = atan2(v.y,sqrt(v.x*v.x+v.z*v.z))
		var vv_base = max_v*((beta/PI)+0.5)
		
		if vv_base < eps:
			vv_base += 0.0
			
		var vv = vv_base * reps_v
		var u = u_base * reps_u
		var uv_coords = Vector2(u, vv)
		uvs.append(uv_coords)
	return uvs
	
## -----------------------------------------------------------------------------
## Calcula las coordenadas de textura usando coordenadas cilindricas
## Visualmente es introducir la figura o parte de ella en una esfera y absorber el aire de dentro
## (probablemente segun su normal)
## vertices : vertices del perfil
func CalcUVCilindricas(vertices : PackedVector3Array,eps:float=0.001,reps_u : float = 1.0, reps_v : float = 1.0, mode : int=0)->PackedVector2Array:
	assert(mode==0 or mode==1 or mode==2, "NO se encuentra ese modo")
	assert(reps_u!=0 or reps_v!=0 , "No puedo poner texturas si no pongo una vez")
	var uvs := PackedVector2Array()
	var max_u = 1.0
	var max_v = 1.0
	var min_alt = INF
	var max_alt = -INF
	match mode:
		0 : # Cilindro base en el plano XZ
			for v in vertices:
				min_alt = min(min_alt,v.y)
				max_alt = max(max_alt,v.y)
		1:	# Cilindro base en el plano XY
			for v in vertices:
				min_alt = min(min_alt,v.z)
				max_alt = max(max_alt,v.z)
		2:	# Cilindro base en el plano YZ
			for v in vertices:
				min_alt = min(min_alt,v.x)
				max_alt = max(max_alt,v.x)
	
	
	for v in vertices:
		# 1. Calcular el valor del parámetro u
		var phi = 0.0
		var vnorm=0.0
		# 2. Calcular el valor del parámetro v
		match mode:
			0:	# Cilindro base en el plano XZ
				phi=atan2(v.z, v.x)
				vnorm = max_v*((v.y-min_alt)/(max_alt-min_alt))
			1: # Cilindro base en el plano XY
				phi=atan2(v.y,v.x)
				vnorm = max_v*((v.z-min_alt)/(max_alt-min_alt))
			2: # Cilindro base en el plano YZ
				phi=atan2(v.z,v.y)
				vnorm = max_v*((v.x-min_alt)/(max_alt-min_alt))
				
		# Normalizar ángulo base [0,1]
		var u_base = (phi / (2*PI)) + 0.5
		
		# APLICAR REPETICIONES con fmod
		var u = u_base * reps_u
		var vv = vnorm * reps_v
		
		if u < eps:
			u += 0.0
		if vv < eps:
			vv += 0.0
		
		uvs.append(Vector2(u,vv))
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

func generarDonutUV(tipo_uv : int = 0, eps:float=0.001 ,reps_u : float = 1.0, reps_v : float = 1.0,mode = 0, nu: int = 128, nv: int = 32, R: float = 1.2, r: float = 0.4)->ArrayMesh:			
	assert(tipo_uv==0 or tipo_uv==1, "No existe el tipo determinado(0,1)")
	
	var vertices := PackedVector3Array([])
	var indices := PackedInt32Array([])
	## Genera vértices con la geometría de un donut
	for i in nu: 
		for j in nv:
			vertices.append( ParamDonut( float(i)/nu, float(j)/nv, r, R )) 

	## Genera los triángulos con topología toroidal (la de un donut)	
	GenTriToroidal( nu, nv, indices )
	var normales := calcNormales(vertices, indices)
	
	
	var uvs := CalcUVCamposAlturas(vertices,eps,reps_u,reps_v)
	if tipo_uv == 1:
		uvs = CalcUVCamposProfundidad(vertices,eps,reps_u,reps_v)
		
	var tablas : Array = []
	tablas.resize(Mesh.ARRAY_MAX)
	tablas[Mesh.ARRAY_VERTEX]   = vertices
	tablas[Mesh.ARRAY_INDEX]    = indices
	tablas[Mesh.ARRAY_NORMAL]   = normales
	tablas[Mesh.ARRAY_TEX_UV]   = uvs

	var mesh := ArrayMesh.new()
	mesh.add_surface_from_arrays(Mesh.PRIMITIVE_TRIANGLES, tablas)
	return mesh
