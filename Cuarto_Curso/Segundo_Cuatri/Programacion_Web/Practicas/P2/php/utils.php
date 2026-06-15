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
    <form name="signUpForm" class="index" method="post" action="./index.php" id="signUpForm" autocomplete="off">
        <div class="field">
            <label for="nickName">Nickname:*</label>
            <input type="text" id="nickName" name="nickName" placeholder="menganito68">
        </div>

        <div class="field">
            <label for="password">Contraseña:*</label>
            <input type="password" id="password" name="password" placeholder="Contraseña">
        </div>
        
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
    $html = '<form id="formSugerencias" name="formSugerencias" autocomplete="off" method="post" action="../html/sugerencias.php">
        <h2>Comparte tu experiencia o sugerencia</h2>
        <fieldset id="formularioSugerencias">
            <div class="field">
                <label for="tipo">Tipo de comentario</label>
                <input type="text" name="tipo" id="tipo" placeholder="Experiencia|Sugerencia">            
            </div>
            <div class="field">
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
            </div>
            <div class="field">
                <label id="labelComentario"
                    for="comentario">Comentario:</label>
                <textarea id="comentario" name="comentario" rows="10"></textarea>
            </div>

            <fieldset id="servicios">
                <legend>¿Qué se ofrecía en tu experiencia?</legend>
                <div class="field" id="serviciosField">
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
                </div>
            </fieldset>

            <fieldset id="buttons">
                <button type="submit">Enviar</button>
                <button type="reset">Borrar</button>
            </fieldset>
        </fieldset>
    </form>';
    echo $html;
}

/**
 * VAlida que la fecha pasada como argumento sea válida
 *
 * @param [type] $date
 * @return void
 */
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

/**
 * Dado un array y un número positivo, lo agrupa en subarrays de ese numero de elementos o menor
 *
 * @param [type] $array
 * @param [type] $number
 * @return array 
 */
function groupByNumber($array, $number):array{
    if($number <= 1) return $array;

    return array_chunk($array, $number);
}


/**
 * Escribe la cabecera según el nuvel de la jerarquía de archivos en la que nos encontremos
 *
 * @param integer $level nivel de la jerarquía de archivos (0 para index.php, 1 para archivos dentro de html/)
 * @return void 
 */
function putHeader($level=0){
    echo "<header>

        <h1 id=\"nombreDecor\">Azimut Viajes</h1>";

    if($level == 0){
        echo "<img id=\"logoHeader\" src=\"./imagenes/logoAzimut.png\" alt=\"Logotipo Azimut\">";
    } else if($level == 1){
        echo "<img id=\"logoHeader\" src=\"../imagenes/logoAzimut.png\" alt=\"Logotipo Azimut\">";
    }

    //Si no se ha loggeado, pongo el formulario
    if (!isset($_SESSION['loggedIn']) || $_SESSION['loggedIn'] === false) {
        if($level == 0){
            putsignUpForm();
        } else if($level == 1){
            echo '<a href="../index.php" id="Session" style="grid-area: signUpForm; justify-self: center;">Inicia sesión</a>';

        }
    } else { //Si se ha loggeado ponemos el avatar con la inicial del nickname y el boton de cierre de sesión
        putAvatar($_SESSION['admin'], $_SESSION['nickName'], $level);
    }
    
    if($level == 0){
        echo "<nav id=\"menuHeader\">
            <ul>
                <li><a href=\"./index.php\">Inicio</a></li>
                <li><a href=\"./html/viajes.php?page=1\">Viajes</a></li>
                <li><a href=\"./html/viajes_grupo.php\">Viajes en
                        grupo</a></li>
                <li><a href=\"./html/ofertas.php\">Ofertas</a></li>
                <li><a href=\"./html/sobre_agencia.php\">Sobre nuestra
                        agencia</a></li>
                <li><a href=\"./html/sugerencias.php\">Sugerencias</a></li>
            </ul>
        </nav>";
    } else if($level == 1){
        echo "<nav id=\"menuHeader\">
            <ul>
                <li><a href=\"../index.php\">Inicio</a></li>
                <li><a href=\"../html/viajes.php?page=1\">Viajes</a></li>
                <li><a href=\"../html/viajes_grupo.php\">Viajes en
                        grupo</a></li>
                <li><a href=\"../html/ofertas.php\">Ofertas</a></li>
                <li><a href=\"../html/sobre_agencia.php\">Sobre nuestra
                        agencia</a></li>
                <li><a href=\"../html/sugerencias.php\">Sugerencias</a></li>
            </ul>
        </nav>";
    }
    echo "</header>";
}

/**
 * Escribe el pie de página según el nivel de la jerarquía de archivos en la que nos encontremos
 *
 * @param integer $level
 * @return void
 */
function putFooter($level = 0){
    echo "<footer>
        <nav id=\"menuFooter\">
            <ul>";

    if($level == 0){
        echo "<li><a href=\"./html/contacto.php\">Contacte con
                        nosotros</a></li>
              <li><a href=\"./como_se_hizo.pdf\"
                        target=\"_blank\">Cómo se
                        hizo</a></li>";

    } else if($level == 1){
        echo "<li><a href=\"../html/contacto.php\">Contacte con
                        nosotros</a></li>
              <li><a href=\"../como_se_hizo.pdf\"
                        target=\"_blank\">Cómo se
                        hizo</a></li>";
    }
    echo "</ul>
        </nav>
        <p id=\"fechaModificacion\">" . date('Y-m-d') . "</p>
    </footer>";
}
?>


