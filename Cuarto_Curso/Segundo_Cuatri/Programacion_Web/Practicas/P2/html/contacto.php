<!DOCTYPE html>
<html lang="es">
    <head>
        <meta charset="UTF-8">
        <meta name="viewport" content="width=device-width, initial-scale=1.0">
        <link rel="stylesheet" href="../css/style.css">
        <link rel="stylesheet" href="../css/contacto.css">
        <link rel="stylesheet" href="../css/form.css">
        <title>Azimut Viajes | Contacto</title>
    </head>
    <body>
        <header>

            <h1 id="nombreDecor" >Azimut Viajes</h1>

            <img  id="logoHeader" src="../imagenes/logoAzimut.png" alt="Logotipo Azimut">

            <?php
            require_once '../php/utils.php';
            session_start();

            //Si se ha loggeado ponemos el avatar y el boton de cerrar sesion
            if(isset($_SESSION['loggedIn']) && $_SESSION['loggedIn'] === true) {
                putAvatar($_SESSION['admin'], $_SESSION['nickName'],1);
            }
            ?>

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
        <main id="basicMain">
            <section id="sobreMi"> 
                
                <h2>Algunos datos</h2>
                <img src="../imagenes/fotoDesarrollador.jpeg" alt="Foto del desarrollador">
                <ul>
                    <li>Nombre: Lucas Hidalgo Herrera</li>
                    <li>Fecha de nacimiento: 10 de noviembre de 2004</li>
                    <li>Email: e.lucashidalgo@go.ugr.es</li>
                    <li>Grado: Ingeniería Informática y Matemáticas</li>
                    <li>Dirección: Calle Gonzalo Gallas, 23</li>
                    <li>Estudios musicales: Grado Medio en la especialidad de Trompeta y Composición</li>
                </ul>
                
            </section>
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