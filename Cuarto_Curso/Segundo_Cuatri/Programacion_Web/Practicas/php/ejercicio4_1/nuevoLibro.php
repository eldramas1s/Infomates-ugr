<!DOCTYPE html>
<html>
<head><title>Nuevo Libro</title></head>
<body>
    <h1>Insertar Registro</h1>
    <form action="procesarInsertar.php" method="POST">
        ISBN: <input type="text" name="isbn" required><br>
        Título: <input type="text" name="titulo" required><br>
        Autor: <input type="text" name="autor" required><br>
        Editorial: <input type="text" name="editorial" required><br>
        Páginas: <input type="number" name="numPaginas" required><br>
        Año: <input type="number" name="anio" required><br>
        <button type="submit">Guardar Libro</button>
    </form>
</body>
</html>
