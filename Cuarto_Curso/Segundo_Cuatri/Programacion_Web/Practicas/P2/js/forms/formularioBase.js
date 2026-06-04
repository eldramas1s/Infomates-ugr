////////////////////////////
// FORMULARIO BASICO
////////////////////////////

export class formularioBase {
    /**
     * Construye un objeto formulario tomandolo del archivo en el que se ejecuta
     * 
     * @param {string} idFormulario identificador del formulario
     */
    constructor(idFormulario) {
        this.form = document.getElementById(idFormulario);

        this.form.addEventListener('submit', (e) => this.enviar(e));

        this.realTimeValidation();
    }

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
     * Envia los datos al servidor para procesarlos
     * 
     * @param {Event} event 
     */
    async enviar(event) {
        event.preventDefault();

        const reglas = this.reglas();

        for (const campo in reglas) {
            this.limpiarError(campo);
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
        else {
            //Enviamos los datos
            try {
                //Hacemos el fetch asíncrono
                const response = await fetch(this.endpoint, {
                    method: 'POST',
                    headers: { 'Content-Type': 'application/json' },
                    body: JSON.stringify(datos)
                });


                if (!response.ok) {
                    throw new Error(`Error en la red: ${response.status}`);
                }


                //Si hay respuesta la procesamos pasandola a json
                const json = await response.json();
                

                //Procesamos la respuesta
                if (json.success) {
                    this.onSuccess(json);
                } else {
                    //Si hay errores los procesamos
                    if (json.errors) {
                        for (const field in json.errors) {
                            this.mostrarError(field, json.errors[field]);
                        }
                        //Si no hay errores procesamos el mensaje
                    } else if (json.message) {
                        alert(json.message);
                    }
                }

            } catch (error) {
                console.error("Hubo un problema con la petición fetch:", error);
                alert("No se pudo conectar con el servidor. Inténtalo de nuevo más tarde.");
            }
        }
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

    /**
     * Devuelve las reglas de cada campo de un formulario
     * 
     * @returns diccionario con las reglas de cada campo
     */
    reglas() {
        return {}
    }

    /**
     * Procesa el json en caso de exito
     * 
     * @param {json} json Mensaje de validacion
     * @returns Depende de la clase
     */
    onSuccess(json) {
        return;
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