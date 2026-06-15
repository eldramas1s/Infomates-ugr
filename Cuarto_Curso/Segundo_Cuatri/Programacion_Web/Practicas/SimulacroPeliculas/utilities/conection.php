<?php

require_once __DIR__.'/../model/config.php';

function connect(){
    try{
        $conexion = new PDO( DB_DSN, DB_USUARIO, DB_CONTRASENIA );
        // Se permite a PHP que mantenga la conexión MySQL abierta para
        // que se emplee en otras partes de la aplicación.
        $conexion->setAttribute( PDO::ATTR_PERSISTENT, true );
        $conexion->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION );
        return $conexion;

    }
    catch(PDOException $e){
        error_log($e->getMessage());
        die("No se pudo conectar con la base de datos");
    }
}

function disconnect($conn){
    $conn=null;
}
?>