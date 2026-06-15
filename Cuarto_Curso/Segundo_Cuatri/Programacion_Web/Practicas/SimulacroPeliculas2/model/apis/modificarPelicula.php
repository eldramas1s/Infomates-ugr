<?php

require_once __DIR__ . '/../peliculas.php';

if (isset($_POST['id']) && is_numeric($_POST['id'])) {
    $data = [
        "id" => (int)$_POST['id'],
        "titulo" => $_POST['titulo'],
        "genero" => $_POST['genero'],
        "anio" => (int)$_POST['anio'],
        "director" => $_POST['director']
    ];
    if (Pelicula::existsById($data['id'])) {
        $result = Pelicula::modify($data);
        if ($result) {
            echo "<p> Modificada Correctamente </p>";
            echo "<a class=\"button\" href=\"../../index.php\">Volver</a>";
        } else {
            echo "<p> No se ha podido realizar la operacion </p>";
            echo "<a class=\"button\" href=\"../../index.php\">Volver</a>";
        }
    } else {
        echo "<p> No existe esa pelicula </p>";
        echo "<a class=\"button\" href=\"../../index.php\">Volver</a>";
    }
} else {
    echo "<p> No hay pelicula con la que trabajar </p>";
    echo "<a class=\"button\" href=\"../../index.php\">Volver</a>";
}
