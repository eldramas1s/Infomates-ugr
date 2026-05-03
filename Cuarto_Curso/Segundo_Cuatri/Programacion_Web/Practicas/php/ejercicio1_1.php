<?php
    echo "Hola caracola", 134;
    echo "Adiós","bye";
    echo '<p>Nueva \n linea</p>';
    echo "<p>Nueva <br/>\n linea </p>";

    $edad = 21;
    $precio = 343.45;
    $nombre = "Pepe";
    $nombre2 = $nombre;
    print_r($nombre);
    echo $nombre2;
    $pseudonimo= & $nombre2;

    $temperatura = 33;
?>

<p> La temperatura es de <?php echo $temperatura; ?> grados. </p>
<?php echo "<p>La temperatura es de ", $temperatura, "grados. (hecho con echo)</p>";?>
<?php echo "<p>La temperatura es de $temperatura grados. (Otra forma con echo)</p>";?>

<?php
    $numero=12321.666;
    echo number_format($numero,2),"<br/>";
    echo number_format($numero,2,",",".");
?>

<?php
    $nombreVariable = "temperatura";
    $$nombreVariable = 30.5;
?>

<?php
    define('PI', 3.1415);
    const TIEMPO = "soleado";
?>

<?php  
    $usuario = $_GET['usuario'] ?? 'Invitado';
    echo $usuario;
    $nombre = null;
    $nombre ??= 'Anonimo';
    echo $nombre;
?>

<!DOCTYPE html>
<html lang="es">
<head>
    <meta charset="UTF-8">
    <title>Menú</title>
</head>
<body>
    <?php
        $precio1 = 2.99;
        $precio2 = 5.00;
        $precio3 = 4.00;
        $precio4 = 3.50;

        const IVA = 0.21;
    ?>
    <ul>
        <li>Primero = Ensalada César (<?php echo number_format($precio1,2)," €"; ?>)</li>
        <li>Segundo = Langosta a la plancha (<?php echo number_format($precio1,2)," €"; ?>)</li>
        <li>Tercero = Solomillo en salsa de almendras (<?php echo number_format($precio1,2)," €"; ?>)</li>
        <li>Postre =  Tarte de queso de la casa (<?php echo number_format($precio1,2)," €"; ?>)</li>
    </ul>
    <p>Total del menú = <?php 
        $total = $precio1+$precio2+$precio3+$precio4;
        echo number_format( $total + IVA*$total,2)," €" 
        ?></p>

</body>
</html>

