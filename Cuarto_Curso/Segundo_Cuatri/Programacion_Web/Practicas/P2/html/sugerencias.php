<!DOCTYPE html>
<html lang="es">
    <head>
        <meta charset="UTF-8">
        <meta name="viewport" content="width=device-width, initial-scale=1.0">
        <link rel="stylesheet" href="../css/style.css">
        <link rel="stylesheet" href="../css/form.css">
        <link rel="stylesheet" href="../css/sugerencias_nuestra_agencia.css">
        <title>Azimut Viajes | Sugerencias</title>
    </head>
    <body>
        <header>

            <h1 id="nombreDecor">Azimut Viajes</h1>

            <img id="logoHeader" src="../imagenes/logoAzimut.png"
                alt="Logotipo Azimut">

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
        <main>
            <section class="intercalar" id="listaExperiencias">
                <h2>Experiencias y Opiniones de otros usuarios</h2>
                <article>
                    <h3 class="sugerencia"> Carlos M. -
                        <small>Sugerencia</small></h3>
                    <p>Valoración:<strong class="stars"> &starf; &starf; &starf;
                            &star; &star; </strong></p>
                    <p>Podrían ofertar más viajes orientados a climas fríos.</p>
                    <h4>¿Qué se ofrecía en tu experiencia? </h4>
                    <p>Alojamiento en Hotel, Transporte privado</p>
                </article>

                <article>
                    <h3 class="experiencia"> Paula M. -
                        <small>Experiencia</small></h3>
                    <p>Valoración: <strong class="stars"> &starf; &starf;
                            &starf; &starf; &star; </strong></p>
                    <p>Visité Sabiote, es un pueblo pequeño; coincidí con las
                        fiestas del Medievo y el ambiente fue espectacular.
                        Durante el primer fin de semana de mayo, parte del
                        pueblo se convierte en una aldea medival.</p>
                    <p>Lo único que no me gustó fue que el alojamiento
                        proporcionado no fue demasiado bueno.</p>
                    <h4>¿Qué se ofrecía en tu experiencia? </h4>
                    <p>Alojamiento en Hotel, Transporte privado</p>
                </article>
                <article>
                    <h3 class="experiencia"> Jaime H. -
                        <small>Experiencia</small></h3>
                    <p>Valoración: <strong class="stars"> &starf; &starf;
                            &starf; &starf; &star; </strong></p>
                    <p>La experiencia viendo las auroras boreales de Laponia fue
                        increíble, el paisaje es espectacular y el ambiente es
                        muy tranquilo. Además, el alojamiento proporcionado era
                        de gran calidad.</p>
                    <p>Lo único que no me gustó fue que el viaje se hizo un poco
                        corto, me hubiera gustado que durara un poco más.</p>
                    <h4>¿Qué se ofrecía en tu experiencia? </h4>
                    <p>Alojamiento en Hotel, Transporte privado, Guía turístico
                    </p>
                </article>
            </section>

            <?php
            if(isset($_SESSION['loggedIn']) && $_SESSION['loggedIn'] === true) {
                putFormSugerencias();
            } else {
                echo '<p class="informativo" id="mensajeLogin">Inicia sesión para compartir tu experiencia o sugerencia.</p>';
            }
            ?>
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