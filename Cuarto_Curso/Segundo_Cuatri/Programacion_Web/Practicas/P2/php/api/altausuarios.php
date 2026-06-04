<?php

require_once __DIR__ . '/../model/forms.php';

// Establecemos el tipo de contenido a JSON
header('Content-Type: application/json');

// Obtenemos la información enviada en el cuerpo de la solicitud
$data = json_decode(file_get_contents("php://input"), true);

// Si no se han recibido datos, enviamos un error
if (!$data) {
    echo json_encode([
        "success" => false,
        "message" => "No se han recibido datos"
    ]);
    exit;
}

// Si existen los datos, procesamos el formulario de registro
$form = new FormSignUp();
$status = $form->handle($data);

// Si el manejo del formulario ha dado error, enviamos los errores
if (!$status) {
    echo json_encode([
        "success" => false,
        "errors" => $form->getErrors()
    ]);
    exit;
}

// Enviamos el éxito si no hay error
echo json_encode([
    "success" => true,
    "message" => "¡Usuario registrado correctamente!"
]);

exit;
?>