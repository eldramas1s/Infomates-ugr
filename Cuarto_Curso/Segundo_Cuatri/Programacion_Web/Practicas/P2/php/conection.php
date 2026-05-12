<?php
/**
 * Clase de conexión a la base de datos, todas las conexiones 
 * se realizarán a través de esta clase.
 */
class Database{
    private $host = 'localhost';
    private $db   = 'dblucashidalgo_pw2526'; //
    private $user = 'pwlucashidalgo';      //
    private $pass = '25lucashidalgo26';    //
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
