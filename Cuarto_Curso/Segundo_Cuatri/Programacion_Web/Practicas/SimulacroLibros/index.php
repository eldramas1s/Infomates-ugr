<?php
require_once __DIR__ . '/model/libro.php';
?>
<!DOCTYPE html>
<html lang="en">

<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <link rel="stylesheet" href="./design/style.css">
    <title>Inicio</title>
</head>

<body>
    <header class="header">
        <h1>Todos los libros</h1>
    </header>

    <main id="indexMain">

        <section class="tarjetas">
            <h2>Libros disponibles</h2>

            <?php
            $libros = Libro::getAll();

            foreach ($libros as $libro):
            ?>

                <article class="tarjeta">
                    <a class="button" href="./structure/editar.php?id=<?php echo $libro['id']; ?>">
                        Modifica
                    </a>
                    <h3><?php echo htmlspecialchars($libro['titulo']); ?>,<?php echo htmlspecialchars($libro['anio']); ?></h3>
                    <img src="" alt="imagen">
                    <p class="autor">Autor: <?php echo htmlspecialchars($libro['autor']); ?> </p>
                    <p class="genero">Genero: <?php echo htmlspecialchars($libro['genero']); ?></p>
                </article>
            <?php endforeach ?>
            <a class="button" href="./structure/nuevo.php">Añadir un libro</a>
        </section>

    </main>

    <footer class="footer">

        <p class="date"> <?php echo date('Y-m-d'); ?> </p>
        <p class="name"> Lucas Hidalgo Herrera </p>

    </footer>

</body>

</html>