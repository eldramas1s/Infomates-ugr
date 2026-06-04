<?php

require_once __DIR__ . '/DataObject.php';

/**
 * Clase que representa la informacion de los destinos.
 */
class InfoTrips extends DataObject
{
    protected $datos = array(
        "continent" => "",
        "country" => "",
        "place" => "",
        "price" => 0.0,
        "img" => "",
        "lodging" =>"",
        "sortDesc" => "",
        "longDesc" => ""
    );

    /**
     * Comprueba si existe el destino
     *
     * @param [type] $continent
     * @param [type] $country
     * @param [type] $place
     * @return boolean True si existe y false si no existe o no se ha podido hacer la operacion
     */
    public static function exists($continent, $country, $place): bool
    {
        $conn = parent::conectar();
        $query = "SELECT * FROM " . TABLA_INFO . " WHERE continent = ? AND country = ? AND place = ?";

        try {
            $stmt = $conn->prepare($query);
            $stmt->execute([$continent, $country, $place]);
            return $stmt->fetchColumn() !== false;
        } catch (PDOException $e) {
            error_log('InfoTrips::exists ' . $e->getMessage());
            return false;
        }
    }

    /**
     * Modifica el precio y/o la url de la imagen de un destino
     *
     * @param [type] $data
     * @return boolean True si se consigue la operacion y false en caso contrario.
     */
    public static function modify($data): bool
    {
        $conn = parent::conectar();
        $query = "UPDATE " . TABLA_INFO;
         //continent = ? AND country = ? AND place = ?";

        $modify=["price=?", "img=?"];
        $parameters=[$data['price'],$data['img']];

        if($data['lodging']!==""){
            $modify[]="lodging=?";
            $parameters[]=$data['lodging'];
        }
        if($data['sortDesc']!==""){
            $modify[]="sortDesc=?";
            $parameters[]=$data['sortDesc'];
        }
        if($data['longDesc']!==""){
            $modify[]="longDesc=?";
            $parameters[]=$data['longDesc'];
        }

        $query.=" SET " . implode(",", $modify);

        $parameters[]=$data['continent'];
        $parameters[]=$data['country'];
        $parameters[]=$data['place'];

        $query.=" WHERE continent=? AND country=? AND place=?";

        try {
            $stmt = $conn->prepare($query);
            if ($stmt->execute($parameters)) {
                return true;
            }
            return false;
        } catch (PDOException $e) {
            error_log('InfoTrips::modify: ' . $e->getMessage());
            return false;
        }
    }

    /**
     * Crea un nuevo destino
     *
     * @param [type] $data
     * @return boolean True si se crea correctamente o false si no se crea
     */
    public static function create($data): bool
    {
        $conn = parent::conectar();
        $query = "INSERT INTO " . TABLA_INFO . " (continent,country,place,price,img,lodging,sortDesc,longDesc) VALUES (?,?,?,?,?,?,?,?)";

        try {
            $stmt = $conn->prepare($query);
            if ($stmt->execute([$data['continent'], $data['country'], $data['place'], $data['price'], $data['img'],$data['lodging'],$data['sortDesc'],$data['longDesc']])) {
                return true;
            }
            return false;
        } catch (PDOException $e) {
            error_log('InfoTrips::create: ' . $e->getMessage());
            return false;
        }
    }


    /**
     * Elimina un destino de la base de datos
     *
     * @param [type] $continent
     * @param [type] $country
     * @param [type] $place
     * @return boolean True si ha podido realizar la operacion y false en caso contrario
     */
    public static function delete($continent, $country, $place): bool
    {
        $conn = parent::conectar();
        $query = "DELETE FROM " . TABLA_INFO . " WHERE continent = ? AND country = ? AND place = ?";

        try {
            $stmt = $conn->prepare($query);
            return $stmt->execute([$continent, $country, $place]);
        } catch (PDOException $e) {
            error_log('InfoTrips::delete ' . $e->getMessage());
            return false;
        }
    }

    /**
     * Valida que un destino no se cree con datos nulos donde no los deba haber
     *
     * @return array Error sobre nulidad de elementos o array vacio
     */
    public function validateInfo(): array
    {
        $errors = [];

        if (empty(trim($this->datos['continent'])) || empty(trim($this->datos['country'])) || empty(trim($this->datos['place']))) {
            $errors[] = "Faltan datos obligatorios para crear el registro en la base de datos.";
        }

        return $errors;
    }

