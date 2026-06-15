<?php

require_once __DIR__ . '/../peliculas.php';

if (isset($_POST['titulo']) && $_POST['titulo'] !== "") {
    $data = [
        "titulo" => $_POST['titulo'],
        "genero" => $_POST['genero'],
        "anio" => (int)$_POST['anio'],
        "director" => $_POST['director']
    ];
    if (!Pelicula::exists($data)) {
        $result = Pelicula::create($data);
        if ($result) {
            echo "<p> Creada Correctamente </p>";
            echo "<a class=\"button\" href=\"../../index.php\">Volver</a>";
        } else {
            echo "<p> No se ha podido realizar la operacion </p>";
            echo "<a class=\"button\" href=\"../../index.php\">Volver</a>";
        }
    } else {
        echo "<p> Ya existe esa pelicula </p>";
        echo "<a class=\"button\" href=\"../../index.php\">Volver</a>";
    }
} else {
    echo "<p> NO hay pelicula con la que trabajar </p>";
    echo "<a class=\"button\" href=\"../../index.php\">Volver</a>";
}
