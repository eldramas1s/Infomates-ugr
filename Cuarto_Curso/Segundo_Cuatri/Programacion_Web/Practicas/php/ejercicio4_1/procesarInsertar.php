<?php
include 'db.php';

if ($_SERVER['REQUEST_METHOD'] == 'POST') {
    try{
        $sql = "INSERT INTO Libros (isbn, titulo, autor, editorial, numPaginas, anio) 
            VALUES (?, ?, ?, ?, ?, ?)";
        $stmt= $connection->prepare($sql);
        $stmt->execute([
            $_POST['isbn'], $_POST['titulo'], $_POST['autor'], 
            $_POST['editorial'], $_POST['numPaginas'], $_POST['anio']
        ]);
        header("Location: index.php"); // Vuelve a la lista
    }catch (Exception $e) {
        die("Error al insertar: " . $e->getMessage());
    }
}
?>