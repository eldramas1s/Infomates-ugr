<?php

require_once __DIR__ . '/../peliculas.php';

if (isset($_GET['id']) && $_GET['id'] !== "") {
    if (is_numeric($_GET['id'])) {
        $result = Pelicula::delete((int)$_GET['id']);
        if ($result) {
            echo "<p> Borrada correctamente </p>";
            echo "<a class=\"button\" href=\"../../index.php\">Volver</a>";
        } else {
            echo "<p> No se ha podido realizar la operacion </p>";
            echo "<a class=\"button\" href=\"../../index.php\">Volver</a>";
        }
    } else {
        echo "<p> El identificador no es un numero </p>";
        echo "<a class=\"button\" href=\"../../index.php\">Volver</a>";
    }
} else {
    echo "<p> NO hay pelicula con la que trabajar </p>";
    echo "<a class=\"button\" href=\"../../index.php\">Volver</a>";
}
