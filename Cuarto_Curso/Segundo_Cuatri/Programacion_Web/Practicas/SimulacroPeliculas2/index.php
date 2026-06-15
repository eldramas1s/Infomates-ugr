<?php
require_once __DIR__ . '/model/peliculas.php';
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
        <h1>Todas las peliculas</h1>
    </header>

    <main id="indexMain">
        <section class="tarjetas">
            <h2>Cartelera</h2>
            <?php
            $peliculas = Pelicula::getAll();
            if (count($peliculas) > 0):
                foreach ($peliculas as $pelicula):
            ?>
                    <article class="tarjeta">

                        <h3> <?php echo htmlspecialchars($pelicula['titulo']); ?>,<?php echo htmlspecialchars($pelicula['anio']); ?></h3>
                        <img src="" alt="No tengo imagen">
                        <p class="director">Director: <?php echo htmlspecialchars($pelicula['director']); ?></p>
                        <p class="genero"> Genero: <?php echo htmlspecialchars($pelicula['genero']); ?></p>

                        <div class="divButtons">
                            <a class="button" href="./structure/editar.php?id=<?php echo $pelicula['id']; ?>">Editar</a>
                            <a class="button" href="./model/apis/eliminarPelicula.php?id=<?php echo $pelicula['id']; ?>">Eliminar</a>
                        </div>
                    </article>

                <?php endforeach; ?>
                <a class="button" href="./structure/añadir.php">Añadir pelicula</a>

            <?php else: ?>
                <p>No hay peliculas por mostrar</p>
            <?php endif; ?>
        </section>
    </main>
    <footer>
        <p class="date">Fecha: <?php echo date('Y-m-d'); ?></p>
        <p class="autor">Lucas Hidalgo Herrera</p>
    </footer>

</body>

</html>