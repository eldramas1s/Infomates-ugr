<?php
    //Iniciamos la sesión
    session_start();
    require_once './php/utils.php';
?>

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

            //Si no se ha loggeado, pongo el formulario
            if(!isset($_SESSION['loggedIn']) || $_SESSION['loggedIn'] === false) {
                putsignUpForm();
            } else { //Si se ha loggeado ponemos el avatar con la inicial del nickname y el boton de cierre de sesión
                putAvatar($_SESSION['admin'], $_SESSION['nickName'],0);
            }
            ?> 
            <nav id="menuHeader">
                <ul>
                    <li><a href="./index.php">Inicio</a></li>
                    <li><a href="./html/viajes.php?page=1">Viajes</a></li>
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
            <?php if(isset($_SESSION['loggedIn']) && $_SESSION['loggedIn'] == true): ?>
            <section id="searchSection" >
                <form id="formularioBusqueda" method="get" action="./html/viajes_buscados.php" autocomplete="off" target="_self">

                    <fieldset>
                        <datalist id="continentes">
                            <option value="Europa">Europa</option>
                            <option value="Asia">Asia</option>
                            <option value="America">América</option>
                            <option value="Africa">África</option>
                            <option value="Oceania">Oceanía</option>
                        </datalist>
                        <input type="text" id="continent" name="continent" placeholder="Continente" list="continentes">

                        <datalist id="paises"></datalist>
                        <input type="text" id="country" name="country" placeholder="País" list="paises">

                        <datalist id="lugares"></datalist>
                        <input type="text" id="place" name="place" placeholder="Lugar" list="lugares">

                        <label for="fecha_salida">From:</label>
                        <input type="date" id="departureDate" name="departureDate"
                            min="<?php echo date('Y-m-d');?>">

                        <label for="fecha_regreso">To:</label>
                        <input type="date" id="returnDate" name="returnDate"
                            min="<?php echo date('Y-m-d');?>">

                        <button type="submit"><img id="icono_busqueda"
                                src="./imagenes/icono_busqueda.png"
                                alt="Buscar"></button>
                    </fieldset>
                    
                </form>

            </section>
            <?php endif ?>
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
            <p id="fechaModificacion"><?php echo date('Y-m-d')?></p>
        </footer>
        <script type="module" src="./js/main.js"></script>
    </body>
</html>

