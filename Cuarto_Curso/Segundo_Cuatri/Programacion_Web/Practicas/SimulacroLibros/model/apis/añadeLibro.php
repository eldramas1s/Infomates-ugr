<?php

require_once __DIR__.'/../libro.php';

//Haría mas comprobaciones pero voy justo de tiempo
if(isset($_GET['titulo']) && $_GET['titulo']!==""){
    if(Libro::exists($_GET['titulo'],$_GET['anio'],$_GET['genero'],$_GET['autor'])){
        echo "<p> Ya existe ese libro </p>";
    }else{
        $result=Libro::create($_GET['titulo'],$_GET['anio'],$_GET['genero'],$_GET['autor']);
        if($result){
            echo "<p> Creado correctamente </p>";
        }else{
            echo "<p> No se ha podido crear </p>";
        }
    }   
}
?>