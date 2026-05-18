<!DOCTYPE html>
<html lang="es">

<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <link rel="stylesheet" href="../../css/style.css">
    <link rel="stylesheet" href="../../css/form.css">
    <link rel="stylesheet" href="../../css/viajes.css">
    <title>Azimut Viajes | Brasil</title>
</head>

<body>
    <header>

        <h1 id="nombreDecor">Azimut Viajes</h1>

        <img id="logoHeader" src="../../imagenes/logoAzimut.png"
            alt="Logotipo Azimut">

        <?php
        require_once '../php/utils.php';
        session_start();

        //Si se ha loggeado ponemos el avatar y el boton de cerrar sesion
        if (isset($_SESSION['loggedIn']) && $_SESSION['loggedIn'] === true) {
            putAvatar($_SESSION['admin'], $_SESSION['nickName'], 2);
        }
        ?>
        <nav id="menuHeader">
            <ul>
                <li><a href="../../index.php">Inicio</a></li>
                <li><a href="../../html/viajes.php">Viajes</a></li>
                <li><a href="../../html/viajes_grupo.php">Viajes en
                        grupo</a></li>
                <li><a href="../../html/ofertas.php">Ofertas</a></li>
                <li><a href="../../html/sobre_agencia.php">Sobre nuestra
                        agencia</a></li>
                <li><a href="../../html/sugerencias.php">Sugerencias</a></li>
            </ul>
        </nav>
    </header>
    <aside id="menuViajesPais">
        <nav>
            <h2>Destinos</h2>
            <details class="listaContinentes">
                <summary>&#127757; Europa</summary>
                <ul class="listaPaises">
                    <li><a
                            href="../../html/viajes_españa/viajes_españa.php">España</a></li>
                    <li><a
                            href="../../html/viajes_suecia/viajes_suecia.php">Suecia</a></li>
                </ul>
            </details>
            <details class="listaContinentes">
                <summary>&#127758; América</summary>
                <ul class="listaPaises">
                    <li><a
                            href="../../html/viajes_brasil/viajes_brasil.php">Brasil</a></li>
                </ul>
            </details>
            <details class="listaContinentes">
                <summary>&#127757; África</summary>
                <ul class="listaPaises">
                    <li><a
                            href="../../html/viajes_madagascar/viajes_madagascar.php">Madagascar</a></li>
                </ul>
            </details>
            <details class="listaContinentes">
                <summary>&#127759;Asia</summary>
                <ul class="listaPaises">
                    <li><a
                            href="../../html/viajes_india/viajes_india.php">La
                            India</a></li>
                </ul>
            </details>
        </nav>

    </aside>
    <main class="viajesCuadricula">
        <!-- Botones para moverse por los grupos de viajes -->
        <input type="radio" name="navGrupo" id="radio1" checked>
        <input type="radio" name="navGrupo" id="radio2">
        <!-- /Botones para moverse por los grupos de viajes -->

        <nav class="flechasGrupos">
            <label for="radio1"
                class="flechaIzq">&#10094;</label>
            <label for="radio2"
                class="flechaDcha">&#10095;</label>
        </nav>
        <section class="viajes" id="grupo1">
            <h2>Viajes</h2>

            <article class="viajeTipo">
                <h3>Rio de Janeiro, Brasil</h3>
                <a href="../../html/viajes_brasil/viajes_brasil.php"><img
                        src="../../imagenes/brasilBetter.jpg"
                        alt="Imagen Rio de Janeiro"></a>
                <form action="../../html/viajes.php" method="post"
                    class="fechaViaje">
                    <select name="fecha" class="selectorFecha">
                        <option value="null">Seleccione fecha</option>

                        <option
                            value="1407;1807">14/07/2026-18/07/2026</option>
                        <option
                            value="0110;0410">1/10/2026-4/10/2026</option>
                    </select>
                </form>
                <p class="precio"><strong>960€</strong></p>
            </article>

            <article class="viajeTipo">
                <h3>Anavilhanas, Brasil</h3>
                <a href="../../html/viajes_brasil/viaje_Anavilhanas.html" target="_blank"><img
                        src="../../imagenes/anavilhanas.jpg"
                        alt="Imagen Anavilhanas"></a>
                <form action="../../html/viajes.php" method="post"
                    class="fechaViaje">
                    <select name="fecha" class="selectorFecha">
                        <option value="null">Seleccione fecha</option>
                        <option
                            value="2407;2807">24/07/2026-28/07/2026</option>
                        <option
                            value="2110;2410">21/10/2026-24/10/2026</option>
                    </select>
                </form>
                <p class="precio"><strong>750€</strong></p>
            </article>
        </section>
        <section class="viajes" id="grupo2">
            <h2>Viajes</h2>
            <article class="viajeTipo">
                <h3>Natal, Brasil</h3>
                <a
                    href="../../html/viajes_brasil/viajes_brasil.php"><img
                        src="../../imagenes/natal.jpg"
                        alt="Imagen Natal"></a>
                <form action="../../html/viajes.php" method="post"
                    class="fechaViaje">
                    <select name="fecha" class="selectorFecha">
                        <option value="null">Seleccione fecha</option>
                        <option
                            value="0603;1603">6/03/2026-16/03/2026</option>
                        <option
                            value="0509;1009">5/9/2026-10/9/2026</option>
                    </select>
                </form>
                <p class="precio"><strong>1500€</strong></p>
            </article>
        </section>

    </main>
    <footer>
        <nav id="menuFooter">
            <ul>
                <li><a href="../../html/contacto.php">Contacte con
                        nosotros</a></li>
                <li><a href="../../como_se_hizo.pdf"
                        target="_blank">Cómo se
                        hizo</a></li>
            </ul>
        </nav>
        <p id="fechaModificacion">27/04/2026</p>
    </footer>
</body>

</html>