## Nombre: Lucas, Apellidos: Hidalgo Herrera, Titulación: GIM
## email: lucashidalgo@correo.ugr.es, DNI o pasaporte: 26512990Q

## Aclaracion: en muchas funciones que devuelven un objeto mesh como resultado, se ha impuesto el material
## usando la sentencia mesh.surface_set_material(0,mat) donde mat es un material ya creado.
## Esta funcion lo que hace es: 
## 			asignar el material mat a la superficie de índice 0 del objeto ArrayMesh denominado mesh
## En nuestro caso, es la unica malla que se ha creado.
## Como alternativa, se podria asignar el material en la funcion _ready(), no obstante, se sigue cumpliendo
## la restriccion del ejercicio de no crear un material por cada malla, pues solo se genera una vez la malla. 

## No obstante, no se ha usado, se ha dejado como opcion
extends Node

## -----------------------------------------------------------------------------
## 
## Función que invierte las caras de una malla indexada
##
##    indexes : indices de la malla antigua
##	  newindexes : indices de la malla con caras invertidas
## Esta funcion no reemplaza los indices por una nueva posible utilizacion de la antigua
func invertMesh(indexes : PackedInt32Array, newindexes : PackedInt32Array):
	# Esta funcion se encarga de cambiar toda una mesh de orientacion en una nueva cadena de indices, es decir, lo que eran caras delanteras ahora son traseras y al reves.

	for i in range(0,indexes.size()-2,3):
		newindexes.append(indexes[i])
		newindexes.append(indexes[i+2])
		newindexes.append(indexes[i+1])
		
## -----------------------------------------------------------------------------
## 
## Función que une dos mallas trabajando solo con vertices e indices
##	  
##	  vertex1 : vertices contenedores
##    indexes1 : indices contenedores
##	  vertex2 : vertices a unir
##	  indexes2 : indices a unir
func uneMallas(vertex1 : PackedVector3Array, indexes1 : PackedInt32Array, vertex2 : PackedVector3Array, indexes2 : PackedInt32Array):
	if(vertex2.size()>0 and indexes2.size()>0):	
		var tam_vertex_orig = vertex1.size()
		for i in range(vertex2.size()):
			vertex1.append(vertex2[i])
		
		for i in range(indexes2.size()):
			indexes1.append(indexes2[i]+tam_vertex_orig)

## -----------------------------------------------------------------------------
## 
## Función quedevuelve los indices y los vertices de una malla de un cubo de lado 2
##	  
##	  vertex1 : vertices contenedores
##    indexes1 : indices contenedores
##	  vertex2 : vertices a unir
##	  indexes2 : indices a unir
func CrearCuadrilatero(pto : Vector3, altura : float, base : float, eje : int, vertex : PackedVector3Array, indexes : PackedInt32Array):
		assert(eje == 0 or eje == 1 or eje == 2, "Eje erroneo")
		assert(altura > 0 and base > 0, "No puedo crear un cuadrilatero sin base o sin altura")		# solo permito eso, necesito el inferior izquierda
		
		# Vacio los contenedores que me dan, aqui estoy creando una solo pieza
		vertex.clear()
		indexes.clear()
		
		# Comenzamos la creacion de la pieza
		
		match eje:
			0:	# z=0
				vertex.append(pto)
				vertex.append(pto+Vector3(base,0,0))
				vertex.append(pto+Vector3(base,altura,0))
				vertex.append(pto+Vector3(0,altura,0))
				
			1:	# y=0
				vertex.append(pto)
				vertex.append(pto+Vector3(0,0,base))
				vertex.append(pto+Vector3(altura,0,base))
				vertex.append(pto+Vector3(altura,0,0))
			2:	# x=0
				vertex.append(pto)
				vertex.append(pto+Vector3(0,base,0))
				vertex.append(pto+Vector3(0,base,altura))
				vertex.append(pto+Vector3(0,0,altura))
				
		indexes.append(0)
		indexes.append(1)
		indexes.append(2)
		indexes.append(0)
		indexes.append(2)
		indexes.append(3)

## -----------------------------------------------------------------------------
## 
## Función que devuelve la malla de un cuadrilatero
##	  
##	  mismos atributos que crearCuadrilatero
func ArrayMeshCuadrilatero(pto : Vector3, altura : float, base : float, eje : int):
	var indexes : PackedInt32Array = []
	var vertex : PackedVector3Array = []
	
	CrearCuadrilatero(pto,altura,base,eje,vertex,indexes)
	
	var tablas : Array = []   ## tabla vacía incialmente
	tablas.resize( Mesh.ARRAY_MAX ) ## redimensionar al tamaño adecuado
	tablas[ Mesh.ARRAY_VERTEX ] = vertex
	tablas[ Mesh.ARRAY_INDEX  ] = indexes
	tablas[ Mesh.ARRAY_NORMAL ] = Utilidades.calcNormales(vertex, indexes)
	
	## crear e inicialzar el objeto 'mesh' de este nodo 
	var mesh = ArrayMesh.new() ## crea malla en modo diferido, vacía
	mesh.add_surface_from_arrays( Mesh.PRIMITIVE_TRIANGLES, tablas )
	
	return mesh
	
