///////////////////////
// FORMULARIO SUGERENCIAS
///////////////////////

//SI tuviera que poner la funcionalidad de crear una sugerencia en la base de datos heredaría de formularioBase
// COmo no es necesario, por falta de tiempo para estudiar los finales, no lo voy a hacer. Entonces debo hacerla completamente repitiendo
// codigo. El motivo de esta clase es porque se pide que *todos* los formularios se validen

export class formularioSugerencias {

    constructor() {
        this.form = document.forms["formSugerencias"];

        this.form.addEventListener('submit', (e) => this.enviar(e));

        this.realTimeValidation();
        this.suggestionContainer = document.getElementById("listaExperiencias");
    }

    reglas() {
        const textRegex = /^[a-zA-Z0-9áéíóúÁÉÍÓÚñÑüÜ\s.,!?¿¡-]+$/;
        const typeRegex = /^(Experiencia|experiencia|sugerencia|Sugerencia)$/i;

        return {
            tipo: (value) => {
                if (!value || value.trim() === "") return "Se necesita un tipo";
                if (!typeRegex.test(value)) return "Solo se admite Sugerencia o Experiencia";
            },

            comentario: (value) => {
                if (!value || value.trim() === "") return "El comentario es obligatorio";
                if (value.length > 255) return "Como máximo 255 caracteres";
                if (value.length < 10) return "Como mínimo 10 caracteres";
                if (!textRegex.test(value)) return "Esto no es texto en español";
            }
        }
    }

    enviar(event) {
        event.preventDefault();

        //Comprobamos los campos

        const reglas = this.reglas();

        for (const field in reglas) {
            this.limpiarError(field);
        }

        const errors = this.validar(this.obtenerDatos());

        if (Object.keys(errors).length > 0) {
            for (const field in errors) {
                this.mostrarError(field, errors[field]);
            }
        } else {
            //Entonces todo esta correcto y podemos crear la sugerencia
            this.onSuccess();
        }
    }
    obtenerCookie(nombre) {
        //console.log("Cookie:"+document.cookie);
        const valor = `; ${document.cookie}`;
        const partes = valor.split(`; ${nombre}=`);
        if (partes.length === 2) return partes.pop().split(';').shift();
        return null;
    }

    getNumStars() {
        let stars = 0;

        for (let i = 1; i <= 5; i++) {
            const starhtml = document.getElementById(`star${i}`);
            if (starhtml && starhtml.checked) {
                stars = i;
            }
        }

        const estrellasRellenas = "&starf;".repeat(stars);
        const estrellasVacias = "&star;".repeat(5 - stars);

        return `${estrellasRellenas}${estrellasVacias}`;

    }

    getServiciosSeleccionados() {
        const checkboxesMarcados = document.querySelectorAll('#servicios input[type="checkbox"]:checked');

        let textosServicios = [];

        checkboxesMarcados.forEach(checkbox => {
            const label = document.querySelector(`label[for="${checkbox.id}"]`);

            if (label) {
                textosServicios.push(label.textContent.trim());
            }
        });


        return textosServicios.join(', ');
    }

    buildSuggestionHTML() {
        const usuario = decodeURIComponent(this.obtenerCookie("name") || "Anónimo");
        let valorTipo = document.getElementById("tipo").value;
        const tipo = valorTipo.charAt(0).toUpperCase() + valorTipo.slice(1);
        const comentario = document.getElementById("comentario").value;

        let html = `<h3 class="sugerencia">${usuario} - <small>${tipo}</small></h3>`;
        html += `<p>Valoración: <strong class="stars">${this.getNumStars()}</strong></p>`;
        html += `<p>${comentario}</p>`;
        if (tipo === "Experiencia") {
            html += `<h4>¿Qué se ofrecía en tu experiencia?</h4>`;
            html += `<p>${this.getServiciosSeleccionados()}</p>`;
        }

        return html;
    }

    onSuccess() {
        alert("Se ha registrado correctamente");

        if (this.suggestionContainer) {
            //Creamos el elemento en el DOM y le damos contenido así como posicion
            const newSuggestion = document.createElement("article");
            newSuggestion.innerHTML = this.buildSuggestionHTML();
            this.suggestionContainer.appendChild(newSuggestion);
        }

        this.form.reset();
    }


    //////////////////////
    // Metodos tomados de formularioBase que realmente no se tomarian
    //////////////////////

    /**
     * Construye un objeto que representa las entradas del formulario
     * 
     * @returns Objeto cuyas entradas son los datos del formulario
     */
    obtenerDatos() {
        const datos = new FormData(this.form);

        return Object.fromEntries(datos.entries());
    }

    /**
     * Valida los datos, se implementa en las hijas
     * 
     * @param {Object} datos datos a validar
     */
    validar(datos) {
        const reglas = this.reglas();
        const errors = {};

        for (const campo in reglas) {
            const validador = reglas[campo];

            const error = validador(datos[campo])

            if (error) {
                errors[campo] = error;
            }
        }

        return errors;

    }

    /**
     * Crea un mensaje de error en el formulario
     * 
     * @param {string} fieldName nombre del campo del formulario
     * @param {string} message mensaje de error
     */
    mostrarError(fieldName, message) {

        if (fieldName === 'general') {
            alert(message);
            location.reload();
            return;
        }

        let field = this.form.elements[fieldName];
        //Si es un radio button, nos quedamos con el primero
        if (field instanceof RadioNodeList || field.length > 0) {
            field = field[0];
        }
        if (field) {

            let container = field.closest(".field")
            if (container) {
                container.classList.add("error")

                let pError = container.querySelector(".errorMessage");

                if (!pError) {

                    pError = document.createElement("div");
                    pError.classList.add("errorMessage");

                    container.appendChild(pError);
                }
                pError.textContent = message;
            }
        }
    }

    /**
     * Limpia el error que habia en el campo con nombre fieldName
     * 
     * @param {string} fieldName nombre del campo
     */
    limpiarError(fieldName) {
        let field = this.form.elements[fieldName];

        //Si son los radio buttons pues cojemos el primero solo
        if (field instanceof RadioNodeList || field.length > 0) {
            field = field[0];
        }

        if (field) {
            let container = field.closest(".field");

            if (container) {

                container.classList.remove("error");
                let pError = container.querySelector(".errorMessage");

                if (pError) {
                    pError.remove()
                }
            }
        }
    }

    realTimeValidation() {

        const eventos = ['input', 'change'];

        eventos.forEach(tipoEvento => {
            //Imponemos un eventListener en los eventos recogidos
            this.form.addEventListener(tipoEvento, (e) => {
                const field = e.target.name;
                const reglas = this.reglas();

                if (reglas[field]) {
                    this.limpiarError(field);

                    const datos = this.obtenerDatos();
                    const error = reglas[field](datos[field]);

                    if (error) {
                        this.mostrarError(field, error);
                    }
                }
            });
        })

    }


}