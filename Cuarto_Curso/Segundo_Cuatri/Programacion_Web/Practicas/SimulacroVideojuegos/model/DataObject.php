<?php

require_once __DIR__.'/config.php';

abstract class DataObject{
    protected $data = array();

    static public function connect(){
        try{
            $conn = new PDO(DB_DSN,DB_USER,DB_PASS,[
                PDO::ATTR_DEFAULT_FETCH_MODE => PDO::FETCH_ASSOC,
                PDO::ATTR_ERRMODE => PDO::ERRMODE_EXCEPTION
            ]);

            return $conn;

        }catch(PDOException $e){
            die("Error de conexion: ". $e->getMessage());
        }
    }

    static public function disconnect($conn){
        $conn=null;
    }
}