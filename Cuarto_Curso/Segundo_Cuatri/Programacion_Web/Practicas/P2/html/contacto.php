<?php
    require_once '../php/utils.php';
    session_start();
?>
<!DOCTYPE html>
<html lang="es">
    <head>
        <meta charset="UTF-8">
        <meta name="viewport" content="width=device-width, initial-scale=1.0">
        <link rel="stylesheet" href="../css/style.css">
        <link rel="stylesheet" href="../css/contacto.css">
        <link rel="stylesheet" href="../css/form.css">
        <title>Azimut Viajes | Contacto</title>
    </head>
    <body>
        <?php putHeader(1); ?>
        <main id="basicMain">
            <section id="sobreMi"> 
                
                <h2>Algunos datos</h2>
                <img src="../imagenes/fotoDesarrollador.jpeg" alt="Foto del desarrollador">
                <ul>
                    <li>Nombre: Lucas Hidalgo Herrera</li>
                    <li>Fecha de nacimiento: 10 de noviembre de 2004</li>
                    <li>Email: e.lucashidalgo@go.ugr.es</li>
                    <li>Grado: Ingeniería Informática y Matemáticas</li>
                    <li>Dirección: Calle Gonzalo Gallas, 23</li>
                    <li>Estudios musicales: Grado Medio en la especialidad de Trompeta y Composición</li>
                </ul>
                
            </section>
        </main>
        <?php putFooter(1); ?>
    </body>
</html>