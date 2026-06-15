<?php 
    session_start();
    require_once './model/films.php';
?>

<!DOCTYPE html>
<html lang="en">

<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <link rel="stylesheet" href="./design/style.css">
    <title>CineMudo</title>
</head>

<body>
    <header id="header">
        <img id="logo" src="../imagenes/logo" alt="Logo de la empresa">
        <h1 id="enterpriseName">CineMudo</h1>
        <form name="logInForm" class="headerForm" action="./index.php" method="post">

            <fieldset class="container">
                <label for="username">Usuario:</label>
                <input type="text" name="username" id="username">
            </fieldset>

            <fieldset class="container">
                <label for="password">Contraseña</label>
                <input type="password" name="password" id="password">
            </fieldset>

            <button type="submit" class="button">LogIn</button>
            <a href="./structure/signUp.php" class="button">Sign Up</a>
        </form>

        <nav id="menuHeader">
            <ul>
                <li><a class="button" href="./structure/films.php">Films</a></li>
                <li><a class="button" href="./structure/author.php">Author</a></li>
            </ul>
        </nav>
    </header>

    <main id="mainIndex">

        <h1 id="titleMain"> CineMudo </h1>
        <section id="tableScrapping" >
            <article id="searcherArticle">
                <h2>¡Busca tu pelicula!</h2>
                <form action="./index.php" method="get">
                    <fieldset id="fieldsBusqueda" class="container">
                        <input type="text" placeholder="Título">
                        <input type="text" placeholder="Versión">
                        <input type="text" placeholder="Idioma">
                    </fieldset>
                    <button type="submit" class="button"> Busca </button>
                </form>
                
            </article>
        </section>
        
        <section class="cartelPeliculas">
            <h2>Todo nuestro repertorio</h2>
            <?php 
            $films = film::getAll();
        
            if(count($films)>0){
                foreach ($films as $film => $data){
                    echo "<article class=\"card\">";
                    echo "<h3 id=\"title\">".$data['title']. " (". $data['version'] . ") </h3>";
                    echo "<p id=\"price\">". $data['price']."</p>";
                    echo "<p id=\"idiom\">". $data['language']."</p>";
                    echo "</article>";
                }
            }
            else{
                echo "<p> No hay nada </p>";
            }
            ?>
        </section>
        

    </main>

    <footer>
        <section id="simpleData" class="footerSection">
            <p><?php echo date('Y-m-d')?></p>
            <p>Lucas Hidalgo Herrera</p>
        </section>

    </footer>
</body>

</html>