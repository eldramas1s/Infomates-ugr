<?php
/**
 * Escribe el avatar mas el boton de cierre de sesion
 *
 * @param [type] $initial
 * @param [type] $nickName
 * @return void 
 */
function putAvatar($initial, $nickName, $index = false) {
    $html = '<div id="userMenu">
        <div id="avatar">' . htmlspecialchars($initial ?? '') . '</div>
        <div id="nickName">' . htmlspecialchars($nickName ?? '') . '</div>';

    if ($index) {
        $html.= '<form id="logoutForm" method="post" action="./php/logout.php">
            <button type="submit" id="logoutbtn">Log Out</button>
        </form>
        </div>';
    } else{
        $html.= '<form id="logoutForm" method="post" action="../php/logout.php">
            <button type="submit" id="logoutbtn">Log Out</button>
        </form>
        </div>';
    }

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
        <a href="./html/altausuarios.php"> Sign Up</a>
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

?>

