<?php

session_start();

// Vaciamos la sesion para eliminar cualquier dato del usuario

$_SESSION = [];

// Destruimos la sesion para asegurarnos de que se cierre la sesion
session_destroy();

header('Location: ../index.php');

//Detenemos la ejecucion del script, php no lo hace tras una redireccion
exit();
?>
 