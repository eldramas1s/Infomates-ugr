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
    public function validate(array $data)
    {
        $this->errors = [];

        if (empty($data['nombre'])) {
            $this->addError('nombre', 'El nombre es obligatorio');
        } elseif (strlen($data['nombre']) > 30) {
            $this->addError('nombre', 'El nombre no puede tener más de 30 caracteres');
        } elseif (!preg_match('/^[A-Za-zÁÉÍÓÚáéíóúÑñÜü ]+$/', $data['nombre'])) {
            $this->addError('nombre', 'El nombre solo puede contener letras y espacios');
        }

        if (empty($data['nickName'])) {
            $this->addError('nickName', 'El nickname es obligatorio');
        } elseif (!preg_match('/^[a-zA-Z0-9_]+$/', $data['nickName'])) {
            $this->addError('nickName', 'Solo letras, números y _');
        } elseif (strlen($data['nickName']) < 3 || strlen($data['nickName']) > 20) {
            $this->addError('nickName', 'Debe tener entre 3 y 20 caracteres');
        }

        if (empty($data['email'])) {
            $this->addError('email', 'El email es obligatorio');
        } elseif (!filter_var($data['email'], FILTER_VALIDATE_EMAIL)) {
            $this->addError('email', 'Email no válido');
        }

        if (empty($data['password'])) {
            $this->addError('password', 'La contraseña es obligatoria');
        } elseif (strlen($data['password']) < 8 || strlen($data['password']) > 15) {
            $this->addError('password', 'Debe tener entre 8 y 15 caracteres');
        } elseif (!preg_match('/(?=.*[a-z])(?=.*[A-Z])(?=.*\d)(?=.*[$@$!%*?&.]).{8,15}/', $data['password'])) {
            $this->addError('password', 'Debe contener mayúscula, minúscula, número y símbolo');
        }

        if (!isset($data['aceptar'])) {
            $this->addError('aceptar', 'Debes aceptar el aviso legal');
        }

        if (!isset($data['adultez'])) {
            $this->addError('adultez', 'Debes indicar si eres mayor de edad');
        }
    }

    public function process(array $data)
    {
        $esAdulto = isset($data['adultez']) && (int)$data['adultez'] === 1;

        if (!$esAdulto) {
            $this->addError('adultez', 'Debes ser mayor de edad');
            return false;
        }

        $user = new User([
            'nickName' => $data['nickName'],
            'nombre' => $data['nombre'],
            'email' => $data['email'],
            'password' => $data['password'],
            'admin' => 0
        ]);

        $errores = User::validateUser($user);

        if (!empty($errores)) {
            foreach ($errores as $error) {
                $this->addError('general', $error);
            }
            return false;
        }

        if (User::exists($data['nickName'], $data['email'])) {
            $this->addError('general', 'Nickname o email ya en uso');
            return false;
        }

        if (!User::create($user->getDatos())) {
            $this->addError('general', 'Error al crear usuario');
            return false;
        }

        return true;
    }
}

class FormLogIn extends FormHandler
{
    public function validate(array $data)
    {
        $this->errors = [];

        if (empty($data['nickName'])) {
            $this->addError('nickName', 'El nickname es obligatorio');
        }

        if (empty($data['password'])) {
            $this->addError('password', 'La contraseña es obligatoria');
        }
    }

    public function process(array $data)
    {
        if (
            !User::exists($data['nickName'], '') ||
            !User::verifyPassword($data['nickName'], $data['password'])
        ) {
            $this->addError('general', 'Nickname o contraseña incorrectos');
            return false;
        }

        $_SESSION['nickName'] = $data['nickName'];
        $_SESSION['loggedIn'] = true;
        $_SESSION['admin'] = User::getUserByNickname($data['nickName'])->isAdmin(); 

        return true;
    }
}