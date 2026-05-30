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
        this.countriesDictionary = {};
        this.loadCountries();

        this.setUpCountryChangeListener();
        this.setUpContinentChangeListener();
    }

    /**
     * Funcion asíncrona que carga todos los países de la API gratuita Rest Countries
     */
    async loadCountries() {

        const formData = this.obtenerDatos();
        let response = null; //Para poder usarla en toda la funcion

        if (formData.continent.trim() === "") {

            //Accedemos a la API Rest Countries para obtener todos los países que necesitamos
            response = await fetch("https://restcountries.com/v3.1/all?fields=translations,name");
        }
        else {

            const mapaContinentes = {
                'europa': 'europe',
                'asia': 'asia',
                'áfrica': 'africa',
                'africa': 'africa',
                'oceanía': 'oceania',
                'oceania': 'oceania',
                'américa': 'americas',
                'america': 'americas'
            };

            const continenteApi = mapaContinentes[formData.continent.trim().toLowerCase()];

            if (continenteApi) {
                //Accedemos a la API Rest Countries para obtener todos los países que necesitamos según el continente
                response = await fetch(`https://restcountries.com/v3.1/region/${continenteApi}?fields=translations,name`);
            } else {
                // Por si acaso el usuario escribe algo raro
                response = await fetch("https://restcountries.com/v3.1/all?fields=translations,name");
            }

        }
        if (!response.ok) {
            throw new Error("Error al conectar con la API de países");
        }

        //Si hay respuesta la procesamos
        const paises = await response.json();

        //Ya tenemos los paises entonces, los procesamos segun como los devuelve la API
        // Mapeamos para obtener los nombres comunes en español y los ordenamos de la A a la Z
        this.validCountries = paises
            .map(p => {
                const nombreEspaniol = p.translations?.spa?.common;
                const nombreIngles = p.name?.common;
                if (!nombreEspaniol) return null;

                const paisFormateado = nombreEspaniol
                    .split(' ')
                    .map(palabra => palabra.charAt(0).toUpperCase() + palabra.slice(1))
                    .join(' ');

                if (nombreIngles) {
                    this.countriesDictionary[paisFormateado] = nombreIngles;
                }

                return paisFormateado;
            })
            .filter(Boolean)
            .sort((a, b) => a.localeCompare(b));

        //Rellenamos el datalist paises
        let lista = document.getElementById("paises");
        if (lista) {
            lista.innerHTML = ""; //Limpiamos la lista
            this.validCountries.forEach(nombrePais => {
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

        const continentRegex = /^(Asia|Africa|África|Europa|Oceania|Oceanía|America|América)$/i;
        const ciudadRegex = /^[A-Za-zÁÉÍÓÚáéíóúÑñÜüÇç['-]+(?: [A-Za-zÁÉÍÓÚáéíóúÑñÜüÇç['-]+)*$/;
        const imgRegex = /^[a-zA-Z0-9_-]+\.(jpg|jpeg|png|webp|gif)$/i;
        const formData = this.obtenerDatos();
        const hoy = new Date();
        hoy.setHours(0, 0, 0, 0); //Comparamos solo dias
        return {
            continent: (value) => {
                if (!value || value.trim() === "") return "Continente vacío";
                if (!continentRegex.test(value.trim())) return "No es un continente válido";
                return null;
            },

            country: (value) => {
                if (!value || value.trim() === "") return "Pais vacío";
                if (!formData.continent) return "Sin continente no hay país";
                if (this.validCountries.length === 0) return null; //La lista de paises validos fallo
                if (!this.validCountries.includes(value.trim())) return "El país que se ha introducido no existe";
                return null;
            },

            place: (value) => {
                if (!value || value.trim() === "") return "Ciudad vacía";
                if (!formData.country) return "Sin país no hay ciudad";
                if (value.length < 2 || value.length > 50) return "El nombre de la ciudad debe tener entre 2 y 50 caracteres.";
                if (!ciudadRegex.test(value.trim())) return "Introduce un nombre de ciudad válido (solo letras, espacios, guiones o apóstrofes).";
                return null;
            },

            price: (value) => {
                if (!value || value.trim() === "") return "Precio inválido";
                if (isNaN(value)) return "El precio debe ser un número.";
                let price = parseFloat(value.trim());
                if (price < 0) return "El precio lo paga el cliente";
                return null;
            },

            departureDate: (value) => {
                if (!value) return "Debe haber una fecha de salida";
                const fechaSalida = new Date(value.trim());

                if (fechaSalida <= hoy) return "La fecha debe ser posterior";
                return null;
            },

            returnDate: (value) => {
                if (!value) return "Los clientes deben volver";
                const fechaVuelta = new Date(value.trim());
                let fechaSalida = formData.departureDate;
                if (!fechaSalida) return "La fecha de salida es necesaria";
                fechaSalida=new Date(fechaSalida);
                if (fechaVuelta <= hoy) return "La fecha de vuelta debe ser posterior a hoy"
                if (fechaVuelta <= fechaSalida) return "No pueden volver si no se han ido los clientes";

                //DEBUG
                console.log("Salida: ", fechaSalida);
                console.log("Entrada: ", fechaVuelta);
                //Un viaje durara tres dias como minimo
                const diferenciaMilisegundos = fechaVuelta - fechaSalida;
                console.log(diferenciaMilisegundos);
                const diferenciaDias = diferenciaMilisegundos / (1000 * 60 * 60 * 24);
                console.log(diferenciaDias);
                if (diferenciaDias < 3) return "El viaje es muy corto";
                return null;
            },

            img: (value) => {
                if (!value || value.trim() === "") return "Necesito una imagen";
                if (!imgRegex.test(value.trim())) return "Formato inválido. Debe ser un nombre de archivo (ej: paris_2026.jpg).";
                return null;
            }
        }
    }

    setUpCountryChangeListener() {
        //Tomamos el input del pais
        const inputCountry = document.querySelector('input[name="country"]');

        if (inputCountry) {
            inputCountry.addEventListener('change', (e) => {
                let countrySelected = e.target.value.trim();

                let placesList = document.getElementById('places');

                if (countrySelected in this.countriesDictionary) {
                    const englishName = this.countriesDictionary[countrySelected] || countrySelected;

                    this.loadCities(englishName);
                }
                else {
                    if (placesList) placesList.innerHTML = "";
                }
            })
        }

    }

    setUpContinentChangeListener() {
        const inputContinent = document.querySelector('input[name="continent"]');
        if (inputContinent) {
            inputContinent.addEventListener('change', () => {
                this.loadCountries();
            })
        }
    }
    async loadCities(englishName) {
        const placesList = document.getElementById('places');

        if (!placesList) return;

        //Para que el usuario sea consciente que se estan cargando las ciudades
        placesList.innerHTML = "<option value='Cargando ciudades...'>";

        //Intentamos obtener las ciudades
        try {
            //DEBUG
            console.log("1. Dato exacto que se va a enviar:", englishName);
            console.log("2. Tipo de dato:", typeof englishName);
            console.log("3. JSON resultante:", JSON.stringify({ country: englishName }));
            const response = await fetch("https://countriesnow.space/api/v0.1/countries/cities", {
                method: "POST",
                headers: { "Content-Type": "application/json" },
                body: JSON.stringify({ country: englishName })
            });

            if (!response.ok) {
                throw new Error("Error al conectar con la API de países");
            }

            const json = await response.json();

            if (json.error) {
                placesList.innerHTML = "";
                return;
            }

            const places = json.data;
            placesList.innerHTML = "";

            places
                .sort((a, b) => a.localeCompare(b))
                .forEach(city => {
                    const option = document.createElement("option");
                    option.value = city;
                    placesList.appendChild(option);
                })


        } catch (error) {
            console.error("Error cargando las ciudades. Vuelva a intentarlo más tarde.")
            placesList.innerHTML = ""; // Limpiamos si hay error de conexión
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