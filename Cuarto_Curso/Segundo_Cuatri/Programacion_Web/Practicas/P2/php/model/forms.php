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

        if (empty($this->errors)) {
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

require_once __DIR__ . '/user.php';
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
        } elseif (strlen($data['nickName']) < 3 || strlen($data['nickName']) > 30) {
            $this->addError('nickName', 'Debe tener entre 3 y 30 caracteres');
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

        $errores = $user->validateUser();

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

require_once __DIR__ . '/trips.php';

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

        $user = User::getUserByNickname($data['nickName']);
        $_SESSION['nickName'] = $data['nickName'];
        $_SESSION['loggedIn'] = true;
        $_SESSION['admin'] = $user->isAdmin();
        $_SESSION['name'] = $user->getDatos()['nombre'];

        return true;
    }
}

class FormAddTrip extends FormHandler
{
    private $healthData = [];

    public function validate(array $data)
    {
        $this->errors = [];

        //Trabajamos con los datos saneados para poder modificarlos
        $this->healthData = $data;

        if (empty($data['continent'])) {
            $this->addError('continent', 'El continente es necesario');
        }
        if (empty($data['country'])) {
            $this->addError('country', 'El pais es necesario');
        }
        if (empty($data['place'])) {
            $this->addError('place', 'El lugar es necesario');
        }
        if (!isset($data['price']) || trim($data['price']) === '' || !is_numeric($data['price'])) {
            $this->healthData['price'] = 0.0; // O manejas un error de validación
        } else {
            //Si el precio que se obtiene es un número, lo convertimos a float y lo redondeamos a 2 decimales, además de evitar precios negativos
            $priceFloat = (float)$data['price'];

            if ($priceFloat < 0) {
                $this->healthData['price'] = 0.0; // Evitamos precios negativos
            } else {
                $this->healthData['price'] = round($priceFloat, 2); //Tomar dos decimales
            }
        }
        if (empty($data['departureDate'])) {
            $this->addError('departureDate', 'La fecha de salida es obligatoria');
        }
        if (empty($data['returnDate'])) {
            $this->addError('returnDate', 'La fecha de vuelta es obligatoria');
        }
        if (empty($data['img'])) {
            $this->healthData['img'] = 'default.jpg';
        } else {
            $img = basename($data['img']); //Se queda solo con [nombre].[formato]

            //Ahora debemos buscar la imagen
            $rutaImagenes = __DIR__ . '/../imagenes/';
            $imagenDefecto = 'default.jpg';

            $rutaCompleta = $rutaImagenes . $img;

            if (file_exists($rutaCompleta)) {
                $this->healthData['img'] = $img;
            } else {
                $this->healthData['img'] = $imagenDefecto;
            }
        }

        // Validamos las fechas por seguridad, aunque en la base de datos también se haga
        if (!empty($data['departureDate']) && !empty($data['returnDate'])) {
            $fechaSalida = new DateTime($data['departureDate']);
            $fechaVuelta = new DateTime($data['returnDate']);
            $diferencia = $fechaSalida->diff($fechaVuelta)->days;

            if ($fechaVuelta <= $fechaSalida) {
                $this->addError('returnDate', 'La vuelta debe ser posterior a la salida');
            } elseif ($diferencia < 3) {
                $this->addError('returnDate', 'El viaje debe durar al menos 3 días');
            }
        }
    }


    public function process(array $data)
    {
        //Buscar si existe el viaje
        $trip = Trip::getTrip($this->healthData['continent'], $this->healthData['country'], $this->healthData['place'], $this->healthData['departureDate'], $this->healthData['returnDate']);

        if ($trip == null) {
            if (!Trip::create($this->healthData)) {
                $this->addError('general', 'Ha habido un error al crear el viaje');
                return false;
            }
        } else {
            $datos = $trip->getDatos();
            if (!Trip::modify($datos['continent'], $datos['country'], $datos['place'], $datos['departureDate'], $datos['returnDate'], $this->healthData['departureDate'], $this->healthData['returnDate'])) {
                $this->addError('general', 'Ha habido un erro al modificar el viaje');
                return false;
            }
        }
        return true;
    }
}
