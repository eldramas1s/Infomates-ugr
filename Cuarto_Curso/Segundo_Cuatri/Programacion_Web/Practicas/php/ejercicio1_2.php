<?php
    //Equipos de formula 1 y sus puntos
    $formula["Mercedes AMG"] = 125;
    $formula["Ferrari"] = 100;
    $formula["McLaren"] = 65;

    echo "<h4> Acceso por clave </h4>";
    foreach ($formula as $team => $points){
        echo "$team : $points <br/>\n";
    }
?>

<?php
    $frutas[] = 'manzana';
    $frutas[] = 'pera';
    $frutas[] = 'sandía';

    echo "<h4> Acceso por iterador </h4>";

    for ($i=0; $i<3; $i++){
        echo "$frutas[$i],";
    }