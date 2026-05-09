<?php include 'db.php'; ?>
<!DOCTYPE html>
<html>
<head><title>Biblioteca</title></head>
<body>
    <h1>Libros en la Base de Datos</h1>
    <a href="nuevoLibro.php">Añadir Nuevo Libro</a>
    <hr>
    <table>
        <tr>
            <th>ISBN</th>
            <th>Título</th>
            <th>Autor</th>
            <th>Editorial</th>
            <th>Acciones</th>
        </tr>
        <?php
        $stmt = $connection->query("SELECT * FROM Libros");
        while ($row = $stmt->fetch()) {
            echo "<tr>
                <td>{$row['isbn']}</td>
                <td>{$row['titulo']}</td>
                <td>{$row['autor']}</td>
                <td>{$row['editorial']}</td>
                <td><a href='eliminar.php?isbn={$row['isbn']}'>Eliminar</a></td>
            </tr>";
        }
        ?>
    </table>
</body>
</html>