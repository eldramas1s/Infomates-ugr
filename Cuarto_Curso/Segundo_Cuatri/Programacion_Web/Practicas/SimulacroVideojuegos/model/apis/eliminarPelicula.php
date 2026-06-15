<?php

require_once __DIR__ . '/../Videojuegos.php';

if (isset($_GET['id']) && $_GET['id'] !== "") {
    if (Videojuego::exists($_GET['id'])) {
        $result = Videojuego::delete($_GET['id']);
        if ($result) {
            echo "<p> Se ha borrado correctamente </p>";
        } else {
            echo "<p> Ha habido un fallo en el borrado </p>";
        }
    }else{
        echo "<p> El videojuego no existe </p>";
    }
    echo "<a href=\"../../index.php\">Volver</a>";
}
?>