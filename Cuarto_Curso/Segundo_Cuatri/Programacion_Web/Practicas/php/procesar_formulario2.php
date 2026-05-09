<?php
class formProcesser
{
    private $datos = [];
    private $errores = [];
    private $enviado = false;

    public function __construct()
    {
        if ($_SERVER["REQUEST_METHOD"] == "POST") {
            $this->enviado = true;
            // Recogemos los datos y limpiamos espacios
            $this->datos['nombre'] = trim($_POST['nombre'] ?? '');
            $this->datos['apellido'] = trim($_POST['apellido'] ?? '');
            $this->datos['password1'] = $_POST['password1'] ?? '';
            $this->datos['password2'] = $_POST['password2'] ?? '';
            $this->datos['genero'] = $_POST['genero'] ?? '';
            $this->datos['rangoEdad'] = $_POST['rangoEdad'] ?? 'infante';
            $this->datos['deporte'] = isset($_POST['deporte']) ? 'Sí' : 'No';
            $this->datos['comentarios'] = trim($_POST['comentarios'] ?? '');
        } else {
            // Si es la primera vez que se entra (no hay POST), inicializamos en vacío
            $this->datos = [
                'nombre' => '',
                'apellido' => '',
                'password1' => '',
                'password2' => '',
                'genero' => '',
                'rangoEdad' => 'infante',
                'deporte' => 'No',
                'comentarios' => ''
            ];
        }
    }

    public function validar(): bool
    {
        if (!$this->enviado) return false; // No se ha enviado el formulario

        //Comprobamos los campos obligatorios
        if (empty($this->datos['nombre'])) {
            $this->errores['nombre'] = "El campo 'Nombre' es obligatorio.";
        }

        if (empty($this->datos['apellido'])) {
            $this->errores['apellido'] = "El campo 'Apellido' es obligatorio.";
        }

        if (empty($this->datos['password1']) || empty($this->datos['password2'])) {
            $this->errores['password1'] = "Las contraseñas son obligatorias.";
        }

        if ($this->datos['password1'] !== $this->datos['password2']) {
            $this->errores['password2'] = "Las contraseñas no coinciden.";
        }

        if (empty($this->datos['genero'])) {
            $this->errores['genero'] = "El campo 'Género' es obligatorio.";
        }
        return empty($this->errores); // Si no hay errores, la validación es correcta
    }

    public function haSidoEnviado(): bool
    {
        return $this->enviado;
    }

    public function getDato($campo)
    {
        return $this->datos[$campo] ?? null;
    }

    public function getError($campo)
    {
        return isset($this->errores[$campo]) ? "<span style='color:red; font-size:0.9em;'> " . $this->errores[$campo] . "</span>" : "";
    }

    public function hayErrores(): bool
    {
        return !empty($this->errores);
    }
}


// ==========================================
// PUESTA EN USO (Lógica de procesamiento)
// ==========================================
$formulario = new formProcesser();

//1. Si el formulario se ha enviado y es válido, mostramos el agradecimiento y detenemos el script.

if ($formulario->haSidoEnviado() && $formulario->validar()) {
    echo "<h1>¡Gracias por registrarte!</h1>";
    echo "<p>Todos los datos han sido procesados correctamente.</p>";
    echo "<dl>";
    echo "<dt><strong>Nombre:</strong></dt>";
    echo "<dd>" . htmlspecialchars($formulario->getDato('nombre')) . "</dd>";
    echo "<dt><strong>Apellido:</strong></dt>";
    echo "<dd>" . htmlspecialchars($formulario->getDato('apellido')) . "</dd>";
    echo "</dl>";
    // Detenemos la ejecución para que no dibuje el formulario de nuevo
    exit();
}

//2. Si es la primera vez o hay errores, mostramos el formulario (con los errores que haya)
?>

<!DOCTYPE html>
<html lang="en">

<head>
    <title>Formulario con POO</title>
</head>

<body>
    <h1> Ejemplo de formulario con POO </h1>
    <?php
    if ($formulario->haSidoEnviado() && $formulario->hayErrores()) {
        echo "<h2>¡Por favor, corrige los errores!</h2>";
        echo "<p>Por favor, corrige los errores marcados en rojo y vuelve a enviar el formulario.</p>";
    } else {
        echo "<h2>¡Bienvenido!</h2>";
        echo "<p>Por favor, rellene los siguientes datos (los campos con <span class='requerido'>*</span> son obligatorios) y haga clic en el botón Enviar.</p>";
    }
    ?>

    <form action="procesar_formulario2.php" method="post">
        <label for="nombre">Nombre*</label>
        <input type="text" name="nombre" id="nombre" value="<?php echo htmlspecialchars($formulario->getDato('nombre')); ?>" />
        <?php echo "<p>" . $formulario->getError('nombre') . "</p>"; ?>

        <label for="apellido">Apellido*</label>
        <input type="text" name="apellido" id="apellido" value="<?php echo htmlspecialchars($formulario->getDato('apellido')); ?>" />
        <?php echo "<p>" . $formulario->getError('apellido') . "</p>"; ?>

        <label for="password1">Contrase&ntilde;a*</label>
        <input type="password" name="password1" id="password1" value="" />
        <?php echo "<p>" . $formulario->getError('password1') . "</p>"; ?>

        <label for="password2">Repita la contrase&ntilde;a*</label>
        <input type="password" name="password2" id="password2" value="" />
        <?php echo "<p>" . $formulario->getError('password2') . "</p>"; ?>

        <label for="generoHombre">¿Eres hombre?*</label>
        <input type="radio" name="genero" id="generoHombre" value="H" <?php echo ($formulario->getDato('genero') == 'H') ? 'checked' : ''; ?> />
        <label for="generoMujer">¿O mujer?*</label>
        <input type="radio" name="genero" id="generoMujer" value="M" <?php echo ($formulario->getDato('genero') == 'M') ? 'checked' : ''; ?> />
        <?php echo "<p>" . $formulario->getError('genero') . "</p>"; ?>

        <label for="rangoEdad">Rango de edad</label>
        <select name="rangoEdad" id="rangoEdad" size="1">
            <option value="infante" <?php echo ($formulario->getDato('rangoEdad') == 'infante') ? 'selected' : ''; ?>>Infante</option>

            <option value="adolescente" <?php echo ($formulario->getDato('rangoEdad') == 'adolescente') ? 'selected' : ''; ?>>Adolescente</option>

            <option value="adulto" <?php echo ($formulario->getDato('rangoEdad') == 'adulto') ? 'selected' : ''; ?>>Adulto</option>

            <option value="mayor" <?php echo ($formulario->getDato('rangoEdad') == 'mayor') ? 'selected' : ''; ?>>Mayor</option>

        </select>

        <label for="deporte">&iquest;Practicas deporte&#63</label>
        <input type="checkbox" name="deporte" id="deporte" value="S&iacute;" <?php echo ($formulario->getDato('deporte') =='Sí') ? 'checked' : ''; ?> />

        <label for="comentarios">&iquest;Alg&uacute;n comentario?</label>
        <textarea name="comentarios" id="comentarios" rows="4" cols="50"> <?php echo htmlspecialchars($formulario->getDato('comentarios')); ?> </textarea>

        <input type="submit" name="botonDeEnvio" id="botonDeEnvio" value="Enviar datos" />

        <input type="reset" name="bontonDeReset" id="botonDeReset" value="Vaciar formulario" />
    </form>
</body>

</html>