## -----------------------------------------------------------------------------
## 
## Función que devuelve la malla de una estrella de n puntas
##	  
##	  n : numero de puntas
##    rad : radio
##	  eje: entero que refleja el eje a usar (0,1,2)->(z=0,y=0,x=0)
##	  centro : punto central de la estrella
func ArrayMeshPoligonoRegular( n: int, rad : float, eje:int, centro : Vector3 = Vector3(0,0,0) ) -> ArrayMesh :
	
	var indexes : PackedInt32Array = []
	var vertex : PackedVector3Array = []
	var colors : PackedColorArray = []
	
	assert(eje==0 or eje == 1 or eje==2, "No ha seleccionado ningun eje")
	
	match eje:
		0:
			#Eje z = 0
			#assert(centro.z==0, "z=0")	# Esta linea sirve para forzar que sea el plano z=0
			for i in range(n):
				vertex.append(rad*Vector3(cos((2*PI*i)/n),sin((2*PI*i)/n),0))
	
		1: 	
			# Eje y = 0
			#assert(centro.y==0, "y=0") # Esta linea sirve para forzar que sea el plano z=0
			for i in range(n):
				vertex.append(rad*Vector3(sin((2*PI*i)/n),0,cos((2*PI*i)/n)))
		
		2: 
			# Eje x = 0
			#assert(centro.x==0, "x=0") # Esta linea sirve para forzar que sea el plano z=0
			for i in range(n):
				vertex.append(rad*Vector3(0,cos((2*PI*i)/n), sin((2*PI*i)/n)))
	
	# Trasladamos los vertices al centro correspondiente
	for i in range(n):
		vertex[i] = vertex[i] + centro
	
	vertex.append(centro)	# Esta en la posicion n del array de vertices.
	
	
	# Triangulos
	for i in range(n):
		indexes.append(i%n)
		indexes.append(n)
		indexes.append((i+1)%n)
	
	# Añadimos los colores
	for i in range(n):
		colors.append(Color(vertex[i].x,vertex[i].y,vertex[i].z))
		
	colors.append(Color(1, 1, 1))
	
	
	# Creamos la malla y le asignamos las cosas que hemos creado
	## inicializar el array con las tablas
	var tablas : Array = []   ## tabla vacía incialmente
	tablas.resize( Mesh.ARRAY_MAX ) ## redimensionar al tamaño adecuado
	tablas[ Mesh.ARRAY_VERTEX ] = vertex
	tablas[ Mesh.ARRAY_INDEX  ] = indexes
	tablas[ Mesh.ARRAY_NORMAL ] = Utilidades.calcNormales(vertex, indexes)
	tablas[ Mesh.ARRAY_COLOR ] = colors
	
	## crear e inicialzar el objeto 'mesh' de este nodo 
	var mesh = ArrayMesh.new() ## crea malla en modo diferido, vacía
	mesh.add_surface_from_arrays( Mesh.PRIMITIVE_TRIANGLES, tablas )
	
	
	##  Con esta forma creamos una mesh con material incluido
	#var mat := StandardMaterial3D.new() 
	#mat.shading_mode = BaseMaterial3D.SHADING_MODE_UNSHADED  # Sin iluminacion
	#mat.cull_mode = BaseMaterial3D.CULL_DISABLED
	#mat.vertex_color_use_as_albedo = true		# Permite difuminado de colores
	#
	#mesh.surface_set_material(0, mat)
	
	return mesh
	

## -----------------------------------------------------------------------------
## 
## Función que devuelve los indices y los vertices de una malla de una estrella de n puntas
##	  
##	  n : numero de puntas
##    rad1,rad2 : radios interior y exterior
##	  eje: entero que refleja el eje a usar (0,1,2)->(z=0,y=0,x=0)
##	  centro : punto central de la estrella
func EstrellaZ(n: int, rad1 : float, rad2 : float, eje:int, vertex : PackedVector3Array, indexes : PackedInt32Array, colors : PackedColorArray, centro : Vector3 = Vector3(0,0,0)):
	
	# Limpiamos zona de trabajo
	vertex.clear()
	indexes.clear()
	colors.clear()
	
	# Establecemos los radios
	var radg : float=max(rad1,rad2)
	var radp : float=min(rad1,rad2)

	assert(eje==0 or eje == 1 or eje==2, "No ha seleccionado ningun eje")
	
	match eje:
		0:
			#Eje z = 0
			#assert(centro.z==0, "z=0")	# Esta linea sirve para forzar que sea el plano z=0
			for i in range(n):
				vertex.append(radg*Vector3(cos((2*PI*i)/n),sin((2*PI*i)/n),0))
				vertex.append(radp*Vector3(cos(2*PI*(i+0.5)/n),sin(2*PI*(i+0.5)/n),0))
	
		1: 	
			# Eje y = 0
			#assert(centro.y==0, "y=0") # Esta linea sirve para forzar que sea el plano z=0
			for i in range(n):
				vertex.append(radg*Vector3(sin((2*PI*i)/n),0,cos((2*PI*i)/n)))
				vertex.append(radp*Vector3(sin((2*PI*(i+0.5))/n),0,cos((2*PI*(i+0.5))/n)))
		
		2: 
			# Eje x = 0
			#assert(centro.x==0, "x=0") # Esta linea sirve para forzar que sea el plano z=0
			for i in range(n):
				vertex.append(radg*Vector3(0,cos((2*PI*i)/n), sin((2*PI*i)/n)))
				vertex.append(radp*Vector3(0,cos((2*PI*(i+0.5))/n), sin((2*PI*(i+0.5))/n)))
	
	# Trasladamos los vertices al centro correspondiente
	for i in range(2*n):
		vertex[i] = vertex[i] + centro
	
	vertex.append(centro)	# Esta en la posicion 2n del array de vertices.
	
	
	# Triangulos
	for i in range(2*n):
		indexes.append(i%(2*n))
		indexes.append(2*n)
		indexes.append((i+1)%(2*n))
	
	# Añadimos los colores
	for i in range(2*n):
		colors.append(Color(vertex[i].x,vertex[i].y,vertex[i].z))
		
	colors.append(Color(1, 1, 1))
	
