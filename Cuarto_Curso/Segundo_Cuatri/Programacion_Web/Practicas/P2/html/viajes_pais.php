<?php
require_once '../php/utils.php';
require_once '../php/trips.php';
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
    <header>

        <h1 id="nombreDecor">Azimut Viajes</h1>

        <img id="logoHeader" src="../imagenes/logoAzimut.png"
            alt="Logotipo Azimut">

        <?php

        //Si se ha loggeado ponemos el avatar y el boton de cerrar sesion
        if (isset($_SESSION['loggedIn']) && $_SESSION['loggedIn'] === true) {
            putAvatar($_SESSION['admin'], $_SESSION['nickName'], 1);
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
        $trips = Trip::getAllBetween(-1, $country,-1,-1,-1);
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
                $trip = new Trip($tripData);
                echo $trip->tripToHtml(true, $page);
            }
            echo "</section>";
        } else {
            echo "<p> Ups! Parece que no hay viajes ;) </p>";
        }

        ?>

    </main>
    <footer>
        <nav id="menuFooter">
            <ul>
                <li><a href="../../html/contacto.php">Contacte con
                        nosotros</a></li>
                <li><a href="../../como_se_hizo.pdf"
                        target="_blank">Cómo se
                        hizo</a></li>
            </ul>
        </nav>
        <p id="fechaModificacion">27/04/2026</p>
    </footer>
</body>

</html>