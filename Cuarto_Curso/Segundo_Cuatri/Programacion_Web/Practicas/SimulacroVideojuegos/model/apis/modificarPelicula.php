<?php

require_once __DIR__ . '/../Videojuegos.php';

if (isset($_POST['id']) && $_POST['id'] !== "") {
    $data = [
        "id"=> $_POST['id'],
        "titulo" => $_POST['titulo'],
        "desarrollador" => $_POST['desarrollador'],
        "plataforma" => $_POST['plataforma'],
        "anio" => $_POST['anio']
    ];
    if (Videojuego::exists($data['id'])) {
        $result = Videojuego::modify($data);
        if ($result) {
            echo "<p> Se ha modificado correctamente </p>";
        } else {
            echo "<p> Ha habido un fallo en la modificacion </p>";
        }
    }else{
        echo "<p> El videojuego no existe </p>";
    }
    echo "<a href=\"../../index.php\">Volver</a>";
}
?>