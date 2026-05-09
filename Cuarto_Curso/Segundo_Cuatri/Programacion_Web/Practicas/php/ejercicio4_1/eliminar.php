<?php
include 'db.php';

if (isset($_GET['isbn'])) {
    $sql = "DELETE FROM Libros WHERE isbn = ?";
    $stmt= $connection->prepare($sql);
    $stmt->execute([$_GET['isbn']]);
}
header("Location: index.php");
?>