## -----------------------------------------------------------------------------
## 
## Función que devuelve la malla de una estrella de n puntas
##	  
##	  n : numero de puntas
##    rad1,rad2 : radios interior y exterior
##	  eje: entero que refleja el eje a usar (0,1,2)->(z=0,y=0,x=0)
##	  centro : punto central de la estrella
func ArrayMeshEstrellaZ(n: int, rad1 : float, rad2 : float, eje:int, centro : Vector3 = Vector3(0,0,0) ) -> ArrayMesh :
	
	var indexes : PackedInt32Array = []
	var vertex : PackedVector3Array = []
	var colors : PackedColorArray = []
	
	EstrellaZ(n,rad1,rad2,eje,vertex,indexes,colors,centro)
	
	# Creamos la malla y le asignamos las cosas que hemos creado
	## inicializar el array con las tablas
	var tablas : Array = []   ## tabla vacía incialmente
	tablas.resize( Mesh.ARRAY_MAX ) ## redimensionar al tamaño adecuado
	tablas[ Mesh.ARRAY_VERTEX ] = vertex
	tablas[ Mesh.ARRAY_INDEX  ] = indexes
	tablas[ Mesh.ARRAY_NORMAL ] = Utilidades.calcNormales(vertex, indexes)
	tablas[ Mesh.ARRAY_COLOR ] = colors
	
	## crear e inicialzar el objeto 'mesh' de este nodo 
	var mesh = ArrayMesh.new() ## crea malla en modo diferido, vacía
	mesh.add_surface_from_arrays( Mesh.PRIMITIVE_TRIANGLES, tablas )
	
	## Con esta forma estamos creando la mesh con el material 
	#var mat := StandardMaterial3D.new() 
	#mat.shading_mode = BaseMaterial3D.SHADING_MODE_UNSHADED		# Sin iluminacion
	#mat.cull_mode = BaseMaterial3D.CULL_DISABLED				# Sin cribado de caras (2D)
	#mat.vertex_color_use_as_albedo = true						# Difuminado de colores segun vertices
	#
	#mesh.surface_set_material(0, mat)
	
	return mesh

## -----------------------------------------------------------------------------
## 
## Función que devuelve los indices y los vertices de una malla de una rejilla
##	  
##	  n : refleja el numero de divisiones en el eje horizontal considerado
##	  m : refleja el numero de divisiones en el eje vertical considerado
##	  vertex : vertices de la malla
##    indexes : indices de la malla
##	  colors : colores de la malla
##    inferiorIzquierda : punto desde el que se genera todo
##	  longitudInferior : longitud horizontal completa de la malla
## 	  longitudIzquierda : longitud vertical completa de la malla
func CrearRejilla(n : int, m : int, eje : int, vertex : PackedVector3Array, indexes : PackedInt32Array, colors : PackedColorArray, inferiorIzquierda : Vector3 = Vector3(0,0,0), longitudInferior : float=1.0, longitudIzquierda : float=1.0):
	assert(eje == 0 or eje == 1 or eje == 2, "Eje erroneo")
	assert(longitudInferior > 0, "longitudInferior no puede ser 0")
	assert(longitudIzquierda > 0, "longitudIzquierda no puede ser 0")
	assert(n>0 and m>0, "No puedo crear una rejilla con una linea o un punto")
	
	var base_sep : float = longitudInferior/float(n)
	var altura_sep : float = longitudIzquierda/float(m)
	var vertex_c : PackedVector3Array = []
	var indexes_c : PackedInt32Array = []
	
	for i in range(n):
		for j in range(m):
			match eje:
				0:
					CrearCuadrilatero(inferiorIzquierda+Vector3(i*base_sep,j*altura_sep,0),altura_sep,base_sep,eje,vertex_c,indexes_c)
				1:
					CrearCuadrilatero(inferiorIzquierda + Vector3(i * base_sep, 0, j * altura_sep), base_sep, altura_sep, eje, vertex_c, indexes_c)
				2:
					CrearCuadrilatero(inferiorIzquierda+Vector3(0,i*base_sep,j*altura_sep),altura_sep,base_sep,eje,vertex_c,indexes_c)
			# Unimos con la mala global
			uneMallas(vertex,indexes,vertex_c,indexes_c)	
			
			
