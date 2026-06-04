<?php
    require_once __DIR__.'/../model/trips.php';

    // Establecemos el tipo de contenido a JSON
    header('Content-Type: application/json');

    //Obtenemos los datos por el canal de input
    $data = json_decode(file_get_contents("php://input"),true);

    //Si no se han recibido datos, enviamos un error
    if(!$data){
        echo json_encode([
            "success"=> false,
            "message" => "No se han recibido datos"
        ]);
        exit;
    }

    //Si los hemos recibido, tenemos que borrar el viaje
    $result = Trip::delete($data['continent'],$data['country'],$data['place'],$data['departureDate'],$data['returnDate']);

    //Enviamos el resultado del borrado
    echo json_encode([
        "success"=>$result,
        "message"=>($result)? "Se ha borrado correctamente" : "Ha habido un problema en el borrado"
    ]);
    exit;
?>