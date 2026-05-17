<?php
abstract class FormHandler
{
    protected $errors = [];

    /**
     * Se encarga de validar el formulario y procesarlo
     *
     * @param array $data
     * @return bool True si el formulario se ha procesado correctamente, false en caso contrario (o si hay errores de validación)
     */
    public function handle(array $data): bool
    {
        $this->validate($data);

        if(empty($this->errors)) {
            return $this->process($data);
        }

        return false;    
    }

    /**
     * Devuelve los errores que tenga el formulario
     *
     * @return array Un array con los errores encontrados, vacío si no hay errores
     */
    public function getErrors(): array
    {
        return $this->errors;
    }

    /**
     * Valida el formulario
     *
     * @param array $data
     * @return array Un array con los errores encontrados, vacío si no hay errores
     */
    abstract public function validate(array $data);

    /**
     * Procesa la informacion del usuario
     *
     * @param array $data
     * @return bool|User|string True si el proceso se ha realizado correctamente, un mensaje de error en caso contrario, o un objeto User si se ha creado uno nuevo
     */
    abstract public function process(array $data);

    /**
     * Añade un error a la lista de errores
     *
     * @param string $field
     * @param string $message
     * @return void
     */
    protected function addError(string $field, string $message)
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
     * @return void Rellena los errores en el array de errores
     */
    public function validate(array $data)
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
        $this->addError('adultez', 'Debes indicar si eres mayor o menor de edad.');
        } 

    }

    /**
     * Procesa el formulario, se encarga de crear el usuario
     *
     * @param array $data
     * @return void 
     */
    public function process(array $data)
    {
        
        $esAdulto = (isset($data['adultez']) && (int)$data['adultez'] === 1);

        $user = new User(
            $data['nickName'],
            $data['nombre'],
            $data['email'],
            $data['password']
        );
        if (!$esAdulto) {
            $this->addError('adultez', 'Debes ser mayor de edad para registrarte.');
            return false;
        }
        $erroresValidacion = $this->userManager->validateUser($user);
        if (!empty($erroresValidacion)) {
            foreach ($erroresValidacion as $error) {
                $this->addError('Usuario', $error); 
            }
            return false; 
        }

        // Aunque lo hace create por seguridad, comprobamos antes la existencia para disponer de errores más específicos
        if ($this->userManager->exists($user->nickName, $user->email)) {
            $this->addError('general', 'El nickname o el correo electrónico ya están en uso.');
            return false; // Salimos para no intentar crearlo
        }

        // Crear usuario
        $creado = $this->userManager->create($user);
        if (!$creado) {
            $this->addError('general', 'Ha ocurrido un error al crear el usuario. Por favor, inténtalo de nuevo más tarde.');
            return false;
        }
        return true;
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

    /**
     * Impone los valores de la sesion o devuelve errores
     *
     * @param array $data Datos del formulario de sesion
     * @return void 
     */
    public function process(array $data)
    {

        // Validación del modelo
        if(!$this->userManager->exists($data['nickName'], '') || !$this->userManager->verifyPassword($data['nickName'], '' , $data['password']))
        {
            $this->addError('general', 'Nickname o contraseña incorrectos');
            return false;
        } else {

            $_SESSION['nickName'] = $data['nickName'];
            $_SESSION['loggedIn'] = true;
            //TODO: Poner si es admin o no

            //Guardamos la inicial del nickName para mostrarla cuando se inicie sesión
            $_SESSION['initial'] = strtoupper($data['nickName'][0]);
            return true;
        }

    }


}