<?php
require_once  __DIR__ . '/model/Videojuegos.php';
?>
<!DOCTYPE html>
<html lang="en">

<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <link rel="stylesheet" href="./style/style.css">
    <title>Inicio</title>
</head>

<body>
    <header>
        <h1>Cartelera de Videojuegos</h1>
    </header>
    <main id="mainIndex">
        <section class="cartelera">
            <h2>Todos nuestros videojuegos</h2>
            <?php
            $videojuegos = Videojuego::getAll();
            if (count($videojuegos) > 0):
            ?>
                <?php foreach ($videojuegos as $vj): ?>
                    <?php $bg = "grey";

                    if ((int)$vj['anio'] > 2015) {
                        $bg = "green";
                    } elseif ((int)$vj['anio'] > 2000) {
                        $bg = "yellow";
                    }
                    ?>
                    <article class="cartel" style="background-color: <?php echo $bg; ?>;">
                        <h3><?php echo htmlspecialchars($vj['titulo']) ?> , <?php echo htmlspecialchars($vj['anio']) ?></h3>
                        <img src="" alt=" No tengo imagen">
                        <p class="desarrollador"> Desarrollador: <?php echo htmlspecialchars($vj['desarrollador']); ?></p>
                        <p class="plataforma">Plataforma: <?php echo htmlspecialchars($vj['plataforma']); ?></p>

                        <div class="divButtons">
                            <a class="button edit" href="./structure/editar.php?id=<?php echo $vj['id']; ?>">Editar</a>
                            <a class="button eliminar" href="./model/apis/eliminarPelicula.php?id=<?php echo $vj['id']; ?>">Eliminar</a>
                        </div>
                    </article>
                <?php endforeach; ?>
                <a id="Aniadir" class="button" href="./structure/añadir.php">Añadir</a>
            <?php else: ?>
                <p>No hay videojuegos disponibles.</p>
            <?php endif; ?>

        </section>
        <script src="./frontEnd/deleteScript.js" type="text/javascript"></script>
    </main>

    <footer>
        <p class="date"> <?php echo date('Y-m-d'); ?></p>
        <p class="autor"> Lucas Hidalgo Herrera</p>
    </footer>

</body>

</html>