    /**
     * Obtiene 7 destinos a lo sumo para poder completar el carrusel.
     *
     * @return array COn los <=7 destinos con imagen y descripcion para el carrusel, o array vacio si no se han podido obtener los datos.
     */
    public static function getForCarrusel(): array{
        $conn = parent::conectar();
        $query = "SELECT place, img, sortDesc FROM " . TABLA_INFO . " WHERE img IS NOT NULL
                AND img!='' ORDER BY RAND() LIMIT 7";

        try{
            $stmt = $conn->prepare($query);
            $stmt->execute();
            return $stmt->fetchAll(PDO::FETCH_ASSOC);

        }catch(PDOException $e){
            error_log('InfoTrips::getForCarrusel: '. $e->getMessage());
            return [];
        }
    }

    /**
     * Obtiene, si existe, el infoTrip con clave primaria pasada como argumento
     *
     * @param [type] $continent continente
     * @param [type] $country pais
     * @param [type] $place lugar
     * @return InfoTrips|null infoTrips si existe y null si no existe
     */
    public static function getInfoTrips($continent, $country, $place): InfoTrips|null
    {
        $conn = parent::conectar();
        $query = "SELECT * FROM " . TABLA_INFO . " WHERE continent = ? AND country = ? AND place = ?";

        try {
            $stmt = $conn->prepare($query);
            $stmt->execute([$continent, $country, $place]);
            $data = $stmt->fetch(PDO::FETCH_ASSOC);
            if ($data) {
                return new InfoTrips($data);
            }
            return null;
        } catch (PDOException $e) {
            error_log('InfoTrips::getInfoTrip: ' . $e->getMessage());
            return null;
        }
    }

    public static function getAll(): array
    {
        $conn = parent::conectar();
        $query = "SELECT DISTINCT t.continent, t.country, t.place, i.price, i.img FROM " . TABLA_VIAJES . " t JOIN " . TABLA_INFO . " i 
                  ON t.continent = i.continent AND t.country = i.country AND t.place = i.place WHERE t.departureDate >= NOW() ORDER BY t.continent, t.country, t.place";

        try{
            $stmt = $conn->prepare($query);
            $stmt->execute();
            return $stmt->fetchAll(PDO::FETCH_ASSOC);
        } catch(PDOException $e){
            error_log('InfoTrips::getAll: ' . $e->getMessage());
            return [];
        }
    }
    /**
     * Devuelve el array de datos por comodidad
     *
     * @return array datos del objeto implícito
     */
    public function getDatos(): array
    {
        return $this->datos;
    }

    /**
     * Obtiene un array con <=4 viajes relacionados con un destino y que sean posteriores a la fecha actual.
     *
     * @return  array viajes relacionados con el destino, o array vacio si no se han podido obtener los datos o no hay viajes relacionados.
     */
    public function getRelatedTrips(): array
    {
        $conn = parent::conectar();
        $query = "SELECT DISTINCT t.continent, t.country, t.place, i.price, i.img
                  FROM " . TABLA_VIAJES . " t
                  INNER JOIN " . TABLA_INFO . " i 
                  ON t.continent = i.continent 
                    AND t.country = i.country 
                    AND t.place = i.place 
                  WHERE t.departureDate >= NOW() 
                    AND t.country = ? 
                    AND t.place <> ?
                  ORDER BY t.continent, t.country, t.place
                  LIMIT 4";

        try {
            $stmt = $conn->prepare($query);
            $stmt->execute([$this->datos['country'], $this->datos['place']]);
            $rows = $stmt->fetchAll(PDO::FETCH_ASSOC);
            $relatedTrips = [];
            foreach ($rows as $row) {
                $relatedTrips[] = new Trip($row);
            }
            return $relatedTrips;
        } catch (PDOException $e) {
            error_log('InfoTrips::getRelatedTrips ' . $e->getMessage());
            return [];
        }
    }

