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
    public $admin = 0;

    /**
     * Constructor de la clase User.
     *
     * @param string $nickName El nickname del usuario.
     * @param string $nombre El nombre del usuario.
     * @param string $email El email del usuario.
     * @param string $password La contraseña del usuario.
     * @param int $admin Indica si el usuario es administrador.
     */
    public function __construct(string $nickName, string $nombre, string $email, string $password, int $admin = 0)
    {
        $this->nickName = $nickName;
        $this->nombre = $nombre;
        $this->email = $email;
        $this->password = $password;
        $this->admin = (int)$admin;
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
        try {
            $query = "INSERT INTO Users (nickName, nombre, email, password, admin)
                VALUES (?,?,?,?,?)";
            $stmt = $this->conn->prepare($query);
            $hashedPassword = password_hash($user->password, PASSWORD_DEFAULT);

            if ($stmt->execute([$user->nickName, $user->nombre, $user->email, $hashedPassword, $user->admin])) {
                return true;
            }
            return false;
        } catch (PDOException $e) {
            error_log('UserManager::create: ' . $e->getMessage());
            return false;
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
                return new User($data['nickName'], $data['nombre'], $data['email'], $data['password'], (bool)$data['admin']);
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
     * Valida un usuario según las reglas de negocio y seguridad establecidas
     * 
     * Reglas de negocio:
     * 1. No se admiten menores de edad
     * Reglas de seguridad:
     * 1. Evitar que entren datos nulos o vacíos a la BD
     * 
     * @param User $user 
     * @return array Un array con los errores encontrados, vacío si no hay errores
     */
    public function validateUser(User $user): array
    {
        $errors = [];

        if (empty(trim($user->nickName)) || empty(trim($user->email)) || empty(trim($user->password)) || empty(trim($user->nombre))) {
            $errors[] = "Faltan datos obligatorios para crear el registro en la base de datos.";
        }

        return $errors;
    }
}
