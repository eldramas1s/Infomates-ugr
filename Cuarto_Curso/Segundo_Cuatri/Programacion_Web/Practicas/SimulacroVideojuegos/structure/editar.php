<?php
require_once  __DIR__ . '/../model/Videojuegos.php';
?>
<!DOCTYPE html>
<html lang="en">

<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <link rel="stylesheet" href="../style/style.css">
    <title>Editar</title>
</head>

<body>
    <header>
        <h1>Añade tu película favorita</h1>
    </header>
    <main id="mainForms">
        <?php if (isset($_GET['id']) && is_numeric($_GET['id'])): ?>
            <?php if (Videojuego::exists($_GET['id'])): ?>
                <?php $vj = Videojuego::getOne($_GET['id']);?>
                <form action="../model/apis/modificarPelicula.php" method="post">
                    <input type="text" hidden name="id" value=<?php echo $_GET['id']; ?>>
                    <fieldset class="field">
                        <label for="titulo">Titulo:</label>
                        <input type="text" name="titulo" id="titulo" value="<?php echo $vj['titulo'];?>">
                    </fieldset>
                    <fieldset class="field">
                        <label for="plataforma">Plataforma:</label>
                        <input type="text" name="plataforma" id="plataforma" value="<?php echo $vj['plataforma'];?>">
                    </fieldset>
                    <fieldset class="field">
                        <label for="desarrollador">Desarrollador:</label>
                        <input type="text" name="desarrollador" id="desarrollador" value="<?php echo $vj['desarrollador'];?>">
                    </fieldset>
                    <fieldset class="field">
                        <label for="anio">Año:</label>
                        <input type="number" step="1" min="0" name="anio" id="anio" value="<?php echo $vj['anio'];?>">
                    </fieldset>
                    <div class="divButtons">
                        <button class="button" type="submit">Enviar</button>
                        <button class="button" type="reset">Borrar Todo</button>
                    </div>
                </form>
                <a class="button" href="../index.php">Home</a>
                <script src="../frontEnd/formValidator.js" type="text/javascript"></script>
            <?php endif; ?>
        <?php else: ?>
            <p>No se tiene ningun identificador de pelicula</p>
        <?php endif; ?>
    </main>

    <footer>
        <p class="date"> <?php echo date('Y-m-d'); ?></p>
        <p class="autor"> Lucas Hidalgo Herrera</p>
    </footer>

</body>

</html>