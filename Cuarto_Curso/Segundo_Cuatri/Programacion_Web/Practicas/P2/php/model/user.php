<?php
require_once __DIR__ . '/DataObject.php';

/**
 * Clase que representa a los usuarios de la página web.
 */
class User extends DataObject
{
    protected $datos = array(
        "nickName" => "",
        "nombre" => "",
        "email" => "",
        "password" => "",
        "admin" => 0
    );

    /**
     * Comprueba si un usuario existe en la base da datos
     *
     * @param [type] $nickname
     * @param [type] $email
     * @return boolean True si existe y false si no existe o no se ha podido hacer la operacion
     */
    public static function exists($nickname, $email): bool
    {
        $conn = parent::conectar();
        $query = "SELECT nickName FROM " . TABLA_USUARIOS . " WHERE nickName = ? OR email = ?";
        try {
            $stmt = $conn->prepare($query);
            $stmt->execute([$nickname, $email]);
            return $stmt->fetchColumn() !== false;
        } catch (PDOException $e) {
            error_log('User::exists: ' . $e->getMessage());
            return false;
        }
    }

    /**
     * Crea una nueva tupla en la base de datos
     *
     * @param array $data
     * @return boolean True si se puede crar y false en caso contrario
     */ 
    public static function create(array $data):bool{
        $conn = parent::conectar();
        $query = "INSERT INTO " . TABLA_USUARIOS . " (nickName, nombre, email, password, admin)
                VALUES (?,?,?,?,?)";
        try {
            
            $stmt = $conn->prepare($query);
            $hashedPassword = password_hash($data['password'], PASSWORD_DEFAULT);

            if ($stmt->execute([$data['nickName'], $data['nombre'], $data['email'], $hashedPassword, $data['admin']])) {
                return true;
            }
            return false;
        } catch (PDOException $e) {
            error_log('User::create: ' . $e->getMessage());
            return false;
        }
    }

    /**
     * Obtiene un usuario según su nickName
     *
     * @param [type] $nickname
     * @return  User|null Usuario si existe y null si no se encuentra
     */
    public static function getUserByNickname($nickname): ?User
    {
        $conn = parent::conectar();
        $query = "SELECT * FROM " . TABLA_USUARIOS . " WHERE nickName = ?";
        try {
            $stmt = $conn->prepare($query);
            $stmt->execute([$nickname]);
            $data = $stmt->fetch(PDO::FETCH_ASSOC);
            if ($data) {
                return new User($data);
            }
            return null;
        } catch (PDOException $e) {
            error_log('User::getUserByNickname: ' . $e->getMessage());
            return null;
        }
    }

    /**
     * Verifica la contraseña del usuario
     *
     * @param [type] $nickname
     * @param [type] $password
     * @return boolean True si es correcta y false si no lo es
     */
    public static function verifyPassword($nickname, $password): bool
    {
        $user = self::getUserByNickname($nickname);
        if ($user) {
            return password_verify($password, $user->datos['password']);
        }
        return false;
    }

    /**
     * Borra un usuario según su nickName
     *
     * @param [type] $nickname
     * @return boolean True si consigue realizar la operacion y false en caso contrario
     */
    public static function deleteByNickname($nickname): bool
    {
        $conn = parent::conectar();
        $query = "DELETE FROM " . TABLA_USUARIOS . " WHERE nickName = ?";
        try {
            $stmt = $conn->prepare($query);
            return $stmt->execute([$nickname]);
        } catch (PDOException $e) {
            error_log('User::deleteByNickname: ' . $e->getMessage());
            return false;
        }
    }

    /**
     * Valida que un usuario no se cree con datos nulos donde no los deba haber
     *
     * @return array Error sobre nulidad de elementos o array vacio
     */
    public function validateUser(): array
    {
        $errors = [];

        if (empty(trim($this->datos['nickName'])) || empty(trim($this->datos['email'])) || empty(trim($this->datos['password'])) || empty(trim($this->datos['nombre']))) {
            $errors[] = "Faltan datos obligatorios para crear el registro en la base de datos.";
        }

        return $errors;
    }

    /**
     * Devuelve los datos del objeto implicito
     *
     * @return array Datos del objeto implicito
     */
    public function getDatos(): array
    {
        return $this->datos;
    }

    /**
     * Comprueba si el objeto implicito es administrador
     *
     * @return boolean True si lo es y false si no lo es.
     */
    public function isAdmin(): bool
    {
        return $this->datos['admin'] == 1;
    }
}


