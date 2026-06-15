////////////////////////////
// FORMULARIO BASICO
////////////////////////////

import { formularioBase } from "./formularioBase.js";

export class formularioBusqueda extends formularioBase {

    /**
     * Crea el objeto formularioBusqueda, que extiende de formularioBase. 
     * Se encarga de cargar los países disponibles según el continente seleccionado 
     * y de cargar las ciudades disponibles según el país seleccionado. 
     * Además, valida que los datos introducidos sean correctos antes de enviar el formulario.
     */
    constructor() {
        super('formularioBusqueda');
        this.validCountries = [];
        this.countriesDictionary = {};
        this.loadCountries();


        //Levantamos los listeners
        this.setUpContinentChangeListener();
        this.setUpCountryChangeListener();
    }

    /**
     * Define las reglas de validación para cada campo del formulario.
     * @returns Diccionario con las funciones de validación para cada campo. 
     */
    reglas() {
        const continentRegex = /^(Asia|Africa|África|Europa|Oceania|Oceanía|America|América)$/i;
        const ciudadRegex = /^[A-Za-zÁÉÍÓÚáéíóúÑñÜüÇç['-]+(?: [A-Za-zÁÉÍÓÚáéíóúÑñÜüÇç['-]+)*$/;

        const formData = this.obtenerDatos();
        const hoy = new Date();
        hoy.setHours(0, 0, 0, 0);

        return {
            continent: (value) => {
                if (!value || value.trim() === "") return null;
                if (!continentRegex.test(value.trim())) return "No es un continente válido";
                return null;
            },

            country: (value) => {
                if (!value || value.trim() === "") return null;
                if (this.validCountries.length === 0) return null; //La lista de paises validos fallo
                if (!this.validCountries.includes(value.trim()) && this.validCountries.length > 0) return "El país que se ha introducido no existe";
                return null;
            },

            place: (value) => {
                if (!value || value.trim() === "") return null;
                if (!ciudadRegex.test(value.trim())) return "Introduce un nombre de ciudad válido (solo letras, espacios, guiones o apóstrofes).";
                return null;
            },

            departureDate: (value) => {
                if (!value || value.trim() === "") return null;
                const fechaSalida = new Date(value.trim());
                fechaSalida.setHours(0, 0, 0, 0);

                if (fechaSalida < hoy) return "La fecha no puede ser anterior a hoy";
                return null;
            },

            returnDate: (value) => {
                if (!value || value.trim() === "") return null;

                const fechaVuelta = new Date(value.trim());

                if (fechaVuelta < hoy) return "La fecha de vuelta no puede ser anterior a hoy";

                return null;
            }
        }
    }

    /**
     * Función asíncrona que se ejecuta al enviar el formulario. 
     * Valida los datos introducidos y, si son correctos, envía el formulario.
     * @param {Event} event 
     */
    async enviar(event) {
        event.preventDefault();

        const reglas = this.reglas();

        for (const field in reglas) {
            this.limpiarError(field);
        }

        const datos = this.obtenerDatos();
        const errors = this.validar(datos);

        if (Object.keys(errors).length > 0) {
            for (const field in errors) {
                if (field == 'password') {
                    this.form.elements['password'].value = "";
                }
                this.mostrarError(field, errors[field]);
            }
        }
        if (Object.keys(errors).length === 0) {
            this.form.submit(); //Ejecutamos una versión similar al envío que hay en el php
        }
    }

    /**
     * Funcion asíncrona que carga todos los países de la API gratuita Rest Countries
     */
    async loadCountries() {

        const formData = this.obtenerDatos();
        let response = null; //Para poder usarla en toda la funcion
        //Rellenamos el datalist paises
        let lista = document.getElementById("paises");

        try {
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
            this.validCountries = paises.map(p => {
                const nombreEspaniol = p.translations?.spa?.common;
                const nombreIngles = p.name?.common;
                if (!nombreEspaniol) return null;

                const paisFormateado = nombreEspaniol.split(' ').map(palabra => palabra.charAt(0).toUpperCase() + palabra.slice(1)).join(' ');

                if (nombreIngles) {
                    this.countriesDictionary[paisFormateado] = nombreIngles;
                }

                return paisFormateado;
            }).filter(Boolean).sort((a, b) => a.localeCompare(b));


            if (lista) {
                lista.innerHTML = ""; //Limpiamos la lista
                this.validCountries.forEach(nombrePais => {
                    const option = document.createElement("option");
                    option.value = nombrePais;
                    lista.appendChild(option);
                })
            }
        } catch (error) {
            console.error("Error cargando los países. Vuelva a intentarlo más tarde.");
            if (lista) lista.innerHTML = ""; //Limpiamos la lista si hay error de conexión
        }
    }

    /**
     * Función que crea un listener que se ejecuta al cambiar el país seleccionado. 
     * Carga las ciudades disponibles para ese país.
     */
    setUpCountryChangeListener() {
        //Tomamos el input del pais
        const inputCountry = document.querySelector('input[name="country"]');

        if (inputCountry) {
            inputCountry.addEventListener('change', (e) => {

                let countrySelected = e.target.value.trim();

                let placesList = document.getElementById('places');

                //Vaciamos el input de la ciudad
                const inputPlace = document.querySelector('input[name="place"]');
                if (inputPlace) inputPlace.value = "";
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

    /**
     * Función que crea un listener que se ejecuta al cambiar el continente seleccionado. 
     * Vacia el input del país y de la ciudad, y carga los países disponibles para ese continente.
     */
    setUpContinentChangeListener() {
        const inputContinent = document.querySelector('input[name="continent"]');
        if (inputContinent) {
            inputContinent.addEventListener('change', () => {
                //Vaciamos el input del pais y al ciudad
                const inputCountry = document.querySelector('input[name="country"]');
                const inputPlace = document.querySelector('input[name="place"]');
                if (inputCountry) inputCountry.value = "";
                if (inputPlace) inputPlace.value = "";
                this.loadCountries();
            })
        }
    }


    /**
     * Carga las ciudades disponibles para un país dado utilizando la API gratuita Countries Now.
     * @param {string} englishName Nombre del país en inglés
     * @returns nothing
     */
    async loadCities(englishName) {
        const placesList = document.getElementById('places');

        if (!placesList) return;

        //Para que el usuario sea consciente que se estan cargando las ciudades
        placesList.innerHTML = "<option value='Cargando ciudades...'>";

        //Intentamos obtener las ciudades
        try {

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

            places.sort((a, b) => a.localeCompare(b)).forEach(city => {
                const option = document.createElement("option");
                option.value = city;
                placesList.appendChild(option);
            })


        } catch (error) {
            console.error("Error cargando las ciudades. Vuelva a intentarlo más tarde.")
            placesList.innerHTML = ""; // Limpiamos si hay error de conexión
        }
    }

}