## Nombre: Lucas, Apellidos: Hidalgo Herrera, Titulación: GIM
## email: lucashidalgo@correo.ugr.es, DNI o pasaporte: 26512990Q
extends Node3D

@export var escena : int = 2 # 1 para practicas 2 para ejercicio adicional
## Ver: 
## https://docs.godotengine.org/en/4.4/classes/class_viewport.html#enum-viewport-debugdraw

var dibujar_aristas : bool = false 


func _init():
	print("Para elegir si se toma la camara de la escena de practicas o de la escena del ejericio adicional, debe modificar a su gusto el atributo escena del script del nodo mundo")
	RenderingServer.set_debug_generate_wireframes(true)

func _unhandled_key_input( key_event ):
	if key_event.keycode == KEY_W and not key_event.pressed :
		dibujar_aristas = not dibujar_aristas
		var viewport = get_viewport()
		if dibujar_aristas:
			viewport.debug_draw = Viewport.DEBUG_DRAW_WIREFRAME
			print("Dibujar en modo aristas: activado")
		else:
			viewport.debug_draw = Viewport.DEBUG_DRAW_DISABLED
			print("Dibujar en modo aristas: desactivado")
