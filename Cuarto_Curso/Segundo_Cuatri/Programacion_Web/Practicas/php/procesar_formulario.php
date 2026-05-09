<?php

class Usuario
{
    private $nombre;
    private $apellido;
    private $password;
    private $gender;
    private $ageRange;
    private $sport;
    private $comments;


    /*Métodos públicos (básicos)*/
    public function __construct($datosPost)
    {
        $this->nombre = ( isset($datosPost['nombre']) && trim($datosPost['nombre']) != '' ) ? $datosPost['nombre'] : 'Campo no asignado';
        $this->apellido = ( isset($datosPost['apellido']) && trim($datosPost['apellido']) != '' ) ? $datosPost['apellido'] : 'Campo no asignado';

        if (isset($datosPost['password1']) && trim($datosPost['password1']) != '') {
            if (isset($datosPost['password2']) && trim($datosPost['password2']) != '') {
                if ($datosPost['password1'] === $datosPost['password2']) {
                    $this->password = $datosPost['password1'];
                } else {
                    $this->password = 'Las contraseñas no coinciden';
                }
            } else {
                $this->password = 'Confirmación de contraseña no asignada';
            }
        } else {
            $this->password = 'Campo no asignado';
        }

        $this->gender = $datosPost['genero'] ?? 'Campo no asignado';
        $this->ageRange = $datosPost['rangoEdad'] ?? 'Campo no asignado';
        $this->sport = isset($datosPost['deporte']) ? 'Sí' : 'No';
        $this->comments = ( isset($datosPost['comentarios']) && trim($datosPost['comentarios']) != '' ) ? $datosPost['comentarios'] : 'Campo no asignado';
    }

    public function toHtml(): string
    {
        $html = "<h2>Datos del Usuario</h2>";
        $html .= "<dl>";
        $html .= "<dt>Nombre:</dt><dd>" . htmlspecialchars($this->nombre) . "</dd>";
        $html .= "<dt>Apellido:</dt><dd>" . htmlspecialchars($this->apellido) . "</dd>";
        $html .= "<dt>Género:</dt><dd>" . htmlspecialchars($this->gender) . "</dd>";
        $html .= "<dt>Rango de Edad:</dt><dd>" . htmlspecialchars($this->ageRange) . "</dd>";
        $html .= "<dt>Practica deporte:</dt><dd>" . htmlspecialchars($this->sport) . "</dd>";
        $commentHtml = !empty($this->comments) ? nl2br(htmlspecialchars($this->comments)) : "Sin comentarios";
        $html .= "<dt>Comentarios:</dt><dd>" . $commentHtml . "</dd>";
        $html .= "</dl>";
        return $html;
    }
}

// ==========================================
// PUESTA EN USO (Lógica de procesamiento)
// ==========================================

// 1. Comprobamos si estamos recibiendo datos por POST
if ($_SERVER["REQUEST_METHOD"] == "POST") {
    
    // 2. Creamos una "instancia" (un objeto) de la clase Usuario pasándole $_POST
    $usuarioRegistrado = new Usuario($_POST);
    
    // 3. Imprimimos el HTML que genera la clase
    echo $usuarioRegistrado->toHtml();
    
    // Enlace para volver
    echo "<br><a href='./ejercicio3_1.html'>Volver al formulario</a>";

} else {
    // Si entran directamente a procesar_formulario.php sin enviar el form
    echo "<h1>Error</h1>";
    echo "<p>No se han recibido datos. Por favor, rellena el <a href='./ejercicio3_1.html'>formulario</a>.</p>";
}

?>
