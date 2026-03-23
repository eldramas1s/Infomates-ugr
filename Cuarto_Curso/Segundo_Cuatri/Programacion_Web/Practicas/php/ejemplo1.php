<?php
$edad = 21;
$precio = 343.45;
$nombre = 'Pepe';
$nombre2 = $nombre;
print_r($nombre);
echo $nombre2;
$pseudonimo = &$nombre2; // Asignación de una variable por referencia.
$temperatura = 25;
?>
<?php
$nombre_de_la_variable = 'temperatura';
$$nombre_de_la_variable = 30.5;
/* Esto implicaría que $temperatura=30.5; */
?>

<p> La temperatura es de <?php echo $temperatura; ?> grados. </p>
<!-- Ó -->
<?php
echo '<p>La temperatura es de ', $temperatura, ' grados. </p>';
?>
<!-- Ó -->
<?php
echo "<p>La temperatura es de $temperatura grados. </p>";
?>

<?php
$numero = 12321.666;
/* Formatea el número con dos decimales y '.' y ',' como separadores decimales y miles */
echo number_format($numero, 2), '<br/>';
/* Formatea el número con 2 decimales y con él ',' y de decimales y la '.' de miles */
echo number_format($numero, 2, ',', '.');
?>

<?php
define('PI', 3.1415);
define('TIEMPO', 'soleado');
const PI_CONST = 3.1415;
?>

<?php
$usuario = $_GET['usuario'] ?? 'Invitado';
echo $usuario; // Si no existe "usuario", muestra "Invitado".
// O también
$nombre = null;
$nombre ??= 'Anónimo';
echo $nombre; // "Anónimo"
?>

<?php
try {
$resultado= $numero/0;
} catch (DivisionByZeroError $error)
{error_log(" Se ha producido un error en la condición",3,"/temp/err_log");
/* O incluso enviar al administrador un mensaje de correo electrónico:*/
error_log("Se ha producido un error en la condición",1,"admin@midominio.es");
exit();
}
try {
throw new Exception("This is an exception");
} catch (Throwable $e) {
echo $e->getMessage();
}
try {
require "index3.php";
} catch (ParseError $e) {
echo $e->getMessage();
}
?>