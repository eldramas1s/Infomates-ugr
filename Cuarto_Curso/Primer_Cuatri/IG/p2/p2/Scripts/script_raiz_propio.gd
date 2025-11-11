## Nombre: Lucas, Apellidos: Hidalgo Herrera, Titulación: GIM
## email: lucashidalgo@correo.ugr.es, DNI o pasaporte: 26512990Q
extends Node3D

var dibujar_aristas : bool = false

func _init():
	RenderingServer.set_debug_generate_wireframes(true)
	
func _unhandled_key_input(key_event):
	if key_event.keycode == KEY_W and not key_event.pressed :
		dibujar_aristas = not dibujar_aristas
		var viewport = get_viewport()
		
		if dibujar_aristas:
			viewport.debug_draw = Viewport.DEBUG_DRAW_WIREFRAME
			print("Dibujar en modo aristas: activado")
		else:
			viewport.debug_draw = Viewport.DEBUG_DRAW_DISABLED
			print("Dibujar en modo aristas: desactivado")
			
