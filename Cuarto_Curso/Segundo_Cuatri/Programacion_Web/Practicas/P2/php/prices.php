<?php
////Esto no sirve (se hizo antes del cambio en la BD)
//use function PHPSTORM_META\type;

require_once __DIR__ . '/DataObject.php';
require_once __DIR__ . '/config.php';

/**
 * Clase que representa los precios de los viajes
 * Solo se usará cuando el administrador quiera añadir o 
 * borrar algún viaje.
 */
class Price extends DataObject
{
    protected $datos = array(
        "coutry" => "",
        "place" => "",
        "img" => "",
        "price" => 0
    );

    /**
     * Crea un nuevo destino y le asocia un precio
     *
     * @param array $data Un array con los datos del destino a crear, con las siguientes claves:
     * - country: El país del destino (string)
     * - place: El lugar del destino (string)
     * - price: El precio del destino (float)
     * - img: La imagen del destino (string)
     * @return bool True si el destino se ha creado correctamente, false en caso contrario
     */
    public static function create(array $data){
        $conn = parent::conectar();
        $query = "INSERT INTO " . TABLA_PRECIOS . " (country, place, price, img)
                VALUES (?,?,?,?)";
        try {
            $stmt = $conn->prepare($query);
            if ($stmt->execute([$data['country'], $data['place'], $data['price'], $data['img']])) {
                return true;
            }
            return false;
        } catch (PDOException $e) {
            error_log('Price::create: ' . $e->getMessage());
            return false;
        }
    }


    /**
     * Elimina un destino de viaje
     *
     * @param [type] $country El país del destino a eliminar
     * @param [type] $place El lugar del destino a eliminar
     * @return bool True si el destino se ha eliminado correctamente, false en caso contrario (o si el destino no existe)
     */
    public static function delete($country, $place){
        $conn = parent::conectar();
        $query = "DELETE FROM " . TABLA_PRECIOS . " WHERE country = ? AND place = ?";
        try {
            $stmt = $conn->prepare($query);
            return $stmt->execute([$country, $place]);
        } catch (PDOException $e) {
            error_log('Price::delete: ' . $e->getMessage());
            return false;
        }
    }

    /**
     * Modificar el precio de un destino concreto
     *
     * @param [type] $country El país del destino a modificar
     * @param [type] $place El lugar del destino a modificar
     * @param [type] $newPrice El nuevo precio a asignar al destino
     * @return bool True si el precio se ha modificado correctamente, false en caso contrario (o si el destino no existe)
     */
    public static function modifyPrice($country, $place, $newPrice){
        $conn = parent::conectar();
        $query = "UPDATE " . TABLA_PRECIOS . " SET price = ? WHERE country = ? AND place = ?";
        try {
            $stmt = $conn->prepare($query);
            return $stmt->execute([$newPrice, $country, $place]);
        } catch (PDOException $e) {
            error_log('Price::modifyPrice: ' . $e->getMessage());
            return false;
        }
    }

    /**
     * Modifica la url de un destino
     *
     * @param [type] $country El país del destino a modificar
     * @param [type] $place El lugar del destino a modificar
     * @param [type] $newImg La nueva url de la imagen a asignar al destino
     * @return bool True si la url de la imagen se ha modificado correctamente, false en caso contrario (o si el destino no existe)
     */
    public static function modifyImg($country, $place, $newImg){
        //Evitar que se suban archivos completos
        if(type($newImg) !== "string"){
            error_log('Price::modifyImg: El nuevo valor de la imagen debe ser una cadena de texto.');
            return false;
        }
        $conn = parent::conectar();
        $query = "UPDATE " . TABLA_PRECIOS . " SET img = ? WHERE country = ? AND place = ?";
        try {
            $stmt = $conn->prepare($query);
            return $stmt->execute([$newImg, $country, $place]);
        } catch (PDOException $e) {
            error_log('Price::modifyImg: ' . $e->getMessage());
            return false;
        }
    }

    /**
     * Obtiene el precio de un destino concreto
     *
     * @param [type] $country El país del destino
     * @param [type] $place El lugar del destino
     * @return float|null El precio del destino, null si el destino no existe o si ocurre un error
     */
    public static function getPrice($country, $place){
        $conn = parent::conectar();
        $query = "SELECT price FROM " . TABLA_PRECIOS . " WHERE country = ? AND place = ?";
        try {
            $stmt = $conn->prepare($query);
            $stmt->execute([$country, $place]);
            $data = $stmt->fetch(PDO::FETCH_ASSOC);
            if ($data) {
                return $data['price'];
            }
            return null;
        } catch (PDOException $e) {
            error_log('Price::getPrice: ' . $e->getMessage());
            return null;
        }
    }

    /**
     * Obtiene la url del destino en cuestión
     *
     * @param [type] $country El país del destino
     * @param [type] $place El lugar del destino
     * @return string|null La url de la imagen del destino, null si el destino no existe o si ocurre un error
     */
    public static function getImg($country, $place){
        $conn = parent::conectar();
        $query = "SELECT img FROM " . TABLA_PRECIOS . " WHERE country = ? AND place = ?";
        try {
            $stmt = $conn->prepare($query);
            $stmt->execute([$country, $place]);
            $data = $stmt->fetch(PDO::FETCH_ASSOC); //Simplemente especifica que el resultado se devuelva como un array asociativo
            if ($data) {
                return $data['img'];
            }
            return null;
        } catch (PDOException $e) {
            error_log('Price::getImg: ' . $e->getMessage());
            return null;
        }
    }


}
?>