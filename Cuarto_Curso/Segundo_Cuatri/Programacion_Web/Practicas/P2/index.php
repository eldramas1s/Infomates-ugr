<!DOCTYPE html>
<html lang="es">
    <head>
        <meta charset="UTF-8">
        <meta name="viewport" content="width=device-width, initial-scale=1.0">
        <link rel="stylesheet" href="./css/style.css">
        <link rel="stylesheet" href="./css/form.css">
        <link rel="stylesheet" href="./css/index.css">
        <title>Azimut Viajes | Exclusividad en cada sitio</title>
    </head>
    <body>
        <header>

            <h1 id="nombreDecor">Azimut Viajes</h1>

            <img  id="logoHeader" src="./imagenes/logoAzimut.png" alt="Logotipo Azimut">

            <?php
            require_once './php/utils.php';
            require_once './php/forms.php';
            require_once './php/conection.php';
            session_start();

            //Procesamos el formulario de login
            if($_SERVER['REQUEST_METHOD'] === 'POST' && isset($_POST['nickName']) && isset($_POST['password'])){
                $db = new Database();
                $form = new FormLogIn($db->connect());
                $form->handle($_POST); //Si hay errores se escriben en el html
            }

            //Si no se ha loggeado, pongo el formulario
            if(!isset($_SESSION['loggedIn']) || $_SESSION['loggedIn'] === false) {
                putsignUpForm();
            } else { //Si se ha loggeado ponemos el avatar con la inicial del nickname y el boton de cierre de sesión
                putAvatar($_SESSION['initial'], $_SESSION['nickName'], true);
            }
            ?> 
            <nav id="menuHeader">
                <ul>
                    <li><a href="./index.php">Inicio</a></li>
                    <li><a href="./html/viajes.php">Viajes</a></li>
                    <li><a href="./html/viajes_grupo.php">Viajes en
                            grupo</a></li>
                    <li><a href="./html/ofertas.php">Ofertas</a></li>
                    <li><a href="./html/sobre_agencia.php">Sobre nuestra
                            agencia</a></li>
                    <li><a href="./html/sugerencias.php">Sugerencias</a></li>
                </ul>
            </nav>
        </header>
        <main>
            <section id="introSection">
                <article>
                    <h2>Azimut Viajes</h2>
                    <img src="./imagenes/brasilPLNM.png" alt="Imagen de Brasil" id="imagenIndex" >
                    <p>Bienvenido a Azimut Viajes, tu agencia de viajes de confianza para descubrir los mejores destinos del mundo. Aquí encontrarás las mejores ofertas para tu próximo viaje. Seremos tu <strong>rumbo</strong> y tu <strong>dirección</strong> en cada aventura.</p>
                </article>
            </section>
            <section id="searchSection" >
                <form id="formularioBusqueda" method="post" action="./index.php" autocomplete="off" target="blank">

                    <fieldset>
                        <input type="search" id="destino" name="destino" required
                            placeholder="Destination" >

                        <label for="fecha_salida">From:</label>
                        <input type="date" id="fecha_salida" name="fecha_salida"
                            required min="2026-04-22">

                        <label for="fecha_regreso">To:</label>
                        <input type="date" id="fecha_regreso" name="fecha_regreso"
                            required min="2026-04-23">

                        <button type="submit"><img id="icono_busqueda"
                                src="./imagenes/icono_busqueda.png"
                                alt="Buscar"></button>
                    </fieldset>
                    
                </form>

            </section>
        </main>
        <footer>
            <nav id="menuFooter">
                <ul>
                    <li><a href="./html/contacto.php">Contacte con
                            nosotros</a></li>
                    <li><a href="./como_se_hizo.pdf"
                            target="_blank">Cómo se
                            hizo</a></li>
                </ul>
            </nav>
            <p id="fechaModificacion">27/04/2026</p>
        </footer>
    </body>
</html>

