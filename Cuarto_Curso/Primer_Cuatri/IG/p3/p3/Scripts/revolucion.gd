## Nombre: Lucas, Apellidos: Hidalgo Herrera, Titulación: GIM
## email: lucashidalgo@correo.ugr.es, DNI o pasaporte: 26512990Q
extends Node

# Esta funcion asume que los vertices vienen ordenados segun la altura,
# en otro caso no se contempla su funcionamiento.
# n es el numero de veces que quiero que este el perfil, no el numero de duplicaciones
# eje:
#		0 -> eje x
#		1 -> eje y
#		2 -> eje z
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
				indexes.append(perfil.size()-2)	# Es el centro de la parte de abajo o arriba dependeidno del orden
			
			
		# Añadimos la capa de arriba
		if tapa_sup:
			for j in range(n):
				indexes.append(n*(perfil.size()-1)+j%n)
				indexes.append(n*(perfil.size()-1))
				indexes.append(n*(perfil.size()-1)+(j+1)%n)
			
			
	
