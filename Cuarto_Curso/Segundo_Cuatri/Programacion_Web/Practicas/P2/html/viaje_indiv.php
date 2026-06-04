<?php
require_once '../php/utils.php';
require_once '../php/model/trips.php';
session_start();
?>
<!DOCTYPE html>
<html lang="es">

<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <link rel="stylesheet" href="../css/style.css">
    <link rel="stylesheet" href="../css/viajeIndividual.css">
    <link rel="stylesheet" href="../css/form.css">
    <title>Azimut Viajes | Jaén</title>
</head>

<body>
    <?php putHeader(1); ?>
    <?php
    //Obtenemos el viaje concreto que se ha pasado por get
    $continent = isset($_GET['continent']) && $_GET['continent'] !== '' ? $_GET['continent'] : -1;
    $country = isset($_GET['country']) && $_GET['country'] !== '' ? $_GET['country'] : -1;
    $place = isset($_GET['place']) && $_GET['place'] !== '' ? $_GET['place'] : -1;

    $destiny = null;
    if ($continent !== -1 && $country !== -1 && $place !== -1) {
        $infoTrip = InfoTrips::getInfoTrips($continent, $country, $place);
        if (!empty($infoTrip)) {
            $destiny = $infoTrip->getDatos(); //Obtenemos el primer resultado, ya que debería ser el único
        } else {
            //Si no hay resultados, es porque la tarjeta del destino no debería mostrarse, pues solo se accede por ahí.
            echo "<main><h2>Viaje no encontrado</h2><p>Ups! El viaje que señalaste no debería existir, avise al administrador.</p></main>";
            putFooter(1);
            exit;
        }
    } else {
        //Si no se han pasado los parámetros necesarios, mostramos un mensaje de error
        echo "<main><h2>Parámetros insuficientes</h2><p>Ups! No se han pasado los parámetros necesarios para mostrar el viaje, avise al administrador.</p></main>";
        putFooter(1);
        exit;
    }
    ?>
    <?php if ($destiny): ?>
        <main id="viajeIndividualMain">
            <section>
                <h2><?php echo $destiny['country'] . ", " . $destiny['place']; ?></h2>
                <img src="../imagenes/<?php echo $destiny['img']; ?>" alt="imagen del destino" id="imgIndiv">

                <article id="infoArticle">
                    <h3>Vive una genial experiencia</h3>
                    <hr>
                    <p>
                        <?php echo $destiny['sortDesc']; ?>
                        <br> <br>
                        <?php echo $destiny['longDesc']; ?>
                    </p>
                    <h3>Alojamientos</h3>
                    <hr>
                    <ul id="alojamientosUl">
                        <?php $alojamientos = $destiny['lodging'] ? explode(',', $destiny['lodging']) : []; ?>
                        <?php foreach ($alojamientos as $alojamiento): ?>
                            <li><?php echo trim($alojamiento); ?></li>
                        <?php endforeach; ?>
                    </ul>
                </article>
                <article id="interesArticle">
                    <h3>Algunos viajes interesantes</h3>
                        <?php $relatedTrips = $infoTrip->getRelatedTrips(); ?>
                        <nav id="relatedTripsNav">

                            <?php if (!empty($relatedTrips)): ?>
                                <ul>
                                    <?php foreach ($relatedTrips as $relatedTrip):
                                        $datos = $relatedTrip->getDatos();
                                    ?>
                                        <li>
                                            <a href="../html/viaje_indiv.php?continent=<?php echo htmlspecialchars($datos['continent']); ?>&country=<?php echo htmlspecialchars($datos['country']); ?>&place=<?php echo htmlspecialchars($datos['place']); ?>">
                                                <?php echo htmlspecialchars($datos['country'] . ", " . $datos['place']); ?>
                                            </a>
                                        </li>
                                    <?php endforeach; ?>
                                </ul>
                            <?php else: ?>
                                <p>Lo sentimos, no hay viajes relacionados disponibles en este momento.</p>
                            <?php endif; ?>

                    </nav>
                </article>
            </section>
            <script src="../js/main.js" type="module"></script>

        </main>
    <?php putFooter(1);
    endif ?>
</body>

</html>