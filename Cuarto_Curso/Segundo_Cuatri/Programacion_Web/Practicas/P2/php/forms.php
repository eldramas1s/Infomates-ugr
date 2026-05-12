<?php 
abstract class FormHandler {
    protected $errors = [];

    /**
     * Se encarga de validar el formulario y procesarlo
     *
     * @param array $data
     * @return void
     */
    protected function handle(array $data): void {
        
        if (empty($this->validate($data))) {
            $this->process($data);
        } else {
            // Aquí podrías redirigir a una página de error o mostrar los errores de alguna forma
            foreach ($this->errors as $field => $message) {
                echo "<p>Error en $field: $message</p>";
            }
        }
        
    }

    /**
     * Valida el formulario
     *
     * @param array $data
     * @return array Un array con los errores encontrados, vacío si no hay errores
     */
    abstract public function validate(array $data): array;

    /**
     * Procesa la informacion del usuario
     *
     * @param array $data
     * @return bool|User|string True si el proceso se ha realizado correctamente, un mensaje de error en caso contrario, o un objeto User si se ha creado uno nuevo
     */
    abstract public function process(array $data): User|bool|string;

    /**
     * Añade un error a la lista de errores
     *
     * @param string $field
     * @param string $message
     * @return void
     */
    protected function addError(string $field, string $message): void {
        $this->errors[$field] = $message;
    }
}

class FormSignUp extends FormHandler{

    public function validate(array $data): array {
        return [];
    }

    public function process(array $data): User|bool|string {
        // Lógica para procesar el formulario de registro
        return true;
    }
}