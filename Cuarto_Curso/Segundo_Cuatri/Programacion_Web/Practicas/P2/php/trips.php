<?php
require_once __DIR__ . '/DataObject.php';
require_once __DIR__. '/utils.php';

class Trip extends DataObject
{
    protected $datos = array(
        "country" => "",
        "place" => "",
        "date" => ""
    );

    //TODO: DOCUMENTACION
    /**
     * Añade un viaje nuevo a la base de datos
     *
     * @param [type] $data 
     * @return void
     */
    public static function create($data)
    {
        $conn = parent::conectar();
        $query = "INSERT INTO " . TABLA_VIAJES . " VALUES (?,?,?)";

        $validDate=validateDate($data['date']);

        if ($validDate) {
            try {
                $stmt = $conn->prepare($query);
                return $stmt->execute([$data['country'], $data['place'], $data['date']]);
            } catch (PDOException $e) {
                if (isset($e->errorInfo[1]) && $e->errorInfo[1] == 1452) {
                    echo "Trips::create No se puede registrar el viaje. El destino no tiene un precio asignado en el sistema.";
                } else if (isset($e->errorInfo[1]) && $e->errorInfo[1] == 1062) { //Error de duplicado
                    echo "Trips::create Ya existe un viaje registrado para este destino en la fecha seleccionada.";
                } else {
                    echo "Trips::create inesperado en la base de datos: " . $e->getMessage();
                }
                return false;
            }
        }else{return false;}
    }

    public static function delete($data){
        $conn = parent::conectar();
        $query = "DELETE FROM " . TABLA_VIAJES . " WHERE country = ? AND place = ? AND date = ?";

        $validDate=validateDate($data['date']);

        if ($validDate) {
            try {
                $stmt = $conn->prepare($query);
                return $stmt->execute([$data['country'], $data['place'], $data['date']]);
            } catch (PDOException $e) {
                error_log('Trips::delete ' . $e->getMessage());
                return false;
            }
        }else{return false;}
    }
}
