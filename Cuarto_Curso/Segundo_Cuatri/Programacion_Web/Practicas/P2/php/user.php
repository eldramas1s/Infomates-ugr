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

    public static function create(array $data){
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

    public static function verifyPassword($nickname, $password): bool
    {
        $user = self::getUserByNickname($nickname);
        if ($user) {
            return password_verify($password, $user->datos['password']);
        }
        return false;
    }

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

    public static function validateUser(User $user): array
    {
        $errors = [];

        if (empty(trim($user->datos['nickName'])) || empty(trim($user->datos['email'])) || empty(trim($user->datos['password'])) || empty(trim($user->datos['nombre']))) {
            $errors[] = "Faltan datos obligatorios para crear el registro en la base de datos.";
        }

        return $errors;
    }

    public function getDatos(): array
    {
        return $this->datos;
    }

    public function isAdmin(): bool
    {
        return $this->datos['admin'] == 1;
    }
}


