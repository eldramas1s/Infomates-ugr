////////////////////////////
// FORMULARIO PAISES
////////////////////////////7

import { formularioBase } from "./formularioBase.js";

export class formularioPaises extends formularioBase {

    /**
     * Constructor del manjeador del formulario de añadir un viaje
     */
    constructor() {
        super("countryForm");
        this.endpoint = "../php/api/addTrip.php";
        this.validCountries = [];
        this.loadCountries();
    }

    /**
     * Funcion asíncrona que carga todos los países de la API gratuita Rest Countries
     */
    async loadCountries() {
        //Accedemos a la API Rest Countries para obtener todos los países que necesitamos
        const response = await fetch("https://restcountries.com/v3.1/all?fields=translations");
        if (!response.ok) {
            throw new Error("Error al conectar con la API de países");
        }

        //Si hay respuesta la procesamos
        const paises = await response.json();

        //Ya tenemos los paises entonces, los procesamos segun como los devuelve la API
        // Mapeamos para obtener los nombres comunes en español y los ordenamos de la A a la Z
        this.listaPaisesValidos = paises
            .map(p => {
                return nombre
                    .split(' ')
                    .map(palabra => palabra.charAt(0).toUpperCase() + palabra.slice(1))
                    .join(' ');
            })
            .filter(Boolean)
            .sort((a, b) => a.localeCompare(b));

        //Rellenamos el datalist paises
        let lista = document.getElementById("paises");
        if (lista) {
            lista.innerHTML = ""; //Limpiamos la lista
            this.listaPaisesValidos.forEach(nombrePais => {
                const option = document.createElement("option");
                option.value = nombrePais;
                lista.appendChild(option);
            })
        }
    }

    /**
     * Devuelve las reglas del formulario de creacion y modificado de viajes
     * @returns Array asociativo de funciones según el campo
     */
    reglas() {

        const continentRegex = /^(Asia|África|Europa|Oceanía|América)$/i;
        const ciudadRegex = /^[A-Za-zÁÉÍÓÚáéíóúÑñÜüÇç['-]+(?: [A-Za-zÁÉÍÓÚáéíóúÑñÜüÇç['-]+)*$/;
        const imgRegex = /^[a-zA-Z0-9_-]+\.(jpg|jpeg|png|webp|gif)$/i;

        return {
            continente: (value) => {
                if (!value || value.trim() === "") return "Continente vacío";
                if (!continentRegex.test(value.trim())) return "No es un continente válido";
            },

            pais: (value) => {
                if (!value || value.trim() === "") return "Pais vacío";
                if (this.listaPaisesValidos.length === 0) return null; //La lista de paises validos fallo
                if (!this.listaPaisesValidos.includes(value.trim())) return "El país que se ha introducido no existe";
                return null;
            },

            place: (value) => {
                if (!value || value.trim() === "") return "Ciudad vacía";
                if (value.length < 2 || value.length > 50) return "El nombre de la ciudad debe tener entre 2 y 50 caracteres.";
                if (!ciudadRegex.test(value.trim())) return "Introduce un nombre de ciudad válido (solo letras, espacios, guiones o apóstrofes).";
                return null;
            },

            price: (value) => {
                if (!value || value.trim() === "") return "Precio inválido";
                if (isNaN(value)) return "El precio debe ser un número.";
                let price = parseFloat(value.trim());
                if (price < 0) return "El precio lo paga el cliente";
            },

            departureDate: (value) => {
                if (!value) return "Debe haber una fecha de salida";
                const fechaSalida = new Date(value);
                const hoy = new Date();
                hoy.setHours(0, 0, 0, 0); //Comparamos solo dias

                if (fechaSalida <= hoy) return "La fecha debe ser posterior";
                return null;
            },

            returnDate: (value) => {
                if (!value) return "Los clientes deben volver";
                const fechaVuelta = new Date(value);
                const formData = this.obtenerDatos();
                const fechaSalida = formData.departureDate;
                if (!fechaSalida) return "La fecha de salida es necesaria";
                if (fechaVuelta <= fechaSalida) return "No pueden volver si no se han ido los clientes";

                //Un viaje durara tres dias como minimo
                const diferenciaMilisegundos = fechaVuelta - fechaSalida;
                const diferenciaDias = diferenciaMilisegundos / (1000 * 60 * 60 * 24);
                if (diferenciaDias < 3) return "El viaje es muy corto";
                return null;
            },

            imagen: (value) => {
                if (!value || value.trim() === "") return "Necesito una imagen";
                if (!imgRegex.test(value.trim())) return "Formato inválido. Debe ser un nombre de archivo (ej: paris_2026.jpg).";
                return null;
            }
        }
    }

    /**
     * Procesa el caso de exito
     * @param {json} json 
     */
    onSuccess(json) {
        alert(json.message);
        location.reload();
    }
}