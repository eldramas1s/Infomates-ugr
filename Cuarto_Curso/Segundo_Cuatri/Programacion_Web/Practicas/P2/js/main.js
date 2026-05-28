import {formularioAlta} from "./forms/fomularioAlta.js";
import { formularioSesion } from "./forms/formularioSesion.js";

if(document.getElementById("formularioAlta")){
    new formularioAlta();
}

if(document.getElementById("signUpForm")){
    new formularioSesion();
}