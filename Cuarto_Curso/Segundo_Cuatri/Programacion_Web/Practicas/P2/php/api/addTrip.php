<?php

    require_once __DIR__ . '/../forms.php';

    header('Content-Type: application/json');

    //Obtenemos la información
    $data = json_decode(file_get_contents("php://input"),true);

    if(!$data){
        echo json_encode([
            "success" => false,
            "message" => "No se han recibido datos"
        ]);
        exit;
    }

    //Si existen los datos, procesamos
    $form = new FormAddTrip();
    $status = $form->handle($data);

    if(!$status){
        echo json_encode([
            "success"=>false,
            "errors"=>$form->getErrors()
        ]);
        exit;
    }

    //Enviamos el exito si no hay error
    echo json_encode([
        "success" => true,
        "message" => "¡Viaje añadido correctamente"
    ]);
    exit;
?>