    /**
     * Obtiene los viajes que cumplen los filtros pasados como argumento, siempre y cuando sean posteriores a la fecha actual. 
     * Si un filtro es -1, se ignora.
     *
     * @param [type] $continent continente
     * @param [type] $country pais
     * @param [type] $place lugar
     * @param [type] $departureDate fecha de salida
     * @param [type] $returnDate fecha de vuelta
     * @return array viajes que cumplen los filtros, o array vacio si no se han podido obtener los datos o no hay viajes que cumplan los filtros.
     */
    public static function getAllBetween($continent,$country,$place, $departureDate, $returnDate): array
    {
        $conn = parent::conectar();

        // Creamos la consulta base
        $query = "SELECT DISTINCT t.continent, t.country, t.place, 
                         i.img, i.price
                  FROM " . TABLA_VIAJES . " t 
                  INNER JOIN " . TABLA_INFO . " i 
                    ON t.continent = i.continent 
                   AND t.country = i.country 
                   AND t.place = i.place AND t.departureDate >= NOW()";

        //Guardamos los filtros y los parametros dependiendo de lo que nos den
        $condiciones = [];
        $parametros = [];

        /// Filtramos los parámetros
        if ($departureDate !== -1 && $departureDate !== "-1") {
            $condiciones[] = "t.departureDate >= ?";
            $parametros[] = $departureDate;
        }

        if ($returnDate !== -1 && $returnDate !== "-1") {
            $condiciones[] = "t.returnDate <= ?";
            $parametros[] = $returnDate;
        }

        if ($country !== -1 && $country !== "-1") {
            $condiciones[] = "t.country LIKE ?";
            $parametros[] = "%".$country."%";
        }

        if ($continent !== -1 && $continent!=='-1' ){
            $condiciones[] = "t.continent LIKE ?";
            $parametros[] = "%".$continent."%";
        }

        if($place !== -1 && $place !== '-1'){
            $condiciones[] = "t.place LIKE ?";
            $parametros[] = "%".$place."%";
        }

        // Si tenemos alguna condicion, la añadimos a la consulta
        if (count($condiciones) > 0) {
            $query .= " WHERE " . implode(" AND ", $condiciones);
        }

        //Añadimos la ordenacion
        $query .= " ORDER BY t.continent, t.country, t.place";

        try {
            $stmt = $conn->prepare($query);

            //Ejecutamos la consulta
            $stmt->execute($parametros);

            return $stmt->fetchAll(PDO::FETCH_ASSOC);
        } catch (PDOException $e) {
            error_log("Trip::getAllBetween " . $e->getMessage());
            return [];
        }
    }

    /**
     * Convierte un viaje en una tarjeta de destino con fechas a elegir y lo enlaza a una página u otra dependiendo de $general.
     * $page se usa para poder gestionar las páginas en los enlaces, simplemente se incrusta.
     * 
     * Antes de hacer nada, toma todas las fechas asociadas a los destinos del objeto implícito.
     *
     * @param [type] $general
     * @param [type] $page
     * @return  string cadena de caracteres con el html asociado a la carta de destino.
     */
    public function tripToHtml($general, $page): string
    {
        //Buscamos todas las fechas asociadas al viaje
        $conn = parent::conectar();
        $query = "SELECT departureDate, returnDate FROM " . TABLA_VIAJES . " 
                  WHERE continent = ? AND country = ? AND place = ? AND departureDate >= NOW()
                  ORDER BY departureDate ASC";

        $optionsHtml = "";

        try {
            $stmt = $conn->prepare($query);
            $stmt->execute([
                $this->datos['continent'],
                $this->datos['country'],
                $this->datos['place']
            ]);
            $viajesDisponibles = $stmt->fetchAll(PDO::FETCH_ASSOC);

            //Construimos el select con cada resultado que hemos obtenido
            foreach ($viajesDisponibles as $viaje) {
                // Convertimos el formato YYYY-MM-DD de la base de datos a DD/MM/YYYY
                if (!empty($viaje['departureDate']) && !empty($viaje['returnDate'])) {
                    $dateSalida = new DateTime($viaje['departureDate']);
                    $fechaSalidaFormateada = $dateSalida->format('d/m/Y');
                    $dateVuelta = new DateTime($viaje['returnDate']);
                    $fechaVueltaFormateada = $dateVuelta->format('d/m/Y');
                } else {
                    $fechaSalidaFormateada = '';
                    $fechaVueltaFormateada = '';
                }

                //El valor serán las fechas de salida y regreso concretas separadas por comas
                $value = $viaje['departureDate'] . ";" . $viaje['returnDate'];

                $optionsHtml .= "<option value=\"{$value}\">{$fechaSalidaFormateada}-{$fechaVueltaFormateada}</option>\n";
            }
        } catch (PDOException $e) {
            error_log('Error en Trip::tripToHtml al cargar fechas: ' . $e->getMessage());
        }

        //Construimos la tarjeta de viaje
        $html = "<article class=\"viajeTipo\"><h3>" . htmlspecialchars($this->datos['place']) . ", " . htmlspecialchars($this->datos['country']) . "</h3>";

        if ($general) {
            $html .= "<a href=\"../html/viajes_pais.php?page=1&country=" . htmlspecialchars($this->datos['country']) . "\">
                    <img src=\"../imagenes/" . htmlspecialchars($this->datos['img']) . "\" alt=\"Imagen de " . htmlspecialchars($this->datos['place']) . "\">
                </a>
                <form action=\"../html/viajes.php?page=" . htmlspecialchars($page) . "\" method=\"post\" class=\"fechaViaje\">";
        } else {
            $html .= "<a href=\"../html/viaje_indiv.php?continent=" . htmlspecialchars($this->datos['continent']) . "&country=" . htmlspecialchars($this->datos['country']) . "&place=" . htmlspecialchars($this->datos['place']) . "\">
                    <img src=\"../imagenes/" . htmlspecialchars($this->datos['img']) . "\" alt=\"Imagen de " . htmlspecialchars($this->datos['place']) . "\">
                </a>
                <form action=\"../html/viajes_pais.php?country=" . htmlspecialchars($this->datos['country']) . "\" method=\"post\" class=\"fechaViaje\">";
        }

        $html .= "<select name=\"fecha\" class=\"selectorFecha\">
                    <option value=\"null\">Seleccione fecha</option>
                    " . $optionsHtml . "
                    </select>
                </form> <p class=\"precio\"><strong>" . number_format($this->datos['price'], 0, ',', '.') . "€</strong></p>";

        //Si el usuario es admin y estamos en el caso general, le permitimos borrar el destino
        if (isset($_SESSION['admin']) && $_SESSION['admin'] && $general) {
            $html .= "<button class=\"deleteButton\" 
                        data-continent=\"" . htmlspecialchars($this->datos['continent']) . "\" 
                        data-country=\"" . htmlspecialchars($this->datos['country']) . "\" 
                        data-place=\"" . htmlspecialchars($this->datos['place']) . "\">
                        <img src=\"../imagenes/deleteButton.png\" alt=\"Eliminar\">
                     </button>";
        }
        $html .= "</article>";

        return $html;
    }
}

