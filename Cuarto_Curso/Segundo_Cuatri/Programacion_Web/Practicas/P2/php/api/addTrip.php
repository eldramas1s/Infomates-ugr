<?php

    require_once __DIR__ . '/../model/forms.php';

    header('Content-Type: application/json');

    //Obtenemos la información
    $data = json_decode(file_get_contents("php://input"),true);

    //Si no se han recibido datos, enviamos un error
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

    // Si el manejo del formulario ha dado error, enviamos los errores
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