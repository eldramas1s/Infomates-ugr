<?php

require_once __DIR__.'/DataObject.php';

class Videojuego extends DataObject{

    protected $data = [
        "id"=>0,
        "titulo"=>"",
        "plataforma"=>"",
        "desarrollador"=>"",
        "anio"=>0
    ];

    public static function exists($id){
        $conn = parent::connect();
        $query = "SELECT * FROM videojuegos WHERE id=?";

        try{
            $stmt = $conn->prepare($query);
            $stmt->execute([$id]);
            $result=$stmt->fetchAll(PDO::FETCH_ASSOC);
            return count($result)>0;
        }catch(PDOException $e){
            die("Videojuego::exists -> " . $e->getMessage());
        }
    }

    public static function existsWithData($data){
        $conn = parent::connect();
        $query = "SELECT * FROM videojuegos WHERE titulo=? AND plataforma=? AND anio=? AND desarrollador=?";

        try{
            $stmt = $conn->prepare($query);
            $stmt->execute([$data['titulo'],$data['plataforma'],$data['anio'],$data['desarrollador']]);
            $result=$stmt->fetchAll(PDO::FETCH_ASSOC);
            return count($result)>0;
        }catch(PDOException $e){
            die("Videojuego::exists -> " . $e->getMessage());
        }
    }

    public static function create($data){
        $conn = parent::connect();
        $query = "INSERT INTO videojuegos(titulo,plataforma,desarrollador,anio) VALUES(?,?,?,?)";

        try{
            $stmt = $conn->prepare($query);
            return $stmt->execute([$data['titulo'],$data['plataforma'],$data['desarrollador'],$data['anio']]);
        }catch(PDOException $e){
            die("Videojuego::create -> " . $e->getMessage());
        }
    }

    public static function modify($data){
        $conn = parent::connect();
        $query = "UPDATE videojuegos SET titulo=?,plataforma=?,desarrollador=?,anio=? WHERE id=?";

        try{
            $stmt = $conn->prepare($query);
            return $stmt->execute([$data['titulo'],$data['plataforma'],$data['desarrollador'],$data['anio'],$data['id']]);
        }catch(PDOException $e){
            die("Videojuego::modify -> " . $e->getMessage());
        }
    }

    public static function delete($id){
        $conn = parent::connect();
        $query = "DELETE FROM videojuegos where id=?";

        try{
            $stmt = $conn->prepare($query);
            return $stmt->execute([$id]);
        }catch(PDOException $e){
            die("Videojuego::create -> " . $e->getMessage());
        }
    }

    public static function getAll(){
        $conn = parent::connect();
        $query = "SELECT * FROM videojuegos";

        try{
            $stmt = $conn->prepare($query);
            $stmt->execute();
            return $stmt->fetchAll(PDO::FETCH_ASSOC);
        }catch(PDOException $e){
            die("Videojuego::create -> " . $e->getMessage());
        }
    }

    public static function getOne($id){
        $conn = parent::connect();
        $query = "SELECT * FROM videojuegos WHERE id=?";

        try{
            $stmt = $conn->prepare($query);
            $stmt->execute([$id]);
            return $stmt->fetch(PDO::FETCH_ASSOC);
        }catch(PDOException $e){
            die("Videojuego::create -> " . $e->getMessage());
        }
    }


}
