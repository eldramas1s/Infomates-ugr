<?php
require_once( __DIR__.'/DataObject.php');

class Sugestion extends DataObject{
    protected $datos = array(
        "nickName" => "",
        "type" => false, // false para sugerencia, true para experiencia
        "points" => 0,
        "comment" => "",
        "touristicGuide" => false,
        "lodging" => false,
        "transport" => false,
        "food" => false
    );

    /**
     * Crea una sugerencia o experiencia en la base de datos
     *
     * @param array $data Un array con los datos de la sugerencia o experiencia a crear, con las siguientes claves:
     * - nickName: El nickname del usuario que hace la sugerencia o experiencia (string)
     * - type: El tipo de entrada, false para sugerencia y true para experiencia (boolean)
     * - points: La puntuación dada por el usuario (entero entre 0 y 5)
     * - comment: El comentario del usuario (string)
     * - touristicGuide: Si el usuario recomienda la guía turística (boolean)
     * - lodging: Si el usuario recomienda el alojamiento (boolean)
     * - transport: Si el usuario recomienda el transporte (boolean)
     * - food: Si el usuario recomienda la comida (boolean)
     * @return bool True si la sugerencia o experiencia se ha creado correctamente, false en caso contrario
     */
    public static function create(array $data){
        $conn = parent::conectar();
        $query = "INSERT INTO " . TABLA_SUGERENCIAS . " (nickName, type, points, comment, touristicGuide, lodging, transport, food)
                VALUES (?,?,?,?,?,?,?,?)";
        
        try{
            $stmt = $conn->prepare($query);
            if ($stmt->execute([$data['nickName'], 
            $data['type'], $data['points'], 
            $data['comment'], $data['touristicGuide'], 
            $data['lodging'], $data['transport'], $data['food']]))
            {
                return true;
            }
        } catch(PDOException $e){
            error_log('Sugestion::create: ' . $e->getMessage());
            return false;
        }
    }

    /**
     * Obtiene todas las sugerencias de un usuario a partir de su nickname
     *
     * @param [type] $nickname
     * @return array Un array con todas las sugerencias del usuario, vacío si no tiene ninguna o si ocurre un error
     */
    public static function getByNickname($nickname){
        $conn = parent::conectar();
        $query = "SELECT * FROM " . TABLA_SUGERENCIAS . " WHERE nickName = ?";
        try {
            $stmt = $conn->prepare($query);
            $stmt->execute([$nickname]);
            $sugestions = [];
            while ($data = $stmt->fetch(PDO::FETCH_ASSOC)) {
                $sugest = new Sugestion(
                    [
                        "nickName" => $data['nickName'],
                        "type" => $data['type'],
                        "points" => $data['points'],
                        "comment" => $data['comment'],
                        "touristicGuide" => $data['touristicGuide'],
                        "lodging" => $data['lodging'],
                        "transport" => $data['transport'],
                        "food" => $data['food']
                    ]
                );
                $sugestions[] = $sugest;
            }
            return $sugestions;
        } catch (PDOException $e) {
            error_log('Sugestion::getByNickname: ' . $e->getMessage());
            return [];
        }
    }

    /**
     * Elimina todas las sugerencias de un usuario a partir de su nickname
     *
     * @param [type] $nickname
     * @return bool True si se han eliminado correctamente o false en caso contrario
     */
    public static function deleteByNickname($nickname){
        $conn = parent::conectar();
        $query = "DELETE FROM ". TABLA_SUGERENCIAS . " WHERE nickName = ?";

        try{    
            $stmt = $conn->prepare($query);
            return $stmt->execute([$nickname]);
        }catch(PDOException $e){
            if ($e->getCode() == '1451') { // Código de error para violación de clave foránea
                error_log('Sugestion::deleteByNickname: No se puede eliminar la sugerencia porque está asociada a un viaje. ' . $e->getMessage());
            } else {
                error_log('Sugestion::deleteByNickname: ' . $e->getMessage());
            }
            return false;
        }
    }

