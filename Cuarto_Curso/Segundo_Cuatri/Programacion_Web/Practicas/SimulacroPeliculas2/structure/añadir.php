<?php

require_once __DIR__.'/../model/peliculas.php';

?>

<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <link rel="stylesheet" href="../style/style.css">
    <title>Añadir Peliculas</title>
</head>
<body>
    <header>
        <h1>Añade tu película</h1>
    </header>
    <main class="formMain">
        <form id="formPelicula" action="../model/apis/añadirPelicula.php" method="post">
            <fieldset class="field">
                <label for="titulo">Titulo:</label>
                <input type="text" name="titulo" id="titulo">
            </fieldset>

            <fieldset class="field">
                <label for="genero">Género:</label>
                <input type="text" name="genero" id="genero">
            </fieldset>

            <fieldset class="field">
                <label for="director">Director:</label>
                <input type="text" name="director" id="director">
            </fieldset>

            <fieldset class="field">
                <label for="anio">Año:</label>
                <input type="number" step="1" min="0" name="anio" id="anio">
            </fieldset>

            <div class="divButtons">
                <button class="button" type="submit">Enviar</button>
                <button class="button" type="reset">Borrar Todo</button>
            </div>
        </form>
        <script src="../frontEnd/formValidator.js" type="text/javascript"></script>
    </main>
    <footer>
        <p class="date">Fecha: <?php echo date('Y-m-d');?></p>
        <p class="autor">Lucas Hidalgo Herrera</p>
    </footer>
</body>
</html>