/**
 * Clase que representa a los viajes de la página.
 */
class Trip extends DataObject
{
    protected $datos = array(
        "continent" => "",
        "country" => "",
        "place" => "",
        "departureDate" => "",
        "returnDate" => "",
        "price" => 0.0,
        "img" => "",
        "lodging" => "",
        "sortDesc" => "",
        "longDesc" => ""
    );

    /**
     * Crea un viaje creando el destino si no existe o modificandolo si existe
     *
     * @param [type] $data
     * @return boolean True si se crea y false si no se crea o si hay fallo
     */
    public static function create($data): bool
    {
        $conn = parent::conectar();
        $infoData = array(
            "continent" => $data['continent'],
            "country" => $data['country'],
            "place" => $data['place'],
            "price" => $data['price'],
            "img" => $data['img'],
            "lodging" => $data['lodging'],
            "sortDesc" => $data['sortDesc'],
            "longDesc" => $data['longDesc']
        );
        if (!InfoTrips::exists($data['continent'], $data['country'], $data['place'])) {
            InfoTrips::create($infoData);
        } else {
            InfoTrips::modify($infoData);
        }

        $query = "INSERT INTO " . TABLA_VIAJES . "(continent, country, place, departureDate, returnDate) VALUES(?,?,?,?,?)";

        try {
            $stmt = $conn->prepare($query);
            return $stmt->execute([
                $data['continent'],
                $data['country'],
                $data['place'],
                $data['departureDate'],
                $data['returnDate']
            ]);
        } catch (PDOException $e) {
            error_log('Trip::create ' . $e->getMessage());
            return false;
        }
    }

    /**
     * Borra un viaje (un destino con fecha)
     *
     * @param [type] $continent
     * @param [type] $country
     * @param [type] $place
     * @param [type] $date
     * @return boolean True si se borra y false si no se puede borrar
     */
    public static function delete($continent, $country, $place, $departureDate, $returnDate): bool
    {
        $conn = parent::conectar();
        $query = "DELETE FROM " . TABLA_VIAJES . " WHERE continent = ? AND country = ? AND place = ? AND departureDate = ? AND returnDate=?";

        try {
            $stmt = $conn->prepare($query);
            return $stmt->execute([$continent, $country, $place, $departureDate, $returnDate]);
        } catch (PDOException $e) {
            error_log('InfoTrips::delete ' . $e->getMessage());
            return false;
        }
    }

