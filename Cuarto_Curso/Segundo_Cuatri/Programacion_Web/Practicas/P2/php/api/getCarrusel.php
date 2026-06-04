<?php
    require_once __DIR__."/../model/trips.php";

    // Establecemos el tipo de contenido a JSON
    header('Content-Type: application/json');

    //Obtenemos los viajes para el carrusel
    $trips = InfoTrips::getForCarrusel();

    //Si no hay viajes, enviamos un mensaje de error
    if(empty($trips)){
        echo json_encode([
            "success"=>false,
            "message" => "Ups! Parece que no hay viajes ;)"
        ]);
        exit;
    }
    else{
        //Si no ponemos & no se modifica el campo, en php se toman copias en los foreach
        //Si el campo de descripción corta está vacío, le ponemos un mensaje por defecto
        foreach($trips as &$trip){
            if(empty($trip['sortDesc'])){
                $trip['sortDesc'] = "¡Ven a descubrir " . $trip['place'] . " con Azimut Viajes! Una experiencia inolvidable.";
            }
        }

        //Enviamos los viajes
        echo json_encode([
            "success"=>true,
            "data"=>$trips
        ]);
        exit;
    }
?>