## -----------------------------------------------------------------------------
## 
## Función que devuelve los indices y los vertices de una malla de una planta de base cuadrada
##	  
##	  pto: punto inferior izquierdade la planta, todo se genera a traves de el
##	  base : longitud del lado de la planta 
##	  altura: altura de la planta
##    eje : representa el plano sobre el que se alza la planta (0,1,2) -> (z=0, y=0, x=0)
##	  cvertex : vertices de la malla
##    indexes : indices de la malla
func CrearPlanta(pto : Vector3, base : float, altura : float, eje : int, vertex : PackedVector3Array, indexes : PackedInt32Array):
	assert(eje == 0 or eje == 1 or eje == 2,"Eje erroneo")
	assert(altura != 0 and base != 0, "No puedo crear una planta sin base o sin altura")
	
	vertex.clear()
	indexes.clear()
	
	var vertex_c : PackedVector3Array = []
	var indexes_c : PackedInt32Array = []
	
	match eje:
		0:	# Apoyada sobre el plano z=0
			
			CrearCuadrilatero(pto,altura,base,eje+2,vertex,indexes)
			CrearCuadrilatero(pto+Vector3(0,base,0),base,altura,eje+1,vertex_c,indexes_c)
			uneMallas(vertex,indexes,vertex_c,indexes_c)
			CrearCuadrilatero(pto+Vector3(base,0,0),altura,base,eje+2,vertex_c,indexes_c)
			uneMallas(vertex,indexes,vertex_c,indexes_c)
			CrearCuadrilatero(pto,base,altura,eje+1,vertex_c,indexes_c)
			uneMallas(vertex,indexes,vertex_c,indexes_c)
			
		1:	#Apoyada sobre el plano y=0
			CrearCuadrilatero(pto,altura,base,eje-1,vertex,indexes)
			CrearCuadrilatero(pto+Vector3(base,0,0),base,altura,eje+1,vertex_c,indexes_c)
			uneMallas(vertex,indexes,vertex_c,indexes_c)
			CrearCuadrilatero(pto,base,altura,eje+1,vertex_c,indexes_c)
			uneMallas(vertex,indexes,vertex_c,indexes_c)
			CrearCuadrilatero(pto+Vector3(0,0,base),altura,base,eje-1,vertex_c,indexes_c)
			uneMallas(vertex,indexes,vertex_c,indexes_c)
		
		2: # Apoyada sobre el plano x=0
			
			CrearCuadrilatero(pto,altura,base,eje-1,vertex,indexes)
			CrearCuadrilatero(pto+Vector3(0,0,base),base,altura,eje-2,vertex_c,indexes_c)
			uneMallas(vertex,indexes,vertex_c,indexes_c)
			CrearCuadrilatero(pto,base,altura,eje-2,vertex_c,indexes_c)
			uneMallas(vertex,indexes,vertex_c,indexes_c)
			CrearCuadrilatero(pto+Vector3(0,base,0),altura,base,eje-1,vertex_c,indexes_c)
			uneMallas(vertex,indexes,vertex_c,indexes_c)

## -----------------------------------------------------------------------------
## 
## Función que devuelve la malla de un cono generado por revolucion
##	  
##	  perfil : vertices del perfil del cono
##	  n : numero de perfiles de revolucion a generar
##	  eje: entero que refleja el eje a usar (0,1,2)->(z=0,y=0,x=0)
## 	  trasl : Centro de l atapa inferior del cono -> representa la traslacion del cono
func GeneraCono(perfil : PackedVector2Array, n : int, eje : int, trasl : Vector3 = Vector3(0,0,0))->ArrayMesh:
	var vertex : PackedVector3Array = []
	var indexes : PackedInt32Array = []
	
	revoluciona(perfil,n,vertex,indexes,true,true,eje)
	
	var tablas : Array = []   ## tabla vacía incialmente
	tablas.resize( Mesh.ARRAY_MAX ) ## redimensionar al tamaño adecuado
	tablas[ Mesh.ARRAY_VERTEX ] = vertex
	tablas[ Mesh.ARRAY_INDEX  ] = indexes
	tablas[ Mesh.ARRAY_NORMAL ] = Utilidades.calcNormales(vertex, indexes)
		
	## crear e inicialzar el objeto 'mesh' de este nodo 
	var mesh = ArrayMesh.new() ## crea malla en modo diferido, vacía
	mesh.add_surface_from_arrays( Mesh.PRIMITIVE_TRIANGLES, tablas )
	
	## Con esta forma estamos creando la mesh con el material incluido
	#var mat := StandardMaterial3D.new() 
	#mat.albedo_color = Color(1,1,1)
	#mat.shading_mode = BaseMaterial3D.SHADING_MODE_UNSHADED		# Sin iluminacion
	#mat.vertex_color_use_as_albedo = true						# Difuminado de colores segun vertices
	#
	#mesh.surface_set_material(0, mat)
	
	return mesh

## -----------------------------------------------------------------------------
## 
## Función que devuelve el ArrayMesh de una rejilla
##	  
##	  n : refleja el numero de divisiones en el eje horizontal considerado
##	  m : refleja el numero de divisiones en el eje vertical considerado
##	  vertex : vertices de la malla
##    indexes : indices de la malla
##	  colors : colores de la malla
##    inferiorIzquierda : punto desde el que se genera todo
##	  longitudInferior : longitud horizontal completa de la malla
## 	  longitudIzquierda : longitud vertical completa de la malla
func ArrayMeshRejilla(n : int, m : int, eje : int, vertex : PackedVector3Array, indexes : PackedInt32Array, colors : PackedColorArray, inferiorIzquierda : Vector3 = Vector3(0,0,0), longitudInferior : float=1.0, longitudIzquierda : float=1.0)->ArrayMesh:
	
	CrearRejilla(n,m,eje,vertex,indexes,colors,inferiorIzquierda,longitudInferior,longitudIzquierda)
	
	for i in range(vertex.size()):
		colors.append(Color(vertex[i].x,vertex[i].y,vertex[i].z))
	
	var tablas : Array = []   ## tabla vacía incialmente
	tablas.resize( Mesh.ARRAY_MAX ) ## redimensionar al tamaño adecuado
	tablas[ Mesh.ARRAY_VERTEX ] = vertex
	tablas[ Mesh.ARRAY_INDEX  ] = indexes
	tablas[ Mesh.ARRAY_NORMAL ] = Utilidades.calcNormales(vertex, indexes)
	tablas[ Mesh.ARRAY_COLOR ] = colors
	
	## crear e inicialzar el objeto 'mesh' de este nodo 
	var mesh = ArrayMesh.new() ## crea malla en modo diferido, vacía
	mesh.add_surface_from_arrays( Mesh.PRIMITIVE_TRIANGLES, tablas )
	
	## COn esta fomra creamos la mesh con el material
	#var mat := StandardMaterial3D.new() 
	#mat.shading_mode = BaseMaterial3D.SHADING_MODE_UNSHADED		# Sin iluminacion
	#mat.cull_mode = BaseMaterial3D.CULL_DISABLED				# Sin cribado de caras (2D)
	#mat.vertex_color_use_as_albedo = true						# Difuminado de colores segun vertices
	#
	#mesh.surface_set_material(0, mat)
	#
	return mesh

