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
    <link rel="stylesheet" href="../css/form.css">
    <link rel="stylesheet" href="../css/viajes.css">
    <title>Azimut Viajes | España</title>
</head>

<body>
    <?php putHeader(1); ?>
    <aside id="menuViajesPais">
        <nav>
            <?php
            $destinies = Trip::getCountriesByContinents();
            ?>
            <h2>Destinos</h2>
            <?php
            if (!empty($destinies)) {
                foreach ($destinies as $continentName => $countriesArray) {
                    echo "<details class=\"listaContinentes\">
                            <summary>&#127757; " . htmlspecialchars($continentName) . " </summary>
                        <ul class=\"listaPaises\">";
                    foreach ($countriesArray as $country) {
                        echo "<li><a href=\"../html/viajes_pais.php?country=" . htmlspecialchars($country) . "\"> " . $country . "</a></li>";
                    }
                    echo "</ul> </details>";
                }
            } else {
                echo "<p> Parece que no hay destinos ;) </p>";
            }
            ?>
        </nav>

    </aside>
    <main class="viajesCuadricula">
        <?php
        $page = isset($_GET['page']) ? (int)$_GET['page'] : 1;
        $country = isset($_GET['country']) ? $_GET['country'] : "";
        $trips = infoTrips::getAllBetween(-1, $country,-1,-1,-1);
        $trips = groupByNumber($trips, 9);
        $totalPages = count($trips);
        $prePag = $page;
        $posPag = $page;
        if (!empty($trips) && $page >= 1 && $page <= $totalPages) {
            //Consideramos la lógica circular
            $prePag = ($page <= 1) ? $totalPages : $page - 1;
            $posPag = ($page % $totalPages) + 1;
        }

        ?>
        <?php if($totalPages>1):?>
            <nav class="flechasGrupos">
                <a href="../html/viajes.php?page=<?php echo $prePag; ?>" class="flechaIzq">&#10094;</a>
                <a href="../html/viajes.php?page=<?php echo $posPag; ?>" class="flechaDcha">&#10095;</a>
            </nav>
        <?php endif?>

        <?php
        if (!empty($trips) && $page >= 1 && $page <= $totalPages) {

            $group = $trips[$page - 1];
            echo "<section class=\"viajes\" id=\"grupo" . $page . "\">";
            echo "<h2>Viajes</h2>";
            foreach ($group as $elem => $tripData) {
                $trip = new infoTrips($tripData);
                echo $trip->tripToHtml(false, $page);
            }
            echo "</section>";
        } else {
            echo "<p> Ups! Parece que no hay viajes ;) </p>";
        }

        ?>
        <script src="../js/main.js" type="module"></script>
    </main>
    <?php putFooter(1);?>
    
</body>

</html>