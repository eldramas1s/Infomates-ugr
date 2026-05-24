<?php
/**
 * Escribe el avatar del usuario logueado
 *
 * @param string $admin Indica si el usuario es admin
 * @param string $nickName Nickname del usuario
 * @param boolean $index Si se llama desde index.php o no (para rutas relativas)
 * @return void
 */
function putAvatar($admin, $nickName, $level = 0){ 
    $html = '<div id="userMenu">
        <div id="avatar">' ;
    if ($admin == 1) {
        $html.= '&#128187; </div>';
    } else {
        $html.= '&#128100; </div>';
    }
        $html.= '<div id="nickName">' . htmlspecialchars($nickName ?? '') . '</div>
        <form id="logoutForm" method="post" action="';
    if ($level == 0) {
        $html.= './php/logout.php">';
    } else if ($level == 1) {
        $html.= '../php/logout.php">';
    } else {
        $html.= '../../php/logout.php">';
    }
    $html.= '<button type="submit" id="logoutbtn">Log Out</button>
        </form>
        </div>';
    echo $html;
}

/**
 * Escribe el formulario de inicio de sesion
 *
 * @return void
 */
function putsignUpForm(){
    echo '
    <form class="index" method="post" action="./index.php" id="signUpForm" autocomplete="off">
        <label for="nickName">Nickname:*</label>
        <input type="text" id="nickName" name="nickName" required placeholder="menganito68">

        <label for="password">Contraseña:*</label>
        <input type="password" id="password" name="password" required placeholder="Contraseña" pattern="(?=.*[a-z])(?=.*[A-Z])(?=.*\d)(?=.*[$@$!%*?&.]).{8,15}"
                title="Entre 8 y 15 caracteres, al menos una mayúscula, una minúscula, un dígito, un carácter especial y sin espacios. ">

        <button type="submit">Log In</button>
        <a href="./html/altausuarios.html"> Sign Up</a>
    </form>';
}

/**
 * Escribe el formulario de sugerencias (por limpieza de codigo)
 *
 * @return void 
 */
function putFormSugerencias(){
    $html = '<form autocomplete="off" method="post" action="../html/sugerencias.php">
        <h2>Comparte tu experiencia o sugerencia</h2>
        <fieldset id="formularioSugerencias">
            <p>
                <label for="nombre">Nombre</label>
                <input type="text" id="nombre" name="nombre"
                    pattern="([A-Za-z]+( [A-Za-z]+)+)" required>
            </p>
            <p>
                <label for="tipo">Tipo de comentario</label>
                <select id="tipo" name="tipo" required>
                    <option value>Selecciona una opción</option>
                    <option value="experiencia">Experiencia</option>
                    <option value="sugerencia">Sugerencia</option>
                </select>
            </p>
            <p class="Score">
                <input type="radio" id="star5" name="valoracion"
                    class="valoracion" value="5">
                <label for="star5">&starf;</label>

                <input type="radio" id="star4" name="valoracion"
                    class="valoracion" value="4">
                <label for="star4">&starf;</label>

                <input type="radio" id="star3" name="valoracion"
                    class="valoracion" value="3">
                <label for="star3">&starf;</label>

                <input type="radio" id="star2" name="valoracion"
                    class="valoracion" value="2">
                <label for="star2">&starf;</label>

                <input type="radio" id="star1" name="valoracion"
                    class="valoracion" value="1">
                <label for="star1">&starf;</label>
            </p>
            <p>
                <label id="labelComentario"
                    for="comentario">Comentario:</label>
                <textarea id="comentario" name="comentario" rows="10"
                    required></textarea>
            </p>

            <fieldset id="servicios">
                <legend>¿Qué se ofrecía en tu experiencia?</legend>
                <input type="checkbox" id="guia" name="servicios"
                    value="guia">
                <label for="guia">Guía turístico</label>

                <input type="checkbox" id="hotel" name="servicios"
                    value="hotel">
                <label for="hotel">Alojamiento en Hotel</label>

                <input type="checkbox" id="transporte" name="servicios"
                    value="transporte">
                <label for="transporte">Transporte privado</label>

                <input type="checkbox" id="comida" name="servicios"
                    value="comida">
                <label for="comida">Comida incluida</label>
            </fieldset>

            <fieldset id="buttons">
                <button type="submit">Enviar</button>
                <button type="reset">Borrar</button>
            </fieldset>
        </fieldset>
    </form>';
    echo $html;
}

//TODO:DOCUMENTACION

function validateDate($date){
        $validDate = false;
        try {
            // Creamos el objeto DateTime a partir del formato esperado
            $dateObj = DateTime::createFromFormat('Y-m-d', $date);

            // Verificamos que la fecha sea válida (ej: que no sea un 32 de diciembre)
            if ($dateObj && $dateObj->format('Y-m-d') === $date) {
                $validDate = true;
            }
        } catch (Exception $e) {
            $validDate = false;
            error_log('Trips::create fecha inválida');
        }

        return $validDate;
    }
?>

