extends Node3D

# Tal y como lo hemos pensado, los limites que estamos pensando es sobre el brazo, es decir,
# como el brazo esta rozado, el eje y que pensamos es realmente el eje z en el marco del brazo.
# Y asi sucesivamente. De esta forma, high_limit es realmente low_limit pensando en el marcho del gancho
# y low_limit es realmente high_limit pensando en el marco del gancho.
# Es una forma RARA de hacerlo, pero creo que me ayuda mucho a entender lo que estoy haciendo

# Variables movimiento horizontal
@export var horizontal_speed := 0.2
@export var left_limit := 0.64
@export var right_limit := -0.2
var active_tras_l := false
var active_tras_r := false

# Variables movimiento vertical
@export var vertical_speed := 0.4
@export var high_limit := 1.0
@export var low_limit := 0.3
var active_high := false
var active_low := false

#? DUDA: como hago lo de la homotecia, lo dejo por hoy porque el grueso de la practica, es decir, lo que me 
# piden esta hecho
var homothety:= false
@export var stretch_speed = 0.1
@export var stretch_min_limit = 0.2
@export var stretch_max_limit = 1.0
var active_high_h := false
var active_low_h := false

func _process(delta: float) -> void:
	
	var vertical_movement := 0.0
	var horizontal_movement := 0.0
	var stretch_change := 0.0
	
	# Gestion de riel
	# Si se pulsa "3" desplazamos hacia alante
	if Input.is_action_just_pressed("AvanzarGancho") and !active_tras_r:
		active_tras_l = !active_tras_l
	if active_tras_l:
		horizontal_movement = (right_limit - position.y)*delta*horizontal_speed
		
	
	# Si se pulsa "4" desplazamos hacia atras
	if Input.is_action_just_pressed("Retrocedergancho") and !active_tras_l:
		active_tras_r = !active_tras_r
	if active_tras_r:
		horizontal_movement = (left_limit - position.y)*delta*horizontal_speed
	
	if !homothety:
		
		# Gestion de altura
		# Si se pulsa "5" subimos
		if Input.is_action_just_pressed("SubirGancho") and !active_low:
			active_high = !active_high
		if active_high:
			vertical_movement = (low_limit - position.z)*delta*vertical_speed
			
		
		# Si se pulsa "6" bajamos
		if Input.is_action_just_pressed("BajarGancho") and !active_high:
			active_low = !active_low
		if active_low:
			vertical_movement = (high_limit - position.z)*delta*vertical_speed
			
	else: 
		# Gestion de altura
		# Si se pulsa "5" subimos
		if Input.is_action_just_pressed("SubirGancho"):
			active_high_h = !active_high_h
		if active_high_h:
			stretch_change =- delta*stretch_speed
			
		
		# Si se pulsa "6" bajamos
		if Input.is_action_just_pressed("BajarGancho"):
			active_low_h = !active_low_h
		if active_low_h:
			stretch_change = delta*stretch_speed
	
	# Actualizamos las posiciones.
	
	position.y += horizontal_movement
	if homothety:
		scale.y += stretch_change
		scale.y=clamp(scale.y,stretch_min_limit,stretch_max_limit)
	else:
		position.z += vertical_movement
	
	
	
