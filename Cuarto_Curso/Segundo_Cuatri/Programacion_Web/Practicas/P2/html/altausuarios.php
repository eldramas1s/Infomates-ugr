<?php
require_once __DIR__ . '/../php/utils.php';
?>

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

        <form id="formularioAlta" method="post" action="../html/altausuarios.html">
            <h1>Alta de usuarios</h1>
            <fieldset>
                <div class="field">
                    <label for="nombre">Nombre:*</label>
                    <input type="text" id="nombre" name="nombre" >
                </div>

                <div class="field">
                    <label for="nickName">Nickname:*</label>
                    <input type="text" id="nickName" name="nickName">
                </div>

                <div class="field">
                    <label for="email">Email:*</label>
                    <input type="email" id="email" name="email">
                </div>

                <div class="field">
                    <label for="password">Contraseña:*</label>
                    <input type="password" id="password" name="password">
                </div>
                <div class="field" id="adultez">
                    <label for="adulto">¿Eres mayor de edad?</label>
                    <input type="radio" name="adultez" id="adulto" value="1" > Si
                    <input type="radio" name="adultez" id="menor" value="0" > No
                </div>

                <div class="field" id="legal">
                    <a href="../aviso_legal.pdf" target="_blank" id="enlaceLegal">Aviso legal</a>
                </div>
                <div class="field" id="checkLegalDiv">
                    <label for="checkLegal">He leído el aviso legal*</label>
                    <input type="checkbox" name="aceptar" id="checkLegal">
                </div>
                <div>
                    <button type="submit">Registrarse</button>
                </div>
            </fieldset>

        </form>

    </main>
    <?php putFooter(1); ?>
    <script type="module" src="../js/main.js"></script>
</body>

</html>