## -----------------------------------------------------------------------------
## 
## Función que devuelve el ArrayMesh de un cubo de 24 vertices centrado en el (0,0,0) y lado 1
##	  
func CrearCubo24()->ArrayMesh:
	## crear las tablas de vértices y triángulos de un Donut 
	var vertices   := PackedVector3Array([])
	var triangulos := PackedInt32Array([])
	
	const D=1
	
	#Vertices de abajo
	
	# Adelante-Izquierda-Abajo (0)
	vertices.append(Vector3(-D, -D, D))  # 0: frontal
	vertices.append(Vector3(-D, -D, D))	 # 1: inferior
	vertices.append(Vector3(-D, -D, D))  # 2: izquierda
	
	# Adelante-Derecha-Abajo (1)
	vertices.append(Vector3( D, -D, D))  # 3: frontal
	vertices.append(Vector3( D, -D, D))  # 4: inferior
	vertices.append(Vector3( D, -D, D))  # 5: derecha
	
	# Atras-Derecha-Abajo (2)
	vertices.append(Vector3( D, -D,-D))  # 6: trasera
	vertices.append(Vector3( D, -D,-D))	 # 7: inferior
	vertices.append(Vector3( D, -D,-D))  # 8: derecha
	
	# Atras-Izquierda-Abajo (3)
	vertices.append(Vector3(-D, -D,-D))  # 9: trasera
	vertices.append(Vector3(-D, -D,-D))  # 10: inferior
	vertices.append(Vector3(-D, -D,-D))  # 11: izquierda
	
	# Vertices de arriba
	
	# Adelante-Izquierda-Arriba (4)
	vertices.append(Vector3(-D,  D, D))  # 12: frontal
	vertices.append(Vector3(-D,  D, D))	 # 13: superior
	vertices.append(Vector3(-D,  D, D))	 # 14: izquierda
	
	# Adelante-Derecha-Arriba (5)
	vertices.append(Vector3( D,  D, D))  # 15: frontal
	vertices.append(Vector3( D,  D, D))  # 16: superior
	vertices.append(Vector3( D,  D, D))  # 17*Transform3D().scaled(Vector3(1/1.2,1,1/1.2)): derecha 
	
	# Atras-Derecha-Arriba (6)
	vertices.append(Vector3( D,  D,-D))  # 18: trasera
	vertices.append(Vector3( D,  D,-D))	 # 19: superior
	vertices.append(Vector3( D,  D,-D))  # 20: derecha
	
	# Atras-Izquierda-Arriba (7)
	vertices.append(Vector3(-D,  D,-D))  # 21: trasera
	vertices.append(Vector3(-D,  D,-D))  # 22: superior
	vertices.append(Vector3(-D,  D,-D))  # 23: izquierda
	
	#Cara frontal
	triangulos.append_array([0,15,3,0,12,15])
	
	#Cara derecha
	triangulos.append_array([5,20,8,5,17,20])
	
	#Cara trasera
	triangulos.append_array([6,21,9,6,18,21])
	
	#Cara izquierda
	triangulos.append_array([11,14,2,11,23,14])
	
	#Cara superior
	triangulos.append_array([16,22,19,16,13,22])
	
	#Cara inferior
	triangulos.append_array([10,1,4,10,4,7])	
		
	var normales := Utilidades.calcNormales( vertices, triangulos )
	
	## inicializar el array con las tablas
	var tablas : Array = []   ## tabla vacía incialmente
	tablas.resize( Mesh.ARRAY_MAX ) ## redimensionar al tamaño adecuado
	tablas[ Mesh.ARRAY_VERTEX ] = vertices
	tablas[ Mesh.ARRAY_INDEX  ] = triangulos
	tablas[ Mesh.ARRAY_NORMAL ] = normales
	
	## crear e inicialzar el objeto 'mesh' de este nodo 
	var mesh = ArrayMesh.new() ## crea malla en modo diferido, vacía
	mesh.add_surface_from_arrays( Mesh.PRIMITIVE_TRIANGLES, tablas )
	
	return mesh

