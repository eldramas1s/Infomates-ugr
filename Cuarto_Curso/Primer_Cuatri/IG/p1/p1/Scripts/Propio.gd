## Nombre: Lucas, Apellidos: Hidalgo Herrera, Titulación: GIM
## email: lucashidalgo@correo.ugr.es, DNI o pasaporte: 26512990Q
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
