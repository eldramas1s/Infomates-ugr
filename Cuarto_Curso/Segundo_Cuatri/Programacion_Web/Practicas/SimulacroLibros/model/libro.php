<?php

require_once __DIR__.'/DataObject.php';

class Libro extends DataObject
{

    protected $data = array([
        "id" => 0,
        "titulo" => "",
        "autor" => "",
        "anio" => 2000,
        "genero" => ""
    ]);

    public static function exists($titulo, $anio, $genero, $autor)
    {
        $conn = parent::connect();
        $query = "SELECT * FROM libros where titulo = ? AND anio = ? AND genero=? AND autor=?";

        try {
            $stmt = $conn->prepare($query);
            $stmt->execute([$titulo, $anio, $genero, $autor]);
            $result = $stmt->fetchAll(PDO::FETCH_ASSOC);
            return count($result) > 0;
        } catch (PDOException $e) {
            die("Libro::create " . $e->getMessage());
        }
    }

    public static function create($titulo, $anio, $genero, $autor)
    {
        $conn = parent::connect();
        $query = "INSERT INTO libros(titulo,anio,genero,autor) VALUES (?,?,?,?)";

        try {
            $stmt = $conn->prepare($query);
            return $stmt->execute([$titulo, $anio, $genero, $autor]);
        } catch (PDOException $e) {
            die("Libro::create " . $e->getMessage());
        }
    }

    public static function modify($data)
    {
        $conn = parent::connect();
        $query = "UPDATE libros SET titulo=? AND anio=? AND genero=? ANd autor=? WHERE id=?";

        if (Libro::exists($data['titulo'], $data['anio'], $data['genero'], $data['autor'])) {
            try {
                $stmt = $conn->prepare($query);
                return $stmt->execute([$data['titulo'], $data['anio'], $data['genero'], $data['autor'], $data['id']]);
            } catch (PDOException $e) {
                die("Libro::modify " . $e->getMessage());
            }
        } else {
            return false;
        }
    }

    public static function delete($data)
    {
        $conn = parent::connect();
        $query = "DELETE FROM libros WHERE id=?";

        if (Libro::exists($data['titulo'], $data['anio'], $data['genero'], $data['autor'])) {
            try {
                $stmt = $conn->prepare($query);
                return $stmt->execute([$data['id']]);
            } catch (PDOException $e) {
                die("Libro::delete " . $e->getMessage());
            }
        } else {
            return false;
        }
    }


    public static function getAll(){
        $conn = parent::connect();
        $query = "SELECT * FROM libros";

        try {
            $stmt = $conn->prepare($query);
            $stmt->execute();
            $result = $stmt->fetchAll(PDO::FETCH_ASSOC);
            return $result;
        } catch (PDOException $e) {
            die("Libro::getAll " . $e->getMessage());
        }
    }

    public static function getOne($id){
        $conn = parent::connect();
        $query = "SELECT * FROM libros WHERE id=?";

        try {
            $stmt = $conn->prepare($query);
            $stmt->execute([$id]);
            $result = $stmt->fetch();
            return $result;
        } catch (PDOException $e) {
            die("Libro::getAll " . $e->getMessage());
        }
    }


    public function getDatos(){
        return $this->data;
    }
}