## -----------------------------------------------------------------------------
## 
## Función que devuelve el ArrayMesh de una rejilla
##	  
##	  perfil : vertices del perfil de la figura
##	  n : numero de copias del perfil que tendra la figura, contando la de partida
##	  vertex : array de vertices resultante
## 	  indexes : array de indices de los triangulos de la malla resultante
##	  tapa_sup : bool que representa si se crea la tapa superior o no
##	  tapa_inf : bool que representa si se crea la tapa inferior o no
## 	  eje : entero que representa el eje de rotacion (0,1,2) -> (eje y, eje z, eje x)
##    trasl :  traslacion que se le hace a la figura resultante
# Esta funcion asume que los vertices vienen ordenados segun la altura,
# en otro caso no se contempla su funcionamiento.
# El algoritmo esta creado para que la snormales queden hacia fuera si el perfil esta dado de arriba a abajo.
func revoluciona(perfil : PackedVector2Array, n : int , vertex : PackedVector3Array, indexes : PackedInt32Array, tapa_sup : bool, tapa_inf : bool, eje : int, trasl : Vector3 = Vector3(0,0,0)):
	if vertex.size()!=0:
		vertex.clear()
	if indexes.size()!=0:
		indexes.clear()
	
	assert(0<=eje and eje<=2, "Parametro de eje de rotacion mal dicho")
	
	
	if n>1 and perfil.size()>0:
		# Creamos los vertices
		match eje: 
			0:
				# El perfil se encuentra en el plano z-x luego tenemos que introducir los vertices 
				# de izquierda a derecha.
				# y -> x
				# z -> y
				# x -> z
				
				for i in range(perfil.size()):
					for j in range(n):
						vertex.append(Vector3(perfil[i].y,perfil[i].x*sin(2*PI*j/n), perfil[i].x*cos(2*PI*j/n)))
				
				vertex.append(Vector3(perfil[0].y,0,0))
				vertex.append(Vector3(perfil[perfil.size()-1].y,0,0))
				
			1:
				# El perfil esta en el plano x-y
				# Se supone que estamos creando los vertices por capas segun el perfil
				# de abajo a arriba o de arriba abajo
				# De esta manera tenemos que cada n casillas tenemos un vertices, correspondidos 
				# por la coordenada z
				# Los triangulos seran de la forma z->z+1->z+1(y+1) y z->z+1(y+1)->z(y+1)
				for i in range(perfil.size()):
					for j in range(n):
						vertex.append(Vector3(perfil[i].x*cos(2*PI*j/n), perfil[i].y,perfil[i].x*sin(2*PI*j/n)))
			
				vertex.append(Vector3(0,perfil[0].y,0))
				vertex.append(Vector3(0,perfil[perfil.size()-1].y,0))
			2: 
				# Ahora rotamos sobre el eje z, luego trabajamos en el plano y-z como perfil
				# E introducimos los vertices de atras adelante
				# x -> y
				# y -> z
				# z -> x
	
				for i in range(perfil.size()):
					for j in range(n):
						vertex.append(Vector3(perfil[i].x*sin(2*PI*j/n),perfil[i].x*cos(2*PI*j/n), perfil[i].y))
				
				vertex.append(Vector3(0,0,perfil[0].y))
				vertex.append(Vector3(0,0,perfil[perfil.size()-1].y))
		
		
		# Traladamos los vertices
		
		for j in range(vertex.size()):
			vertex[j] = vertex[j]+trasl
			
		# Asignamos los indices 

		for i in range(perfil.size()-1):
			# Añadimos una capa
			for j in range(n):
				# Añadimos el primer triangulo
				indexes.append(n*i+(j%n))		#z
				indexes.append(n*(i+1)+(j+1)%n)	#z+1(y+1)
				indexes.append(n*i+(j+1)%n)		#z+1
				
				
				# Añadimos el segundo triangulo
				indexes.append(n*i+j%n)		#z
				indexes.append(n*(i+1)+j%n)	#z(y+1)
				indexes.append(n*(i+1)+(j+1)%n)	#z+1(y+1)
				
			
		# Añadimos la capa de abajo
		if tapa_inf:
			for j in range(n):
				indexes.append(j%n)
				indexes.append((j+1)%n)
				indexes.append(vertex.size()-2)	# Es el centro de la parte de abajo o arriba dependeidno del orden
			
			
		# Añadimos la capa de arriba
		if tapa_sup:
			for j in range(n):
				indexes.append(n*(perfil.size()-1)+j%n)
				indexes.append(vertex.size()-1)
				indexes.append(n*(perfil.size()-1)+(j+1)%n)

## -----------------------------------------------------------------------------
## 
## Función que devuelve un arraymesh de un plano centrado en (0,0,0) 
## y lado 2*D con sus coordenadas de textura
##
## D : entero que refleja la mitad del lado del plano
func ArrayMeshPlanoUV(D : int) -> ArrayMesh:
	var vertex := PackedVector3Array([
		Vector3(-D, -D, 0),  # 0: esquina inferior-izq
		Vector3( D, -D, 0),  # 1: inferior-der
		Vector3( D,  D, 0),  # 2: superior-der  
		Vector3(-D,  D, 0)   # 3: superior-izq	
	])
	var indexes := PackedInt32Array([0,1,2, 0,2,3])
	
	# UVs para textura completa: (0,0) -> (1,1)
	var uvs := PackedVector2Array([
		Vector2(0,1),  # inferior-izq
		Vector2(1,1),  # inferior-der
		Vector2(1,0),  # superior-der
		Vector2(0,0)   # superior-izq
	])
	
	var normales := Utilidades.calcNormales(vertex, indexes)
	
	var tablas : Array = []
	tablas.resize(Mesh.ARRAY_MAX)
	tablas[Mesh.ARRAY_VERTEX] = vertex
	tablas[Mesh.ARRAY_INDEX]  = indexes
	tablas[Mesh.ARRAY_NORMAL] = normales
	tablas[Mesh.ARRAY_TEX_UV] = uvs 
	
	var mesh = ArrayMesh.new()
	mesh.add_surface_from_arrays(Mesh.PRIMITIVE_TRIANGLES, tablas)
	return mesh
	
