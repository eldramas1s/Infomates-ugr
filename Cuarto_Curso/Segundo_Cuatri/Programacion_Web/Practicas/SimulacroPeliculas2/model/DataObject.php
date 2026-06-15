<?php

require_once __DIR__.'/config.php';

abstract class DataObject{
    protected $data=array([]);

    public static function conect(){
        try{
            
            $conn = new PDO(DB_DSN,DB_USER,DB_PASS,[
                PDO::ATTR_ERRMODE => PDO::ERRMODE_EXCEPTION,
                PDO::ATTR_DEFAULT_FETCH_MODE => PDO::FETCH_ASSOC
            ]);
            
            return $conn;
        }catch(PDOException $e){
            die("Error al conectar: ".$e->getMessage());
        }
    }

    public static function disconnect($conn){
        $conn=null;
    }
}
?>