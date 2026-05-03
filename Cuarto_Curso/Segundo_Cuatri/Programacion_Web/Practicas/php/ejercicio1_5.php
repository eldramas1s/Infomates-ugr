<?php
function headerMaker($id, $class, $title, $content): string
{
    $headerHtml = "<header id=\"$id\" class=\"$class\">";
    $headerHtml .= "<h2>" . htmlspecialchars($title) . "</h2>";
    $headerHtml .= $content;
    $headerHtml .= "</header>";
    return $headerHtml;
}

function sectionMaker($id, $class, $title, $content): string
{
    $sectionHtml = "<section id=\"$id\" class=\"$class\">";
    $sectionHtml .= "<h2>$title</h2>";
    $sectionHtml .= $content;
    $sectionHtml .= "</section>";

    return $sectionHtml;
}

function footerMaker($id, $class, $content): string
{
    $footerHtml = "<footer id=\"$id\" class=\"$class\">";
    $footerHtml .= $content;
    $footerHtml .= "</footer>";

    return $footerHtml;
}
?>

<?php
// Tus variables de precios
$precio1 = 10.50;
$precio2 = 12.00;

// Contenido del menú en formato lista
$listaPlatos = "<ul>
    <li>Primer = Ensalada ($precio1)</li>
    <li>Primer = Pasta ($precio2)</li>
</ul>";

// Renderizar las partes
echo headerMaker("cabecera-principal", "top", "Restaurante PHP", "Bienvenidos a nuestra mesa.");
echo sectionMaker("menu-hoy", "principal", "Menú del Día", $listaPlatos);
echo sectionMaker("menu-hoy", "principal", "Menú del Día", $listaPlatos);
echo sectionMaker("menu-hoy", "principal", "Menú del Día", $listaPlatos);
echo footerMaker("pie-pagina", "footer-claro", "<p> 2026 Mi Restaurante</p>");
?>