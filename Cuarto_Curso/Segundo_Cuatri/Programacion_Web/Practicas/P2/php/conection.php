<?php
/**
 * Clase de conexión a la base de datos, todas las conexiones 
 * se realizarán a través de esta clase.
 */
class Database{
    //TODO: cambiar los datos a como los tiene gabri
    private $host = 'localhost'; // Dirección del servidor de base de datos
    private $db   = 'dblucashidalgo_pw2526'; // Nombre de la base de datos
    private $user = 'pwlucashidalgo';      // Nombre de usuario
    private $pass = '25lucashidalgo26';    // Contraseña
    private $charset = 'utf8mb4';

    public $conn;

    /**
     * Crea la conexión a la base de datos
     *
     * @return PDO La conexión a la base de datos
     */
    public function connect():PDO{
        try{
            $dsn = "mysql:host=$this->host;dbname=$this->db;charset=$this->charset";
            $this->conn = new PDO($dsn, $this->user, $this->pass, [PDO::ATTR_ERRMODE => PDO::ERRMODE_EXCEPTION]);
            return $this->conn;
        } catch (\PDOException $e) {
            die("Error de conexión: " . $e->getMessage());
        }
    }

    public function __destruct() {
        $this->conn = null; // Cierra la conexión al destruir el objeto
    }
}
?>
