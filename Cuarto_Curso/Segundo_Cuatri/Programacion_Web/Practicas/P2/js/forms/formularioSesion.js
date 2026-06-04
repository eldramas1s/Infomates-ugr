///////////////////////
// FORMULARIO INICIO SESION
///////////////////////

//Importamos la clase genérica

import { formularioBase } from "./formularioBase.js";

export class formularioSesion extends formularioBase{

    /**
     * Constructor del manejador del formulario de inicio de sesion
     */
    constructor(){
        super("signUpForm");
        this.endpoint = "./php/api/inicioSesion.php"
    }

    /**
     * Devuelve las reglas asociadas al formulario de inicio de sesion
     * @returns Array asociativo de funciones
     */
    reglas(){
        const nickNameRegex = /^[a-zA-Z0-9_]+$/;
        const passwordRegex = /(?=.*[a-z])(?=.*[A-Z])(?=.*\d)(?=.*[$@$!%*?&.]).{8,15}/;
        return {
            nickName: (value) => {
                if(!value || value.trim() === "") return "NickName vacío";
                if(value.length < 3 || value.length > 30) return "Entre 3 y 30 caracteres";
                if(!nickNameRegex.test(value)) return "Solo letras, números y _";
                return null;
            },

            password: (value) => {
                if(!value || value.trim() === "") return "Contraseña vacía";
                if(value.length < 8 || value.length > 15) return "Debe tener entre 8 y 15 caracteres";
                if(!passwordRegex.test(value)) return "Debe contener mayúscula, minúscula, número y símbolo";
                return null;
            }
        }
    }

    /**
     * Respuesta del servidor cuando sí se loguea el usuario
     * 
     * @param {json} json 
     */
    onSuccess(json){
        location.reload();
    }
}

