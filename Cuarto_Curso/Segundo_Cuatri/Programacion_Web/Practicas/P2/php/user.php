<?php
require_once __DIR__ . '/conection.php';

/**
 * Clase que representa a los usuarios de la página web.
 */
class User
{
    public $nickName;
    public $nombre;
    public $email;
    public $password;
    public $adultez;

    /**
     * Constructor de la clase User.
     *
     * @param string $nickName El nickname del usuario.
     * @param string $nombre El nombre del usuario.
     * @param string $email El email del usuario.
     * @param string $password La contraseña del usuario.
     * @param bool $adultez Indica si el usuario es mayor de edad.
     */
    public function __construct(string $nickName, string $nombre, string $email, string $password, bool $adultez)
    {
        $this->nickName = $nickName;
        $this->nombre = $nombre;
        $this->email = $email;
        $this->password = $password;
        $this->adultez = $adultez;
    }
}

class UserManager
{
    private PDO $conn;
    private $table = 'Users';

    /**
     * Simplemente inicializa el manejador de usuario
     *
     * @param PDO $db
     */
    public function __construct(PDO $db)
    {
        $this->conn = $db;
    }

    /**
     * Comprueba si el usuario existe por su nickname o email
     *
     * @param string $nickname
     * @param string $email
     * @return bool True si el usuario existe, false en caso contrario (o si falla la base de datos)
     */
    public function exists($nickname, $email): bool
    {
        try {
            $query = "SELECT nickName FROM {$this->table} WHERE nickName = ? OR email = ?";
            $stmt = $this->conn->prepare($query);
            $stmt->execute([$nickname, $email]);
            return $stmt->fetchColumn() !== false;
        } catch (PDOException $e) {
            error_log('UserManager::exists: ' . $e->getMessage());
            return false;
        }
    }

    /**
     * Inserta un usuario a la base de datos.
     *
     * @param User $user
     * @return boolean True si el usuario se ha creado correctamente, false en caso contrario (o si falla la base de datos)
     */
    public function create(User $user): bool
    {
        if ($this->exists($user->nickName, $user->email)) {
            return false;
        } else if (!empty($this->validateUser($user))) {
            return false;
        } else {
            try {
                $query = "INSERT INTO {$this->table} (nickName, nombre, email, password, adultez) VALUES (?, ?, ?, ?, ?)";
                $stmt = $this->conn->prepare($query);
                return $stmt->execute([$user->nickName, $user->nombre, $user->email, password_hash($user->password, PASSWORD_DEFAULT), $user->adultez]); //Ciframos la contraseña
            } catch (PDOException $e) {
                error_log('UserManager::create: ' . $e->getMessage());
                return false;
            }
        }
    }

    /**
     * Busca un usuario por su nickName o email
     *
     * @param [type] $nickname
     * @param [type] $email
     * @return User|null El usuario encontrado o null si no se encuentra o si falla la base de datos
     */
    public function getUserByNickname($nickname, $email): ?User
    {
        try {
            $query = "SELECT * FROM {$this->table} WHERE nickName = ? OR email = ?";
            $stmt = $this->conn->prepare($query);
            $stmt->execute([$nickname, $email]);
            $data = $stmt->fetch(PDO::FETCH_ASSOC);
            if ($data) {
                return new User($data['nickName'], $data['nombre'], $data['email'], $data['password'], (bool)$data['adultez']);
            }
            return null;
        } catch (PDOException $e) {
            error_log('UserManager::getUserByNickname: ' . $e->getMessage());
            return null;
        }
    }

    /**
     * Comprueba si la contraseña dada es correcta
     *
     * @param [type] $nickname
     * @param [type] $email
     * @param [type] $password
     * @return boolean
     */
    public function verifyPassword($nickname, $email, $password): bool
    {
        $user = $this->getUserByNickname($nickname, $email);
        if ($user) {
            return password_verify($password, $user->password);
        }
        return false;
    }

    /**
     * Borra un usuario por nombre de usuario
     *
     * @param [type] $nickname
     * @return boolean True si el usuario se ha borrado correctamente, false en caso contrario (o si falla la base de datos)
     */
    public function deletebyNickname($nickname): bool
    {
        try {
            $query = "DELETE FROM {$this->table} WHERE nickName = ?";
            $stmt = $this->conn->prepare($query);
            return $stmt->execute([$nickname]);
        } catch (PDOException $e) {
            error_log("UserManager::deletebyNickname: " . $e->getMessage());
            return false;
        }
    }

    /**
     * Valida que los datos de un usuario sean correctos
     *
     * @param User $user
     * @return array Un array con los errores encontrados, vacío si no hay errores
     */
    public function validateUser(User $user): array
    {
        $errors = [];

        if (empty($user->nickName)) {
            $errors[] = "El nickname es obligatorio";
        }

        if (!filter_var($user->email, FILTER_VALIDATE_EMAIL)) {
            $errors[] = "Email no válido";
        }

        if (strlen($user->password) < 6) {
            $errors[] = "La contraseña debe tener al menos 6 caracteres";
        }

        if (empty($user->nombre)) {
            $errors[] = "El nombre es obligatorio";
        }
        return $errors;
    }
}
