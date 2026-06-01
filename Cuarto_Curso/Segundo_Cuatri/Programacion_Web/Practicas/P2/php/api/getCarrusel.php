<?php
    require_once __DIR__."/../trips.php";

    header('Content-Type: application/json');

    $trips = InfoTrips::getForCarrusel();

    if(empty($trips)){
        echo json_encode([
            "success"=>false,
            "message" => "Ups! Parece que no hay viajes ;)"
        ]);
        exit;
    }
    else{
        //Si no ponemos & no se modifica el campo, en php se toman copias en los foreach
        foreach($trips as &$trip){
            if(empty($trip['sortDesc'])){
                $trip['sortDesc'] = "¡Ven a descubrir " . $trip['place'] . " con Azimut Viajes! Una experiencia inolvidable.";
            }
        }

        echo json_encode([
            "success"=>true,
            "data"=>$trips
        ]);
        exit;
    }
?>