    /**
     * Borra todas las sugerencias de la base de datos
     *
     * @return bool True si se ha conseguido correctamente o false en caso contrario.
     */
    public static function deleteAll(){
        $conn = parent::conectar();
        $query = "DELETE FROM " . TABLA_SUGERENCIAS;
        try {
            $stmt = $conn->prepare($query);
            return $stmt->execute();
        } catch (PDOException $e) {
            error_log('Sugestion::deleteAll: ' . $e->getMessage());
            return false;
        }
    }

    /**
     * Obtiene todas las sugerencias o experiencias de la base de datos
     *
     * @return array Un array con todas las sugerencias o experiencias
     */
    public static function getAll(){
        $conn = parent::conectar();
        $query = "SELECT * FROM " . TABLA_SUGERENCIAS;
        try {
            $stmt = $conn->prepare($query);
            $stmt->execute();
            $sugestions = [];
            while ($data = $stmt->fetch(PDO::FETCH_ASSOC)) {
                $sugest = new Sugestion(
                    [
                        "nickName" => $data['nickName'],
                        "type" => $data['type'],
                        "points" => $data['points'],
                        "comment" => $data['comment'],
                        "touristicGuide" => $data['touristicGuide'],
                        "lodging" => $data['lodging'],
                        "transport" => $data['transport'],
                        "food" => $data['food']
                    ]
                );
                $sugestions[] = $sugest;
            }
            return $sugestions;
        } catch (PDOException $e) {
            error_log('Sugestion::getAll: ' . $e->getMessage());
            return [];
        }
    }

    /**
     * Devuelve los datos de una sugerencia
     *
     * @return array
     */
    public function getDatos(): array{
        return $this->datos;
    }
    
    /**
     * Plasma la sugerencia o experiencia en un html 
     *
     * @return string El código html de la sugerencia o experiencia
     */
    public function toHtml(){
        $html = '<article>
                <h3 class="experiencia">'. $this->getUserName() . ' '. mb_strtoupper(mb_substr($this->datos['nickName'], 0, 1, "UTF-8"), "UTF-8").'. ' .'-
                    <small>'. ($this->datos['type'] ? 'Experiencia' : 'Sugerencia') . '</small></h3>
                <p>Valoración: <strong class="stars"> '. $this->getHTMLPoints() .' </strong></p>
                <p>'. $this->datos['comment'] .'</p>
                <h4>¿Qué se ofrecía en tu experiencia? </h4>
                <p>'. $this->getHTMLServices() .'</p>
            </article>';
            
        return $html;
    }


    /**
     * Obtiene el nombre del usuario para la sugerencia
     *
     * @return string Nombre del usuario o cadena vacía
     */
    private function getUserName(){
        $user = User::getUserByNickname($this->datos['nickName']);
        if ($user) {
            return $user->getDatos()['nombre']; 
        }
        return "";
    }

    /**
     * Obtiene el código html de la puntuacion con estrellas
     * vacías o llenas segun la puntuacion.
     *
     * @return string El código html de la puntuación
     */
    private function getHTMLPoints(){
        $html = '';
        for ($i = 0; $i<$this->datos['points']; $i++){
            $html .= '&starf; ';
        }
        for ($i = $this->datos['points']; $i<5; $i++){
            $html .= '&star; ';
        }
        return $html;
    }

    /**
     * Obtiene el código html de los servicios que experimentó
     * el usuario de la reseña
     *
     * @return string El código html de los servicios
     */
    private function getHTMLServices(){
        $html = '';
        if($this->datos['touristicGuide']){
            $html .= 'Guía turístico, ';
        }
        if($this->datos['lodging']){
            $html .= 'Alojamiento en Hotel, ';
        }
        if($this->datos['transport']){
            $html .= 'Transporte privado, ';
        }
        if($this->datos['food']){
            $html .= 'Comida incluida, ';
        }
        return $html;
    }
}



?>
