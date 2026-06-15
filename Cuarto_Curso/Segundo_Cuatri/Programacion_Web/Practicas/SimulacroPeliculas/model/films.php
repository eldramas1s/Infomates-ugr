<?php

require_once __DIR__.'/../utilities/conection.php';
require_once __DIR__.'/config.php';

class film{
    protected $data = array([
        "title"=>"",
        "version"=>1,
        "language"=>'english',
        "price"=>0.00,
        "time"=>1.0
    ]);

    
    public static function getAll(){
        $conn = connect();
        $query = "SELECT f.title, f.version, f.language,f.price, f.time  from " . TABLA_FILMS . " f JOIN " . TABLA_STREAMS . " s
                    on f.title = s.title and f.version = s.version and f.language = s.language
                where s.fecha_stream >= NOW()";

        try{

            $stmt = $conn->prepare($query);
            $stmt->execute();
            return $stmt->fetchAll(PDO::FETCH_ASSOC);

        }
        catch(PDOException $e){
            error_log("film::getAll()" . $e->getMessage());
            return [];
        }
    }


    public static function getSearched(string $title, int $version, string $language='english'){
        $conn = connect();
        $query = "SELECT f.title, f.version, f.language from " . TABLA_FILMS . " f JOIN " . TABLA_STREAMS . " s
                    on f.title = s.title and f.version = s.version and f.language = s.language
                where s.fecha_stream >= NOW()";

        $params = [];
        $conditions = [];

        if($title !== -1 || $title !== '-1'){
            $params[]=$title;
            $conditions[]=" and f.title=?";
        }

        if($version !== -1 || $version !== '-1'){
            $params[]=$version;
            $conditions[]=" and f.version=?";
        }

        if($language !== -1 || $language !== '-1'){
            $params[]=$language;
            $conditions[]=" and f.language=?";
        }

        foreach($conditions as $condition){
            $query .= $condition;
        }

        try{
            $stmt = $conn -> prepare($query);
            $stmt -> execute($params);
            return $stmt->fetchAll(PDO::FETCH_ASSOC);
        }
        catch(PDOException $e){
            error_log("film::getSearched()" . $e->getMessage());
            return [];
        }
    }
}

?>