    /**
     * Devuelve un viaje en una fecha dada
     *
     * @param [type] $continent
     * @param [type] $country
     * @param [type] $place
     * @param [type] $date
     * @return Trip|null
     */
    public static function getTrip($continent, $country, $place, $departureDate, $returnDate): Trip|null
    {
        $conn = parent::conectar();
        $query = "SELECT * FROM " . TABLA_VIAJES . " t JOIN " . TABLA_INFO . " i 
        ON t.continent = i.continent AND t.country = i.country AND t.place = i.place
        WHERE t.continent = ? AND t.country = ? AND t.place = ? AND t.departureDate = ?  AND t.returnDate = ?";
        try {
            $stmt = $conn->prepare($query);
            $stmt->execute([$continent, $country, $place, $departureDate, $returnDate]);
            $data = $stmt->fetch(PDO::FETCH_ASSOC);
            if ($data) {
                return new Trip($data);
            }
            return null;
        } catch (PDOException $e) {
            error_log('Trip::getTrip: ' . $e->getMessage());
            return null;
        }
    }

    /**
     * Modifica un viaje, realmente lo borra y lo crea por ser todo clave primaria
     *
     * @param [type] $continent
     * @param [type] $country
     * @param [type] $place
     * @param [type] $departureDate
     * @param [type] $returnDate
     * @param [type] $newDepartureDate
     * @param [type] $newReturnDate
     * @return boolean True si modifica y false si no puede crear, borrar u obtener el viaje
     */
    public static function modify($continent, $country, $place, $departureDate, $returnDate, $newDepartureDate, $newReturnDate): bool
    {
        $trip = Trip::getTrip($continent, $country, $place, $departureDate, $returnDate);

        $datosTrip = $trip->getDatos();

        $datosTrip['departureDate'] = $newDepartureDate;
        $datosTrip['returnDate'] = $newReturnDate;

        if (Trip::delete($continent, $country, $place, $departureDate, $returnDate) && !empty($trip)) {
            return Trip::create($datosTrip);
        }
        return false;
    }

    /**
     * Devuelve los datos del objeto implicito
     *
     * @return array datos del objeto implícito
     */
    public function getDatos(): array
    {
        return $this->datos;
    }

    /**
     * Devuelve todos los viajes de la base de datos
     *
     * @return array array con todos los viajes
     */
    public static function getAll(): array
    {
        $conn = parent::conectar();

        $query = "SELECT t.departureDate, t.returnDate, 
                         t.continent, t.country, t.place, 
                         i.price, i.img
                  FROM " . TABLA_VIAJES . " t
                  INNER JOIN " . TABLA_INFO . " i 
                  ON t.continent = i.continent 
                    AND t.country = i.country 
                    AND t.place = i.place 
                  WHERE t.departureDate >= NOW()
                    ORDER BY t.continent, t.country, t.place,t.departureDate,t.returnDate";

        try {
            $stmt = $conn->query($query);
            return $stmt->fetchAll(PDO::FETCH_ASSOC);
        } catch (PDOException $e) {
            error_log('Trip::getAllTrips ' . $e->getMessage());
            return [];
        }
    }

    
    /**
     * Obtiene un array con los países agrupados por continente, es decir, 
     * el array devuelto tiene como claves los continentes y como valores arrays con los países de cada continente.
     *
     * @return array
     */
    public static function getCountriesByContinents(): array
    {
        $conn = parent::conectar();
        $query = "SELECT DISTINCT t.continent, t.country
                  FROM " . TABLA_VIAJES . " t 
                  INNER JOIN " . TABLA_INFO . " i 
                    ON t.continent = i.continent 
                   AND t.country = i.country 
                   AND t.place = i.place 
                  ORDER BY t.continent,t.country";

        try {
            $stmt = $conn->prepare($query);
            $stmt->execute();
            //Agrupamos por la primera columna y los valores son la segunda columna
            return $stmt->fetchAll(PDO::FETCH_GROUP | PDO::FETCH_COLUMN);
        } catch (PDOException $e) {
            error_log("Trips::getCountriesByContinents: " . $e->getMessage());
            return [];
        }
    }
}
