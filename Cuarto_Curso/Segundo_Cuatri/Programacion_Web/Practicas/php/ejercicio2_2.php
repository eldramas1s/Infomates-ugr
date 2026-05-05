<?php

class formBuilder
{
    private $arrayFields = [];

    /*Metodos publicos*/
    /**
     * Constructor para crear un formulario de campos de texto
     *
     *
     * @param array $arrayBasic array de arrays de campos del formulario
     */
    public function __construct($arrayBasic)
    {

        foreach ($arrayBasic as $index => $field) {
            // 1. Comprobar que sea un array y tenga exactamente 4 elementos
            if (!is_array($field) || count($field) !== 4) {
                throw new InvalidArgumentException("El campo en el índice $index debe ser una cuadrupleta (id, name, default, label).");
            }

            // 2. Opcional: Validar que los elementos importantes sean strings
            // $field[0] = id, $field[1] = name
            if (!is_string($field[0]) || !is_string($field[1])) {
                throw new InvalidArgumentException("ID y Name en el índice $index deben ser texto.");
            }
        }
        $this->arrayFields = $arrayBasic;
    }

    public function addNewField($id, $name, $default, $label)
    {
        if (!is_string($id) || !is_string($name)) {
            throw new InvalidArgumentException("ID y Name deben ser texto.");
        }

        $newField = [$id, $name, $default, $label];
        $this->arrayFields[] = $newField;
    }


    public function htmlForm($action, $method){
        if(empty($this->arrayFields))
            {
                return "";
            }
        if (!is_string($action) || !is_string($method)) 
            {
                throw new InvalidArgumentException("ID y Name deben ser texto.");
            }
        $html = "<form action=\"$action\" method=\"$method\">";

        // Recorremos cada sección por su índice
        for($i=0; $i<count($this->arrayFields) ; $i++) 
            {
                $html.= $this->htmlField($i);
            }
        return $html;
    }
    /*Metodos privados*/
    private function htmlField($i)
    {
        if (!isset($this->arrayFields[$i])) 
            {
                return "";
            }

        $field = $this->arrayFields[$i];

        return "<label for=\"{$field[0]}\">{$field[3]}</label> 
        <input type=\"text\" id=\"{$field[0]}\" name=\"{$field[1]}\" value=\"{$field[2]}\">
        ";

    }
}
