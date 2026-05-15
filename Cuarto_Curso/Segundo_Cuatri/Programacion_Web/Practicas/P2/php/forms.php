<?php
abstract class FormHandler
{
    protected $errors = [];

    /**
     * Se encarga de validar el formulario y procesarlo
     *
     * @param array $data
     * @return void
     */
    public function handle(array $data): void
    {

        if (empty($this->validate($data))) {
            $this->process($data);
        } else {
            // Mostrar errores
            foreach ($this->errors as $field => $message) {
                echo "<p class=\"error\">Error en $field: $message</p>";
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
    protected function addError(string $field, string $message): void
    {
        $this->errors[$field] = $message;
    }
}

require_once 'user.php';
require_once 'conection.php';
class FormSignUp extends FormHandler
{

    private UserManager $userManager;

    /**
     * Constructor de FormSignUp
     *
     * @param PDO $conn
     */
    public function __construct(PDO $conn)
    {
        $this->userManager = new UserManager($conn);
    }

    /**
     * Validación de campos del formulario
     *
     * @param array $data
     * @return array errores encontrados, vacío si no hay errores
     */
    public function validate(array $data): array
    {
        $this->errors = [];

        // Comprobaciones básicas del formulario
        if (empty($data['nombre'])) {
            $this->addError('nombre', 'El nombre es obligatorio');
        } else if (strlen($data['nombre']) > 30) {
            $this->addError('nombre', 'El nombre no puede tener más de 30 caracteres');
        } else if (!preg_match('/^[A-Za-zÁÉÍÓÚáéíóúÑñÜü ]+(?:\s[A-Za-zÁÉÍÓÚáéíóúÑñÜü ]+)*$/', $data['nombre'])) {
            $this->addError('nombre', 'El nombre solo puede contener letras y espacios');
        }

        if (empty($data['nickName'])) {
            $this->addError('nickName', 'El nickname es obligatorio');
        } else if (!preg_match('/^[a-zA-Z0-9_]+$/', $data['nickName'])) {
            $this->addError('nickName', 'El nickname solo puede contener letras, números y guiones bajos');
        } else if (strlen($data['nickName']) < 3 || strlen($data['nickName']) > 20) {
            $this->addError('nickName', 'El nickname debe tener entre 3 y 20 caracteres');
        }

        if (empty($data['email'])) {
            $this->addError('email', 'El email es obligatorio');
        } else if (!filter_var($data['email'], FILTER_VALIDATE_EMAIL)) {
            $this->addError('email', 'Email no válido');
        } else if (strlen($data['email']) > 100) {
            $this->addError('email', 'El email no puede tener más de 100 caracteres');
        } else if (!preg_match('/^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$/', $data['email'])) {
            $this->addError('email', 'El email no tiene un formato válido');
        }
        
        if (empty($data['password'])){
            $this->addError('password', 'La contraseña es obligatoria');
        } else if (strlen($data['password']) < 8 || strlen($data['password']) > 15) {
            $this->addError('password', 'La contraseña debe tener entre 8 y 15 caracteres');
        } else if (!preg_match('/(?=.*[a-z])(?=.*[A-Z])(?=.*\d)(?=.*[$@$!%*?&.]).{8,15}/', $data['password'])) {
            $this->addError('password', 'La contraseña debe contener al menos una letra mayúscula, una letra minúscula, un número y un carácter especial');
        }

        if (!isset($data['aceptar'])) {
            $this->addError('aceptar', 'Debes aceptar el aviso legal');
        }

        if (!isset($data['adultez'])) {
            $this->addError('adultez', 'Debes indicar si eres mayor de edad');
        }

        // Si ya hay errores, no seguimos
        if (!empty($this->errors)) {
            return $this->errors;
        }

        return $this->errors;
    }

    /**
     * Procesa el formulario, se encarga de crear el usuario
     *
     * @param array $data
     * @return User|boolean|string Un objeto User si se ha creado correctamente, un mensaje de error en caso contrario, o true si el proceso se ha realizado correctamente pero no se ha creado un nuevo usuario (TODO: esto último no sé si lo voy a usar)
     */
    public function process(array $data): User|bool|string
    {
        $user = new User(
            $data['nickName'],
            $data['nombre'],
            $data['email'],
            $data['password'],
            $data['adultez'] === 'adulto'
        );

        // Validación del modelo
        $errors = $this->userManager->validateUser($user);

        // Lo juntamos con los errores (TODO)
        if (!empty($errors)) {
            return implode("<br>", $errors);
        }

        // Crear usuario
        $this->userManager->create($user);

        return $user;
    }
}

/**
 * Clase para manejar el formulario de inicio de sesión
 */
class FormLogIn extends FormHandler
{
    private UserManager $userManager;

    public function __construct(PDO $conn)
    {
        $this->userManager = new UserManager($conn);
    }

    public function validate(array $data): array
    {
        $this->errors = [];

        if (empty($data['nickName'])) {
            $this->addError('nickName', 'El nickname es obligatorio');
        }

        if (empty($data['password'])) {
            $this->addError('password', 'La contraseña es obligatoria');
        }

        return $this->errors;   
    }
    //TODO: hacer lo de las sesiones
    public function process(array $data): User|bool|string
    {

        // Validación del modelo
        if(!$this->userManager->exists($data['nickName'], '') || !$this->userManager->verifyPassword($data['nickName'], '' , $data['password']))
        {
            return 'Nickname o contraseña incorrectos';
        } 
            //TODO: hacer lo de las sesiones
        return true;
    }

}


