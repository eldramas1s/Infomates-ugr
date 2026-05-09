<?php
$host = 'localhost';
$db   = 'dblucashidalgo_pw2526'; //
$user = 'pwlucashidalgo';      //
$pass = '25lucashidalgo26';    //
$charset = 'utf8mb4';

try {
    $dsn = "mysql:host=$host;dbname=$db;charset=$charset";
    $connection = new PDO($dsn, $user, $pass, [PDO::ATTR_ERRMODE => PDO::ERRMODE_EXCEPTION]);
} catch (\PDOException $e) {
    die("Error de conexión: " . $e->getMessage());
}
?>