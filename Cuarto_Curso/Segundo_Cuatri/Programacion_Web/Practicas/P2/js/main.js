import {formularioAlta} from "./forms/fomularioAlta.js";
import { formularioPaises } from "./forms/formularioPaises.js";
import { formularioSesion } from "./forms/formularioSesion.js";

if(document.getElementById("formularioAlta")){
    new formularioAlta();
}

if(document.getElementById("signUpForm")){
    new formularioSesion();
}

if(document.getElementById("countryForm")){
    new formularioPaises();
}