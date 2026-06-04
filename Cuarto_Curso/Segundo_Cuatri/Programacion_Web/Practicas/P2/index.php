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
    <?php putHeader(); ?>
    <main id="mainIndex">
        <section id="introSection">
            <article>
                <h2>Azimut Viajes</h2>
                <div class="carrusel" id="carrusel">
                </div>
                <p>Bienvenido a Azimut Viajes, tu agencia de viajes de confianza para descubrir los mejores destinos del mundo. Aquí encontrarás las mejores ofertas para tu próximo viaje. Seremos tu <strong>rumbo</strong> y tu <strong>dirección</strong> en cada aventura.</p>
            </article>
        </section>
        <?php if (isset($_SESSION['loggedIn']) && $_SESSION['loggedIn'] == true): ?>
            <section id="searchSection">
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

                        <datalist id="places"></datalist>
                        <input type="text" id="place" name="place" placeholder="Lugar" list="places">

                        <label for="fecha_salida">From:</label>
                        <input type="date" id="departureDate" name="departureDate"
                            min="<?php echo date('Y-m-d'); ?>">

                        <label for="fecha_regreso">To:</label>
                        <input type="date" id="returnDate" name="returnDate"
                            min="<?php echo date('Y-m-d'); ?>">

                        <button type="submit"><img id="icono_busqueda"
                                src="./imagenes/icono_busqueda.png"
                                alt="Buscar"></button>
                    </fieldset>

                </form>

            </section>
        <?php endif ?>
    </main>
    <?php putFooter(); ?>
    <script type="module" src="./js/main.js"></script>
</body>

</html>