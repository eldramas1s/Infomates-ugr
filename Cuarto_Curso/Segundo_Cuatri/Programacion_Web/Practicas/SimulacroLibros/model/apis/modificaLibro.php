<?php

require_once __DIR__.'/../libro.php';

//Haría mas comprobaciones pero voy justo de tiempo
if(isset($_GET['titulo']) && $_GET['titulo']!==""){
    if(Libro::exists($_GET['titulo'],$_GET['anio'],$_GET['genero'],$_GET['autor'])){
        echo "<p> Ya existe ese libro </p>";
    }else{
        $data=array([
            "id"=>$_GET['id'],
            "titulo"=>$_GET['titulo'],
            "anio"=>$_GET['anio'],
            "genero" => $_GET['genero'],
            "autor"=> $_GET['autor']
        ]);
        $result=Libro::modify($data);
        if($result){
            echo "<p> Modificado correctamente </p>";
        }else{
            echo "<p> No se ha podido modificar </p>";
        }
    }   
}
?>