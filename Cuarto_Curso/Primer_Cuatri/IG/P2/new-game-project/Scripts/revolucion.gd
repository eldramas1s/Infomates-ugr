extends Node

# Esta funcion asume que los vertices vienen ordenados segun la altura,
# en otro caso no se contempla su funcionamiento.
# n es el numero de veces que quiero que este el perfil, no el numero de duplicaciones
func revoluciona(perfil : PackedVector2Array, n : int , vertex : PackedVector3Array, indexes : PackedInt32Array):
	if vertex.size()!=0:
		vertex.clear()
	if indexes.size()!=0:
		indexes.clear()
	
	if n>1 and perfil.size()>0:
		
		
		# Creamos los vertices
		# Se supone que estamos creando los vertices por capas segun el perfil
		# de abajo a arriba o de arriba abajo
		# De esta manera tenemos que cada n casillas tenemos un vertices, correspondidos 
		# por la coordenada z
		# Los triangulos seran de la forma z->z+1->z+1(y+1) y z->z+1(y+1)->z(y+1)
		for i in range(perfil.size()):
			for j in range(n):
				vertex.append(Vector3(perfil[i].x*cos(2*PI*j/n), perfil[i].y,perfil[i].x*sin(2*PI*j/n)))
					
		# Duda: ¿en un perfil que no tome un punto en la recta y=x=0 tengo que añadir centros para 
		# obtener los poligonos regulares de la capa superior e inferior?
		
		# Asignamos los indices 
		# !Falta por ver las capas superior e inferior! 
		
		vertex.append(Vector3(0,perfil[0].y,0))
		vertex.append(Vector3(0,perfil[perfil.size()-1].y,0))

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
		for j in range(n):
			indexes.append(j%n)
			indexes.append((j+1)%n)
			indexes.append(perfil.size()-2)	# Es el centro de la parte de abajo o arriba dependeidno del orden
			
			
		# Añadimos la capa de arriba
		
		for j in range(n):
			indexes.append(n*(perfil.size()-1)+j%n)
			indexes.append(n*(perfil.size()-1))
			indexes.append(n*(perfil.size()-1)+(j+1)%n)
			
			
	
