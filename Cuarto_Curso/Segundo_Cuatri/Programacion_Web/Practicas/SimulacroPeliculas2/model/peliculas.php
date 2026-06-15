<?php

require_once __DIR__.'/DataObject.php';

class Pelicula extends DataObject{
    protected $data = [
        "id"=>0,
        "titulo"=>"",
        "director"=>"",
        "genero"=>"",
        "anio"=>0
    ];


    public static function exists($data){
        $conn = parent::conect();
        $query = "SELECT * FROM " . TABLA_PELICULAS . " WHERE titulo=? AND director=? AND genero=? AND anio=?";

        try{
            $stmt = $conn->prepare($query);
            $stmt->execute([$data['titulo'],$data['director'],$data['genero'],$data['anio']]);
            $result = $stmt->fetchAll(PDO::FETCH_ASSOC);
            return count($result)>0;
        }catch(PDOException $e){
            die('Pelicula::exists :'.$e->getMessage());
        }
    }

    public static function existsById($id){
        $conn = parent::conect();
        $query = "SELECT * FROM " . TABLA_PELICULAS . " WHERE id=?";

        try{
            $stmt = $conn->prepare($query);
            $stmt->execute([$id]);
            $result = $stmt->fetchAll(PDO::FETCH_ASSOC);
            return count($result)>0;
        }catch(PDOException $e){
            die('Pelicula::exists :'.$e->getMessage());
        }
    }

    public static function getAll(){
        $conn = parent::conect();
        $query = "SELECT * FROM " . TABLA_PELICULAS;

        try{
            $stmt = $conn->prepare($query);
            $stmt->execute();
            $result = $stmt->fetchAll(PDO::FETCH_ASSOC);
            return $result;
        }catch(PDOException $e){
            die('Pelicula::getAll :'.$e->getMessage());
        }
    }

    public static function create($data){
        $conn = parent::conect();
        $query = "INSERT INTO " . TABLA_PELICULAS ." (titulo,genero,anio,director) VALUES(?,?,?,?)";

        try{
            $stmt = $conn->prepare($query);
            return $stmt->execute([$data['titulo'],$data['genero'],$data['anio'],$data['director']]);
        }catch(PDOException $e){
            die('Pelicula::getAll :'.$e->getMessage());
        }
    }

    public static function delete($id){
        $conn = parent::conect();
        $query = "DELETE FROM " . TABLA_PELICULAS . " WHERE id=?";

        try{
            $stmt = $conn->prepare($query);
            return $stmt->execute([$id]);
        }catch(PDOException $e){
            die('Pelicula::exists :'.$e->getMessage());
        }
    }

    public static function modify($data){
        $conn = parent::conect();
        $query = "UPDATE " . TABLA_PELICULAS . " SET titulo=?, director=?, genero=?, anio=? WHERE id=?";

        try{
            $stmt = $conn->prepare($query);
            return $stmt->execute([$data['titulo'],$data['director'],$data['genero'],$data['anio'],$data['id']]);
        }catch(PDOException $e){
            die('Pelicula::exists :'.$e->getMessage());
        }
    }

    public static function getById($id){
        $conn = parent::conect();
        $query = "SELECT * FROM " . TABLA_PELICULAS . " WHERE id=?";

        try{
            $stmt = $conn->prepare($query);
            $stmt->execute([$id]);
            $result=$stmt->fetch(PDO::FETCH_ASSOC);
            return $result;
        }catch(PDOException $e){
            die('Pelicula::exists :'.$e->getMessage());
        }
    }
}