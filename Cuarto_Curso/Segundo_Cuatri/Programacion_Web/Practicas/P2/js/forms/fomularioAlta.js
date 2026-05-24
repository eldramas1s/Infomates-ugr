///////////////////////
// FORMULARIO ALTA USUARIOS
///////////////////////

//Importamos la clase genérica

import {formularioBase} from "./formularioBase.js"

export class formularioAlta extends formularioBase{

    /**
     * Constructor de formularioAlta. Determina el endpoint asociado.
     */
    constructor(){
        super("formularioAlta");
        //TODO: Corregir url
        this.endpoint = "../php/api/altausuarios.php"
        //this.endpoint = "https://bahia.ugr.es/~lucashidalgo/pe2/php/api/altausuarios.php";
        this.avisoLeido = false;
    }

    reglas(){
        const nameRegex = /^[A-Za-zÁÉÍÓÚáéíóúÑñÜü ]+$/;
        const nickNameRegex = /^[a-zA-Z0-9_]+$/;
        const emailRegex = /^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$/;
        const passwordRegex = /(?=.*[a-z])(?=.*[A-Z])(?=.*\d)(?=.*[$@$!%*?&.]).{8,15}/;

        // Variable para controlar si se ha leído el aviso legal
        document.getElementById("enlaceLegal").addEventListener('click',()=>{
            this.avisoLeido = true;
        });

        return {
            nombre : (value) => {
                if(!value) return "Nombre vacío";
                if(value.length > 30) return "Máximo 30 caracteres";
                if(!nameRegex.test(value)) return "Solo letras y espacios";
                return null;
            },

            nickName : (value) => {
                if(!value) return "NickName vacío";
                if(value.length < 3 || value.length > 30) return "Entre 3 y 30 caracteres";
                if(!nickNameRegex.test(value)) return "Solo letras, números y _";
                return null;
            },

            email : (value) => {
                if(!value) return "Email vacío";
                if(value.length > 100) return "Máximo 100 caracteres";
                if(!emailRegex.test(value)) return "Email no válido";
                return null;
            },

            password : (value) => {
                if(!value) return "Contraseña vacía";
                if(value.length < 8 || value.length > 15) return "Debe tener entre 8 y 15 caracteres";
                if(!passwordRegex.test(value)) return "Debe contener mayúscula, minúscula, número y símbolo";
                return null;
            },

            aceptar : (value) => {
                if(!value) return "Debes aceptar el aviso legal";
                if(!this.avisoLeido) return "Debes leer el aviso legal";
                return null;
            },

            adultez : (value) => {
                if(!value) return "Debes confirmar que eres mayor de edad";
                return null;
            }
        }
    }

    /**
     * Respuesta del servidor cuando sí se crea el usuario
     * 
     * @param {json} json 
     */
    onSuccess(json){
        alert(json.message);
        window.location.href = "../index.php";
    }


}