<?php
class formProcesserBetter
{
    private $datos = [];
    private $errores = [];
    private $enviado = false;
    private $pasoActual = 1; // Aquí guardamos el paso de forma segura

    private function validarPasoActual(): bool
    {
        if (!$this->enviado) return false; // No se ha enviado el formulario

        $valido=true;
        switch ($this->pasoActual) {
            case 1:
                if (empty($this->datos['nombre'])) {
                    $this->errores['nombre'] = "El campo 'Nombre' es obligatorio.";
                    $valido = false;
                }
                if (empty($this->datos['apellido'])) {
                    $this->errores['apellido'] = "El campo 'Apellido' es obligatorio.";
                    $valido = false;
                }
                break;
            case 2:
                if (empty($this->datos['password1']) || empty($this->datos['password2'])) {
                    $this->errores['password1'] = "Las contraseñas son obligatorias.";
                    $valido = false;
                } elseif ($this->datos['password1'] !== $this->datos['password2']) {
                    $this->errores['password2'] = "Las contraseñas no coinciden.";
                    $valido = false;
                }
                break;
            case 3:
                if (empty($this->datos['genero'])) {
                    $this->errores['genero'] = "El campo 'Género' es obligatorio.";
                    $valido = false;
                }
                break;
            default:
                return true; // Para pasos sin validación específica
        }
        return $valido; // Si el paso es válido
    }

    public function __construct()
    {
        if ($_SERVER["REQUEST_METHOD"] == "POST") {
            $this->enviado = true;

            //Leemos el paso actual de forma segura (si no viene, asumimos que es el paso 1)
            $this->pasoActual = (int)($_POST['paso_actual'] ?? 1);

            // Recogemos los datos y limpiamos espacios
            $this->datos['nombre'] = trim($_POST['nombre'] ?? '');
            $this->datos['apellido'] = trim($_POST['apellido'] ?? '');
            $this->datos['password1'] = $_POST['password1'] ?? '';
            $this->datos['password2'] = $_POST['password2'] ?? '';
            $this->datos['genero'] = $_POST['genero'] ?? '';
            $this->datos['rangoEdad'] = $_POST['rangoEdad'] ?? 'infante';
            $this->datos['deporte'] = isset($_POST['deporte']) ? 'Sí' : 'No';
            $this->datos['comentarios'] = trim($_POST['comentarios'] ?? '');

            // Si el paso actual es válido, avanzamos al siguiente
            if ($this->validarPasoActual()) {
                if ($this->pasoActual < 5) {
                    $this->pasoActual++;
                }
            }
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

    public function getPasoActual():int{
        return $this->pasoActual;
    }
}


// ==========================================
// PUESTA EN USO (Lógica de procesamiento)
// ==========================================
$formulario = new formProcesserBetter();

//1. Si el formulario se ha enviado y es válido, mostramos el agradecimiento y detenemos el script.

if ($formulario->haSidoEnviado() && $formulario->validar() && $formulario->getPasoActual() == 5) {
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

//2. Si es la primera vez, hay errores o el paso no está completo, mostramos el formulario (con los errores que haya)
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

    <form action="ejercicio3_2.php" method="post">
        <input type="hidden" name="paso_actual" value="<?php echo $formulario->getPasoActual(); ?>">

        <fieldset>
            <legend>Paso 1: Datos Personales</legend>
            <label>Nombre*</label>
            <input type="text" name="nombre" value="<?php echo htmlspecialchars($formulario->getDato('nombre')); ?>" />
            <?php echo $formulario->getError('nombre'); ?> <br><br>

            <label>Apellido*</label>
            <input type="text" name="apellido" value="<?php echo htmlspecialchars($formulario->getDato('apellido')); ?>" />
            <?php echo $formulario->getError('apellido'); ?>
        </fieldset>

        <?php if ($formulario->getPasoActual() >= 2): ?>
        <fieldset>
            <legend>Paso 2: Seguridad</legend>
            <?php if ($formulario->getPasoActual() > 2): ?>
                <p><i>Contraseñas guardadas.</i></p>
                <input type="hidden" name="password1" value="<?php echo htmlspecialchars($formulario->getDato('password1')); ?>">
                <input type="hidden" name="password2" value="<?php echo htmlspecialchars($formulario->getDato('password2')); ?>">
            <?php else: ?>
                <label>Contraseña*</label>
                <input type="password" name="password1" />
                <?php echo $formulario->getError('password1'); ?> <br><br>

                <label>Repita la contraseña*</label>
                <input type="password" name="password2" />
                <?php echo $formulario->getError('password2'); ?>
            <?php endif; ?>
        </fieldset>
        <?php endif; ?>

        <?php if ($formulario->getPasoActual() >= 3): ?>
        <fieldset>
            <legend>Paso 3: Detalles</legend>
            <label>¿Eres hombre?*</label>
            <input type="radio" name="genero" value="H" <?php echo ($formulario->getDato('genero') == 'H') ? 'checked' : ''; ?> />
            <label>¿O mujer?*</label>
            <input type="radio" name="genero" value="M" <?php echo ($formulario->getDato('genero') == 'M') ? 'checked' : ''; ?> />
            <?php echo $formulario->getError('genero'); ?> <br><br>

            <label>Rango de edad</label>
            <select name="rangoEdad">
                <option value="infante" <?php echo ($formulario->getDato('rangoEdad') == 'infante') ? 'selected' : ''; ?>>Infante</option>
                <option value="adolescente" <?php echo ($formulario->getDato('rangoEdad') == 'adolescente') ? 'selected' : ''; ?>>Adolescente</option>
                <option value="adulto" <?php echo ($formulario->getDato('rangoEdad') == 'adulto') ? 'selected' : ''; ?>>Adulto</option>
                <option value="mayor" <?php echo ($formulario->getDato('rangoEdad') == 'mayor') ? 'selected' : ''; ?>>Mayor</option>
            </select>
        </fieldset>
        <?php endif; ?>

        <?php if ($formulario->getPasoActual() >= 4): ?>
        <fieldset>
            <legend>Paso 4: Aficiones</legend>
            <label>¿Practicas deporte?</label>
            <input type="checkbox" name="deporte" value="Sí" <?php echo ($formulario->getDato('deporte') == 'Sí') ? 'checked' : ''; ?> />
        </fieldset>
        <?php endif; ?>

        <?php if ($formulario->getPasoActual() >= 5): ?>
        <fieldset>
            <legend>Paso 5: Finalizar</legend>
            <label>¿Algún comentario?</label><br>
            <textarea name="comentarios" rows="4" cols="50"><?php echo htmlspecialchars($formulario->getDato('comentarios')); ?></textarea>
        </fieldset>
        <?php endif; ?>

        <br>
        <input type="submit" value="<?php echo ($formulario->getPasoActual() >= 5) ? 'Finalizar' : 'Siguiente Paso'; ?>" />
    </form>
</body>

</html>