<!DOCTYPE html>
<html lang="en">

<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <link rel="stylesheet" href="../style/style.css">
    <title>Añadir</title>
</head>

<body>
    <header>
        <h1>Añade tu película favorita</h1>
    </header>
    <main id="mainForms">
        <form id="formVj" action="../model/apis/añadirPelicula.php" method="post">
            <fieldset class="field">
                <label for="titulo">Titulo:</label>
                <input type="text" name="titulo" id="titulo">
            </fieldset>
            <fieldset class="field">
                <label for="plataforma">Plataforma:</label>
                <input type="text" name="plataforma" id="plataforma">
            </fieldset>
            <fieldset class="field">
                <label for="desarrollador">Desarrollador:</label>
                <input type="text" name="desarrollador" id="desarrollador">
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
        <a class="button" href="../index.php">Home</a>
        <script src="../frontEnd/formValidator.js" type="text/javascript"></script>
    </main>

    <footer>
        <p class="date"> <?php echo date('Y-m-d');?></p>
        <p class="autor"> Lucas Hidalgo Herrera</p>
    </footer>

</body>

</html>