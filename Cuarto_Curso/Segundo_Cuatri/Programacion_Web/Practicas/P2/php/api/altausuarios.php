<?php

require_once '../forms.php';

header('Content-Type: application/json');

$data = json_decode(file_get_contents("php://input"), true);

if (!$data) {
    echo json_encode([
        "success" => false,
        "message" => "No se han recibido datos"
    ]);
    exit;
}

$form = new FormSignUp();
$status = $form->handle($data);

if (!$status) {
    echo json_encode([
        "success" => false,
        "errors" => $form->getErrors()
    ]);
    exit;
}

exit;
?>