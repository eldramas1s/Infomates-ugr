<!DOCTYPE html>
<html lang="en">

<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <link rel="stylesheet" href="../design/style.css">
    <title>Añadir un libro</title>
</head>

<body>
    <header class="header">
        <h1>Añade tu libro</h1>
    </header>
    <main class="mainForms">
        <form name="formNuevo" method="get" action="../model/apis/añadeLibro.php">
            <fieldset class="field">
                <label for="titulo"> Titulo: </label>
                <input type="text" name="titulo" id="titulo">
            </fieldset>
            <fieldset class="field">
                <label for="autor"> Autor: </label>
                <input type="text" name="autor" id="autor">
            </fieldset>
            <fieldset class="field">
                <label for="genero"> Genero: </label>
                <input type="text" name="genero" id="genero">
            </fieldset>
            <fieldset class="field">
                <label for="anio"> Año: </label>
                <input type="number" min="0" step="1" name="anio" id="anio">
            </fieldset>
            <div class="divButons">
                <button id="enviar" class="button" type="submit">Añadir</button>
                <button class="button" type="reset">Borrar Todo</button>
            </div>

        </form>
        <script>
            const regexTitle = /^[A-Za-z0-9 ]+$/;
            button = document.getElementById("enviar")
            button.addEventListener("submit", (e) => {
                e.preventDefault();
                let titulo = document.getElementById("titulo");
                let container = titulo.closest(".field");

                if (!titulo.value || titulo.value.trim() === "" || !regexTitle.test(titulo.value)) {
                    alert("El titulo no es correcto debe ser una cadena alfanumérica");
                    location.reload();
                }
            });
        </script>
    </main>
    <footer class="footer">

        <p class="date"> <?php echo date('Y-m-d'); ?> </p>
        <p class="name"> Lucas Hidalgo Herrera </p>

    </footer>
</body>

</html>