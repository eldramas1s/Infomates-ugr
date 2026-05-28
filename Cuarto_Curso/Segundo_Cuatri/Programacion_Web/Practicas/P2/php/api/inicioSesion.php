<?php
//Necesitamos iniciar la sesión dentro de la api porque 
//el formulario trabaja directamente con $_SESSION
session_start();

require_once '../forms.php';
require_once '../utils.php';

header('Content-Type: application/json');

$data = json_decode(file_get_contents("php://input"),true);

if(!$data){
    echo json_encode([
        "success" => false,
        "message" => "No se han recibido datos"
    ]);
    exit;
}

$form = new FormLogIn();
$status = $form->handle($data);

if(!$status){
    echo json_encode([
        "success" => false,
        "errors" => $form->getErrors()
    ]);
    exit;
}

echo json_encode([
    "success" => true,
    "message" => "¡Usuario loggeado correctamente!"
]);

exit;
?>