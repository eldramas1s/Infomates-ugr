## Nombre: Lucas, Apellidos: Hidalgo Herrera, Titulación: GIM
## email: lucashidalgo@correo.ugr.es, DNI o pasaporte: 26512990Q
extends Camera3D

## VARIABLES GLOBALES
var selected_figure = null	## determina la figura que hay seleccionada
var material_original: Material = null ## guarda el material que tenia antes al esfera

## ----------------------------------------------------------------------
## contantes y variables de instancia 

const at   := 2.5   ## ángulo de rot. con teclas (en grados x pulsación)
const ar   := 0.5   ## ángulo de rot. con ratón (en grados x pixel)
var   bdrp := false ## botón derecho del ratón presionado sí/no
var   dz   := 3.0   ## distancia en Z de la cámara al origen
var   dxy  := Vector2( 0.0, 0.0 ) ## ángulos hor. y vert. (en grados)

## -------------------------------------------------------------------
## actualiza la variable 'transform' de este nodo cámara

func _actualiza_transf_vista(  ) -> void : 
	var ahr  := ((45.0+float(dxy.x))*2.0*PI)/360.0 ## ang.horiz.radi.
	var avr  := ((30.0+float(dxy.y))*2.0*PI)/360.0 ## ang.vert.radi.
	var tras := Transform3D().translated( Vector3( 0.0, 0.0, dz))	
	var rotx := Transform3D().rotated( Vector3.RIGHT, -avr )
	var roty := Transform3D().rotated( Vector3.UP, ahr ) 
	transform = roty*rotx*tras   ## actualiza transform del nodo cámara

## -------------------------------------------------------------------
func _ready() -> void :  ## se ejecuta una vez al inicio
	_actualiza_transf_vista() ## inicializa la vista al inicio

func _input( event ):
	if self.get_parent().get_parent().escena!=1:
		if (event is InputEventMouseButton and event.pressed and event.button_index == MOUSE_BUTTON_LEFT):
			## 1. Buscar nodo de la camara
			var cam : Node =self
			assert( cam != null, "No se encuentra el nodo CameraAdicional")
			
			## 2. Construir objetos con parametros de interseccion
			var query := PhysicsRayQueryParameters3D.new()
			query.collision_mask = 0xFFFFFFFF # todas las caras
			query.from = cam.project_ray_origin(event.position)
			query.to = query.from+100*cam.project_ray_normal(event.position)
			
			## 3. Calcular las intersecciones
			var space_state = get_world_3d().direct_space_state
			var result = space_state.intersect_ray(query)
			
			## 4. Procesar el resultado
			
			if result:
				# Conseguimos la esfera seleccionada
				var sphere : Node = result.collider.get_parent()
				#var dad_scene = sphere.get_parent()
				var scene = self.get_parent()
	
				## Cambiamos el color
				
				# Guardo la esfera seleccionada
				selected_figure = sphere
				material_original = sphere.material_override
			
				# Creamos el material
				var material_red = StandardMaterial3D.new()
				material_red.albedo_color = Color.RED
				material_red.roughness = material_original.roughness 
				material_red.metallic = material_original.metallic
				
				# Asignamos el material
				selected_figure.material_override = material_red
				
				## Imprimimos que esfera se ha seleccionado
				# Obtenemos las variables globales que necesitamos
				var m = scene.m
				var index = scene.get_index()
				
				# Obtenemos el radio y la posicion en el radio
				var pos_rad = index%m +1
				var rad = index/m +1	
				# Imprimimos la esfera que ha colisionado
				print("Se ha seleccionado la esfera ", rad, ",",pos_rad)
			else:
				print("NO hay objeto en el pixel seleccionado")
		if(event is InputEventMouseButton and not event.pressed and event.button_index == MOUSE_BUTTON_LEFT):
			if selected_figure != null:
				selected_figure.material_override = material_original
				
				#Limpiamos las variables
				selected_figure = null
				material_original = null
				
		if(event is InputEventMouseMotion and selected_figure):
			var move = Vector3(0, -event.relative.y*0.005, 0)
			selected_figure.position += move
		
		var av : bool = true ## actualizar vista sí/no
		
		if event is InputEventKey and event.pressed: ## teclas
			match event.keycode:
				KEY_UP:    
					dxy += Vector2( 0, -at )
				KEY_DOWN:  
					dxy += Vector2( 0, +at )
				KEY_RIGHT: 
					dxy += Vector2( -at, 0 )
				KEY_LEFT:
					dxy += Vector2( at, 0 )
				KEY_MINUS, KEY_PAGEDOWN, KEY_KP_SUBTRACT: 
					dz *= 1.05 
				KEY_PLUS, KEY_PAGEUP, KEY_KP_ADD: 
					dz = max( dz/1.05, 0.1 )
				_: 
					av = false
					
		elif event is InputEventMouseButton: ## botón ratón o rueda
			match event.button_index:
				MOUSE_BUTTON_RIGHT: 
					bdrp = event.pressed 
					av = false 
				MOUSE_BUTTON_WHEEL_DOWN: 
					dz *= 1.05
				MOUSE_BUTTON_WHEEL_UP:   
					dz = max( dz/1.05, 0.1 )
				_: 
					av = false
					
		elif event is InputEventMouseMotion and bdrp: ## movim. ratón
			dxy += ar * Vector2( -event.relative.x, event.relative.y ) 
			
		else: ## otros tipos de eventos (no hace nada)
			av = false ## (no actualizar transf)

		if av:
			_actualiza_transf_vista( )
	
	
## ---------------------------------------------- ##
## Funcion que selecciona la figura pasada como argumento
##	figure : figura pasada como argumento

func select_figure(figure):
	# Seleccionar nuevo
	selected_figure = figure
	if selected_figure:
		print("Seleccionado: ", selected_figure.name)

## ---------------------------------------------- ##
## Funcion que selecciona el area de la mesh instance pasada como argumento
##	name : nombre de la mesh instance
@warning_ignore("shadowed_variable_base_class")
func select_figure_by_name(name):
	var root =get_tree().current_scene
	var node = root.find_child(name, true, false)
	if node:
		select_figure(node)
	else:
		print("ERROR: No se encontro figura: ", name)

	
## ---------------------------------------------- ##
## Funcion que selecciona el area de la mesh instance clicada con el raton
##	name : nombre de la mesh instance
func select_figure_at_mouse(from, to):
	print("=== RAYCAST DEBUG ===")
	print("From: ", from)
	print("To: ", to)
	
	#ray.global_position = from
	#ray.look_at(to)
	#ray.target_position = Vector3(0, 0, -1000)
	#ray.force_raycast_update()
	#
	#print("Ray enabled: ", ray.enabled)
	#print("Ray colliding: ", ray.is_colliding())
	#
	#if ray.is_colliding():
		#var figura = ray.get_collider().get_parent()
		#select_figure(figura)
	#else:
		#print("NO HAY COLISION")
