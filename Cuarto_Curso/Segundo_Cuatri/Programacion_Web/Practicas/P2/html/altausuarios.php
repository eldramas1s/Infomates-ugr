<!DOCTYPE html>
<html lang="es">

<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <link rel="stylesheet" href="../css/style.css">
    <link rel="stylesheet" href="../css/form.css">
    <title>Azimut Viajes | Alta de usuarios</title>
</head>

<body>
    <header>
        <h1 id="nombreDecor">Azimut Viajes</h1>

        <img id="logoHeader" src="../imagenes/logoAzimut.png" alt="Logotipo Azimut">

        <nav id="menuHeader">
            <ul>
                <li><a href="../index.php">Inicio</a></li>
                <li><a href="../html/viajes.php">Viajes</a></li>
                <li><a href="../html/viajes_grupo.php">Viajes en
                        grupo</a></li>
                <li><a href="../html/ofertas.php">Ofertas</a></li>
                <li><a href="../html/sobre_agencia.php">Sobre nuestra
                        agencia</a></li>
                <li><a href="../html/sugerencias.php">Sugerencias</a></li>
            </ul>
        </nav>
    </header>
    <main>
        <?php
        require_once '../php/forms.php';
        require_once '../php/conection.php';

        $sent = false;
        $status = false;
        $errorsList = [];
        if ($_SERVER['REQUEST_METHOD'] === 'POST') {
            $sent = true;
            $db = new Database();
            $form = new FormSignUp($db->connect());
            $status = $form->handle($_POST);

            if(!$status){
                $errorsList = $form->getErrors();
            }
        }
        ?>

        <?php if (!$sent || !$status ): ?>
            <?php if (!empty($errorsList)){
                foreach ($errorsList as $field => $message) {
                    echo "<p class=\"error\"> Error en $field: $message </p>";
                }
            }
            ?>
        <form id="formularioAlta" method="post" action="../html/altausuarios.php">
            <h1>Alta de usuarios</h1>
            <fieldset>
                <p>
                    <label for="nombre">Nombre:*</label>
                    <input type="text" id="nombre" name="nombre" maxlength="30"
                        value="<?php echo isset($_POST['nombre']) ? htmlspecialchars($_POST['nombre']) : ''; ?>"
                        title="Solo se admiten caracteres alfabéticos.">
                </p>

                <p>
                    <label for="nickName">Nickname:*</label>
                    <input type="text" id="nickName" name="nickName" maxlength="30"
                        value="<?php echo isset($_POST['nickName']) ? htmlspecialchars($_POST['nickName']) : ''; ?>">
                </p>

                <p>
                    <label for="email">Email:*</label>
                    <input type="email" id="email" name="email" maxlength="100"
                        value="<?php echo isset($_POST['email']) ? htmlspecialchars($_POST['email']) : ''; ?>">
                </p>

                <p>
                    <label for="password">Contraseña:*</label>
                    <input type="password" id="password" name="password"
                        title="Entre 8 y 15 caracteres, al menos una mayúscula, una minúscula, un dígito, un carácter especial y sin espacios. ">
                </p>
                <p>
                    <label for="adulto">¿Eres mayor de edad?</label>
                    <input type="radio" name="adultez" id="adulto" value="1" <?php echo (isset($_POST['adultez']) && $_POST['adultez'] === 'adulto') ? 'checked' : ''; ?>> Si
                    <input type="radio" name="adultez" id="menor" value="0" <?php echo (isset($_POST['adultez']) && $_POST['adultez'] === 'menor') ? 'checked' : ''; ?>> No
                </p>

                <p>
                    <a href="../aviso_legal.pdf" target="_blank" id="enlaceLegal">Aviso legal</a>
                </p>
                <p class="zonaAceptar">
                    Ha leído el aviso legal:* <input type="checkbox" name="aceptar" id="checkLegal"
                        <?php echo isset($_POST['aceptar']) ? 'checked' : ''; ?>>
                </p>
                <p>
                    <button type="submit">Registrarse</button>
                </p>
            </fieldset>

        </form>
        <?php else: ?>
            <section id="todoOkey">
                <h2>Se ha registrado con éxito</h2>
                <p>Para volver al menú de inicio pulse el botón que aparece en pantalla</p>
                <a href="../index.php">Volver</a>
            </section>
        <?php endif; ?>

    </main>
    <footer>
        <nav id="menuFooter">
            <ul>
                <li><a href="../html/contacto.php">Contacte con
                        nosotros</a></li>
                <li><a href="../como_se_hizo.pdf"
                        target="_blank">Cómo se
                        hizo</a></li>
            </ul>
        </nav>
        <p id="fechaModificacion">27/04/2026</p>
    </footer>
</body>

</html>