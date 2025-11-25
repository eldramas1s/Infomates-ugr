## Nombre: Lucas, Apellidos: Hidalgo Herrera, Titulación: GIM
## email: lucashidalgo@correo.ugr.es, DNI o pasaporte: 26512990Q
extends Node3D

@export var rotation_speed := 10.0 # solo un radian por segundo
var activa_drcha := false
var activa_izquierda := false


# Funcion para rotar en el tiempo al pilar

func _process(delta: float) -> void:
	
	# Si se pulsa "1" rotamos a derecha
	if Input.is_action_just_pressed("Rotarderecha") and !activa_izquierda:
		activa_drcha = !activa_drcha
	if activa_drcha:
		rotation.y += deg_to_rad(rotation_speed * delta)
	
	# Si se pulsa "2" rotamos a izquierda
	if Input.is_action_just_pressed("RotarIzquierda") and !activa_drcha:
		activa_izquierda = !activa_izquierda
	if activa_izquierda:
		rotation.y += deg_to_rad(-rotation_speed * delta)
