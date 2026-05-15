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
            <h1 id="nombreDecor" >Azimut Viajes</h1>

            <img  id="logoHeader" src="../imagenes/logoAzimut.png" alt="Logotipo Azimut">

            <nav id="menuHeader">
                <ul>
                    <li><a href="../index.html">Inicio</a></li>
                    <li><a href="../html/viajes.html">Viajes</a></li>
                    <li><a href="../html/viajes_grupo.html">Viajes en
                            grupo</a></li>
                    <li><a href="../html/ofertas.html">Ofertas</a></li>
                    <li><a href="../html/sobre_agencia.html">Sobre nuestra
                            agencia</a></li>
                    <li><a href="../html/sugerencias.html">Sugerencias</a></li>
                </ul>
            </nav>
        </header>
        <main>
            <?php
                require_once '../php/forms.php';
                require_once '../php/conection.php';

                if($_SERVER['REQUEST_METHOD'] === 'POST'){
                    $db = new Database();
                    $conn = $db->connect();
                    if ($conn){
                        $form = new FormSignUp($conn);
                        $form->handle($_POST);
                    } //No tengo que poner el else porque el constructor de Database ya se encarga de mostrar el error en caso de que falle la conexión
                }
            
            ?>

            <form id="formularioAlta" method="post" action="../html/altausuarios.php">
                <h1>Alta de usuarios</h1>
                <fieldset>
                    <p>
                        <label for="nombre">Nombre:*</label>
                        <input type="text" id="nombre" name="nombre" maxlength="30" 
                            title="Solo se admiten caracteres alfabéticos.">
                    </p>

                    <p>
                        <label for="nickName">Nickname:*</label>
                        <input type="text" id="nickName" name="nickName"  maxlength="30">
                    </p>

                    <p>
                        <label for="email">Email:*</label>
                        <input type="email" id="email" name="email" maxlength="100">
                    </p>

                    <p>
                        <label for="password">Contraseña:*</label>
                        <input type="password" id="password" name="password" 
                        title="Entre 8 y 15 caracteres, al menos una mayúscula, una minúscula, un dígito, un carácter especial y sin espacios. ">
                    </p>
                    <p>
                        <label for="adulto">¿Eres mayor de edad?</label>
                        <input type="radio" name="adultez" id="adulto" value="adulto"> Si
                        <input type="radio" name="adultez" id="menor" value="menor"> No
                    </p>

                    <p>
                        <a href="../aviso_legal.pdf" target="_blank" id="enlaceLegal">Aviso legal</a>
                    </p>
                    <p class="zonaAceptar">
                        Ha leído el aviso legal:* <input type="checkbox" name="aceptar" id="checkLegal" >
                    </p>
                    <p>
                        <button type="submit">Registrarse</button>
                    </p>
                </fieldset>

            </form>
            
        </main>
        <footer>
            <nav id="menuFooter">
                <ul>
                    <li><a href="../html/contacto.html">Contacte con
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