## -----------------------------------------------------------------------------
## 
## Función que devuelve un arraymesh de un cubo de 24 vertices centrado en (0,0,0) 
## y lado 2*D con sus coordenadas de textura
##
## D : mitad del lado del cubo
func ArrayMeshCubo24_CCT(D : int) -> ArrayMesh:
	var vertex := PackedVector3Array([
		# Cara frontal  (Z = +D)
		Vector3(-D,-D, D), # 0  inf-izq
		Vector3( D,-D, D), # 1  inf-der
		Vector3( D, D, D), # 2  sup-der
		Vector3(-D, D, D), # 3  sup-izq

		# Cara trasera  (Z = -D)
		Vector3( D,-D,-D), # 4  inf-izq (vista desde atrás)
		Vector3(-D,-D,-D), # 5  inf-der
		Vector3(-D, D,-D), # 6  sup-der
		Vector3( D, D,-D), # 7  sup-izq

		# Cara derecha  (X = +D)
		Vector3( D,-D, D), # 8  inf-izq
		Vector3( D,-D,-D), # 9  inf-der
		Vector3( D, D,-D), #10  sup-der
		Vector3( D, D, D), #11  sup-izq

		# Cara izquierda (X = -D)
		Vector3(-D,-D,-D), #12  inf-izq
		Vector3(-D,-D, D), #13  inf-der
		Vector3(-D, D, D), #14  sup-der
		Vector3(-D, D,-D), #15  sup-izq

		# Cara superior (Y = +D)
		Vector3(-D, D, D), #16  inf-izq
		Vector3( D, D, D), #17  inf-der
		Vector3( D, D,-D), #18  sup-der
		Vector3(-D, D,-D), #19  sup-izq

		# Cara inferior (Y = -D)
		Vector3(-D,-D,-D), #20  inf-izq
		Vector3( D,-D,-D), #21  inf-der
		Vector3( D,-D, D), #22  sup-der
		Vector3(-D,-D, D)  #23  sup-izq
	])
	
	var indexes := PackedInt32Array([
		# Frontal  (0‑3)
		0,2,1,  0,3,2,
		# Trasera (4‑7) ojo al orden para que la normal salga hacia fuera
		4,6,5,  4,7,6,
		# Derecha (8‑11)
		8,10,9, 8,11,10,
		# Izquierda (12‑15)
		12,14,13, 12,15,14,
		# Superior (16‑19)
		16,18,17, 16,19,18,
		# Inferior (20‑23)
		20,22,21, 20,23,22
	])
	
	# Calculo de normales
	var normales := Utilidades.calcNormales(vertex, indexes)
	
	# Coordenadas UV: Mismas por cada plano (cara)
	var uvs := PackedVector2Array([])
	
	## Patrón UV por cara: 
	# Hay que tener en cuenta que en las imagenes el vertice (0,0) es el de la esquina superior-izquierda
	var uv_cara := PackedVector2Array([
		Vector2(0,1),  # inferior-izquierda
		Vector2(1,1),  # inferior-derecha  
		Vector2(1,0),  # superior-derecha
		Vector2(0,0)   # superior-izquierda
	])
	
	# Repetir 6 veces (una por cada cara)
	for i in range(6):
		uvs.append_array(uv_cara)
	
	# Construir tablas de la malla
	var tablas : Array = []
	tablas.resize(Mesh.ARRAY_MAX)
	tablas[Mesh.ARRAY_VERTEX]   = vertex
	tablas[Mesh.ARRAY_INDEX]    = indexes
	tablas[Mesh.ARRAY_NORMAL]   = normales
	tablas[Mesh.ARRAY_TEX_UV]   = uvs  # ← ¡ACTIVA LAS TEXTURAS!
	
	# Crear y retornar el ArrayMesh
	var mesh = ArrayMesh.new()
	mesh.add_surface_from_arrays(Mesh.PRIMITIVE_TRIANGLES, tablas)
	
	return mesh

