extends Camera3D

## VARIABLES GLOBALES
var selected_figure = null	## determina la figura que hay seleccionada
var figures :Array[String]= ["Plano","Cilindro","Cubo"] ## mallas que podemos seleccionar
var current_figure_index = 0 ## Indices de la figura seleccionada

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
	make_current()
	_actualiza_transf_vista() ## inicializa la vista al inicio
		
@onready var ray = $RayCast3D # == nodo `RayCast3D` hijo de la camara

func _input( event ):
	if current:
		var mouse_pos = get_viewport().get_mouse_position()
		var from = project_ray_origin( mouse_pos )
		var to = from + project_ray_normal( mouse_pos ) * 1000.0
		if event is InputEventMouseButton and event.pressed \
				and event.button_index == MOUSE_BUTTON_LEFT:
			select_figure_at_mouse(from,to)
			
		if event is InputEventMouseMotion and selected_figure:
			var move = Vector3((event.relative.x * 0.01), 0, (event.relative.y * 0.01))
			selected_figure.position += move
			selected_figure.position.x = clamp(selected_figure.position.x, -10.0, 10.0)
			selected_figure.position.z = clamp(selected_figure.position.z, -10.0, 10.0)
		
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
		
func _unhandled_key_input(key_event):
	# Cambiar parte con flechas
	if key_event.keycode == KEY_UP and not key_event.pressed:
		current_figure_index = (current_figure_index + 1) % figures.size()
		select_figure_by_name(figures[current_figure_index])
		print("Parte: ", figures[current_figure_index])
	
	if key_event.keycode == KEY_DOWN and not key_event.pressed:
		current_figure_index = (current_figure_index - 1 + figures.size()) % figures.size()
		select_figure_by_name(figures[current_figure_index])
		print("Parte: ", figures[current_figure_index])

func crear_cubo_en( pos ):
	var nuevo_cubo = MeshInstance3D.new()
	nuevo_cubo.mesh = BoxMesh.new()
	# Elevarlo para que no atraviese el suelo
	nuevo_cubo.position = pos + Vector3.UP * 0.5
	var mat = StandardMaterial3D.new()
	mat.albedo_color = Color(randf(), randf(), randf())
	nuevo_cubo.material_override = mat
	get_tree().get_current_scene().add_child(nuevo_cubo)
	
	
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
	
	ray.global_position = from
	ray.look_at(to)
	ray.target_position = Vector3(0, 0, -1000)
	ray.force_raycast_update()
	
	print("Ray enabled: ", ray.enabled)
	print("Ray colliding: ", ray.is_colliding())
	
	if ray.is_colliding():
		var figura = ray.get_collider().get_parent()
		select_figure(figura)
	else:
		print("NO HAY COLISION")
