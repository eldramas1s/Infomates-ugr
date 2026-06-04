<?php
    require_once '../php/utils.php';
    session_start();
?>
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
        <?php putHeader(1); ?>
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
        <?php putFooter(1); ?>
    </body>
</html>