<!DOCTYPE html>
<html lang="en">
    <head>
        <meta charset="UTF-8">
        <meta name="viewport" content="width=device-width, initial-scale=1.0">
        <title>Document</title>
    </head>
    <body>
        <form action="consolas.php" method="post">
            <label for="consolasFavoritas[]">&iquest;Cu&aacute;les son tus
                consolas
                favoritas?</label>
            <select name="consolasFavoritas[]" id="consolasFavoritas" size="3"
                multiple="multiple">
                <option value="xbox">XBox</option>
                <option value="psp">PSP</option>
                <option value="wii">Wii</option>
            </select>
            <label for="comunicacionesTelefonicas">
                &iquest;Quieres recibir comunicaciones telef&oacute;nicas?
            </label>
            <input type="checkbox" name="comunicaciones[]"
                id="comunicacionesTelefonicas"
                value="comunicacionesTelefonicas" />
            <label for="comunicacionesCorreo">&iquest;Quieres recibir
                comunicaciones por
                correo?</label>
            <input type="checkbox" name="comunicaciones[]"
                id="comunicacionesCorreo"
                value="comunicacionesCorreo" />
            <button type="submit">Enviar</button>
        </form>
        <?php
        $consolasFavoritas = "";
        $comunicaciones = "";
        if ( !empty( $_POST["consolasFavoritas"] ) ) {
        foreach ( $_POST["consolasFavoritas"] as $consola ) {
        $consolasFavoritas .= $consola . ", ";
        }
        // También se podría acceder mediante $_POST["consolasFavoritas"][0],
        // $_POST["consolasFavoritas"][1] y $_POST["consolasFavoritas"][2].
        }
        if ( isset( $_POST["comunicaciones"] ) ) {
        foreach ( $_POST["comunicaciones"] as $comunicacion ) {
        $comunicaciones .= $comunicacion . ", ";
        }
        }
        echo "$consolasFavoritas <br /> $comunicaciones <br />";
        ?>
    </body>
</html>