## -----------------------------------------------------------------------------
## 
## Función que devuelve un arraymesh de una piramide centrada con base en (0,0,0)
## de lado 2*D y altura 2*D con sus coordenadas de textura
##
## D : mitad de lado de la base y altura
func ArrayMeshPiramideUV(D : int) -> ArrayMesh:
	var vertex := PackedVector3Array([
		# Cara frontal  (Z = +D)
		Vector3(-D,0, D), # 0  inf-izq
		Vector3(D,0, D), # 1  inf-der
		Vector3( 0,2*D, 0), # 2  sup

		# Cara trasera  (Z = -D)
		Vector3( -D,0,-D), # 3  inf-izq (vista desde atrás)
		Vector3(D,0,-D), # 4  inf-der
		Vector3( 0,2*D, 0), # 5  sup

		# Cara derecha  (X = +D)
		Vector3( D,0, D), # 6  inf-izq
		Vector3( D,0,-D), # 7  inf-der
		Vector3( 0,2*D, 0), # 8  sup

		# Cara izquierda (X = -D)
		Vector3(-D,0,-D), #9  inf-izq
		Vector3(-D,0, D), #10  inf-der
		Vector3( 0,2*D, 0), #11  sup

		# Cara inferior (Y = 0)
		Vector3(-D, 0, D), #12  delantero-izq
		Vector3( D, 0, D), #13  delantero-der
		Vector3( D, 0,-D), #14  trasero-der
		Vector3(-D, 0,-D), #15  trasero-izq
	])
	var indexes := PackedInt32Array([
		# Frontal  
		0,2,1,
		# Trasera 
		3,4,5,
		# Derecha 
		6,8,7,
		# Izquierda 
		9,11,10,
		# inferior
		15,13,14, 15,12,13
	])
	
	# Calculo de normales
	var normales := Utilidades.calcNormales(vertex, indexes)
	
	# Coordenadas UV: 
	var uvs := PackedVector2Array([])
	## Patrón UV por cara: 
	# Hay que tener en cuenta que en las imagenes el vertice (0,0) es el de la esquina superior-izquierda
	var uv_cara := PackedVector2Array([
		Vector2(0,1),  # inferior-izquierda
		Vector2(1,1),  # inferior-derecha  
		Vector2(0.5,0) # apice
	])
	var uv_base := PackedVector2Array([
		Vector2(0,1),  # inferior-izquierda
		Vector2(1,1),  # inferior-derecha  
		Vector2(1,0),  # superior-derecha
		Vector2(0,0)   # superior-izquierda
	])
	# Repetir 6 veces (una por cada cara)
	for i in range(4):
		uvs.append_array(uv_cara)
	uvs.append_array(uv_base)
	var tablas : Array = []
	tablas.resize(Mesh.ARRAY_MAX)
	tablas[Mesh.ARRAY_VERTEX]   = vertex
	tablas[Mesh.ARRAY_INDEX]    = indexes
	tablas[Mesh.ARRAY_NORMAL]   = normales
	tablas[Mesh.ARRAY_TEX_UV]   = uvs  # ← ¡ACTIVA LAS TEXTURAS!
	
	# Crear y retornar el ArrayMesh
	var mesh = ArrayMesh.new()
	mesh.add_surface_from_arrays(Mesh.PRIMITIVE_TRIANGLES, tablas)
	
	return mesh

## -----------------------------------------------------------------------------
##Genera un disco plano en el eje XZ. Basta hacerlo en un eje pues el resto son rotaciones o traslaciones
## n : divisiones angulares
## m : divisiones radiales
## r_max : radio máximo del disco
## uv_tipo = 0 -> (u, v) = (ángulo, radio)
## uv_tipo = 1 -> (u, v) = lineal en (x,z)
func ArrayMeshDiscoUV(n: int, m: int, r_max: float, uv_tipo:int = 0, centro :=Vector3(0,0,0)) -> ArrayMesh:
	assert(n > 0 and m > 0)

	var vertex  := PackedVector3Array()
	var indexes := PackedInt32Array()

	## Construimos los vertices
	for j in range(m + 1):              # anillos 0..m
		var r = r_max * float(j) / float(m)
		for i in range(n):         # Duplicamos el 0 para cerrar 
			var ang = 2*PI * float(i) / float(n)
			var x = r * cos(ang)
			var z = r * sin(ang)
			vertex.append(Vector3(x, 0.0, z))

	## Generamos los indices
	# cada celda (j,i) forma 2 triángulos
	# idx(j,i) = j*(n+1) + i
	for j in range(m):
		for i in range(n):
			var ind0 = j*n + i
			var ind1 = j*n + ((i + 1) % n)         
			var ind2 = (j + 1)*n + i
			var ind3 = (j + 1)*n + ((i + 1) % n)

			# Triángulo 1
			indexes.append(ind0)
			indexes.append(ind3)
			indexes.append(ind1)
			# Triángulo 2
			indexes.append(ind0)
			indexes.append(ind2)
			indexes.append(ind3)

	var normales := Utilidades.calcNormales(vertex, indexes)

	var uvs := PackedVector2Array()

	if uv_tipo == 0:
		# (u, v) proporcional a ángulo y radio
		for a in vertex:
			var dx = a.x - centro.x		# distancias de la suma al centro
			var dz = a.z - centro.z
			var r = sqrt(dx*dx + dz*dz) # distancia euclidea
			var ang = atan2(dz, dx) + PI             # [-PI, PI]
			var u = ang/ (2.0 * PI)      # 0..1	(angulo normalizado)
			var v = r / r_max                   # 0..1 (proporcion desde el centro)
			if u > 0.999:
				u = 0.0

			uvs.append(Vector2(u, v))
	else:
		# (u, v) lineales en (x,z)  -> proyección plana
		for a in vertex:
			var dx = a.x / r_max                 # -1..1
			var dz = a.z / r_max                 # -1..1
			var u = 0.5 * (dx + 1.0)             # 0..1
			var v = 0.5 * (dz + 1.0)            # 0..1
			uvs.append(Vector2(u, v))

	var tablas : Array = []
	tablas.resize(Mesh.ARRAY_MAX)
	tablas[Mesh.ARRAY_VERTEX]   = vertex
	tablas[Mesh.ARRAY_INDEX]    = indexes
	tablas[Mesh.ARRAY_NORMAL]   = normales
	tablas[Mesh.ARRAY_TEX_UV]   = uvs

	var mesh := ArrayMesh.new()
	mesh.add_surface_from_arrays(Mesh.PRIMITIVE_TRIANGLES, tablas)
	return mesh
