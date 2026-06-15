<?php

require_once __DIR__ . '/../Videojuegos.php';

if (isset($_POST['titulo']) && $_POST['titulo'] !== "") {
    $data = [
        "titulo" => $_POST['titulo'],
        "desarrollador" => $_POST['desarrollador'],
        "plataforma" => $_POST['plataforma'],
        "anio" => $_POST['anio']
    ];
    if (!Videojuego::existsWithData($data)) {
        $result = Videojuego::create($data);
        if ($result) {
            echo "<p> Se ha creado correctamente </p>";
        } else {
            echo "<p> Ha habido un fallo en la creacion </p>";
        }
    }else{
        echo "<p> El videojuego ya existe </p>";
    }
    echo "<a href=\"../../index.php\">Volver</a>";
}
?>
