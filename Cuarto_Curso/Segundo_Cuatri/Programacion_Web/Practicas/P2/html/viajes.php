<?php
require_once '../php/utils.php';
require_once '../php/trips.php';

session_start();
ini_set('display_errors', 1);
error_reporting(E_ALL);
?>
<!DOCTYPE html>
<html lang="es">

<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <link rel="stylesheet" href="../css/style.css">
    <link rel="stylesheet" href="../css/form.css">
    <link rel="stylesheet" href="../css/viajes.css">
    <title>Azimut Viajes | Viajes</title>
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
                <li><a href="../html/viajes.php?page=1">Viajes</a></li>
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
        $trips = Trip::getAll();
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

        <?php if (isset($_SESSION['admin']) && $_SESSION['admin'] === true): ?>
            <h2>!Gestiona los viajes <?php echo $_SESSION['nickName'] ?>! </h2>
            <form id="countryForm" action="./viajes.php" method="post">
                <div class="field">
                    <datalist id="continentes">
                        <option value="Asia">Asia</option>
                        <option value="Africa">Africa</option>
                        <option value="Europa">Europa</option>
                        <option value="Oceania">Oceania</option>
                        <option value="America">America</option>
                    </datalist>
                    <label for="continent">Continente</label>
                    <input type="text" id="continent" name="continent" list="continentes">
                </div>
                <div class="field">
                    <label for="country">Pais</label>
                    <input type="text" name="country" id="country" list="paises">
                    <datalist id="paises"></datalist>
                </div>
                <div class="field">
                    <label for="place">Lugar</label>
                    <input type="text" name="place" id="place" list="places">
                    <datalist id="places"></datalist>
                </div>
                <div class="field">
                    <label for="price">Precio</label>
                    <input type="number" name="price" id="price" step="1" min="0">
                </div>
                <div class="field">
                    <label for="fechaSalida">Fecha</label>
                    <input type="date" name="departureDate" id="fechaSalida" min=<?php echo date('Y-m-d'); ?>>
                </div>
                <div class="field">
                    <label for="fechaVuelta">Fecha</label>
                    <input type="date" name="returnDate" id="fechaVuelta" min=<?php echo date('Y-m-d'); ?>>
                </div>
                <div class="field">
                    <label for="lodging">Alojamiento</label>
                    <input type="text" name="lodging" id="lodging" placeholder="[hotel], [albergue], [hostal]">
                </div>
                <div class="field">
                    <label for="sortDesc">Breve descripción:</label>
                    <input type="textarea" name="sortDesc" id="sortDesc" rows="3" columns="34" placeholder="Escribe una breve descripcion">
                </div>
                <div class="field">
                    <label for="longDesc">Descripción:</label>
                    <input type="textarea" name="longDesc" id="longDesc" rows="5" columns="50" placeholder="Escribe una breve descripcion">
                </div>
                <div class="field">
                    <label for="img">Nombre de la imagen</label>
                    <input type="text" name="img" id="img" placeholder="ejemplo.jpg">
                </div>
                <button type="submit">Done</button>
            </form>

            <!--Los scripts solo aportan funcionalidades a los administradores-->
            <script src="../js/main.js" type="module"></script>
            <script src="../js/deleteTrip.js" type="module"></script>
        <?php endif; ?>
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
        <p id="fechaModificacion"><?php echo date('Y-m-d') ?></p>
    </footer>
</body>

</html>