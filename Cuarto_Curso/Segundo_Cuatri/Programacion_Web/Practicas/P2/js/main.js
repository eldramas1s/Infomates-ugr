import {formularioAlta} from "./forms/fomularioAlta.js";
import { formularioBusqueda } from "./forms/formularioBusqueda.js";
import { formularioPaises } from "./forms/formularioPaises.js";
import { formularioSesion } from "./forms/formularioSesion.js";
import {Carrusel} from "./carrusel.js";
import { formularioSugerencias } from "./forms/formularioSugerencias.js";

if(document.getElementById("formularioAlta")){
    new formularioAlta();
}

if(document.getElementById("signUpForm")){
    new formularioSesion();
}

if(document.getElementById("countryForm")){
    new formularioPaises();
}

if(document.getElementById("formularioBusqueda")){
    new formularioBusqueda();
}

if(document.getElementById("carrusel")){
    new Carrusel("carrusel");
}

//Si esta el formulario de sugerencias y la seccion de experiencias entonces creo el formulario
if(document.getElementById("formSugerencias") && document.getElementById("listaExperiencias")){
    new formularioSugerencias();
}