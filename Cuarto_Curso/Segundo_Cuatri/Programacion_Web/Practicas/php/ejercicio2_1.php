<?php
class Calculadora
{
    protected $a;
    protected $b;


    function __construct($a, $b)
    {
        if (is_numeric($a) && is_numeric($b)) {
            $this->a = $a;
            $this->b = $b;
        } else {
            $this->a = 0;
            $this->b = 0;
        }
    }

    function setValues($a, $b)
    {
        if (is_numeric($a) && is_numeric($b)) {
            $this->a = $a;
            $this->b = $b;
        }
    }

    function suma()
    {
        return $this->a + $this->b;
    }

    function resta()
    {
        return $this->a + $this->b;
    }

    function multiplica()
    {
        return $this->a * $this->b;
    }

    function divide()
    {
        return $this->b <> 0 ? $this->a / $this->b : "Division by zero";
    }
}

class CalculadoraAvanzada extends Calculadora
{
    function mcd()
    {

        $a = abs($this->a);
        $b = abs($this->b);

        while ($b !== 0) {
            $resto = $a % $b;
            $a = $b;
            $b = $resto;
        }

        return $a;
    }

    function mcm()
    {
        return abs($this->a * $this->b) / $this->mcd();
    }

    function pow()
    {
        if ($this->b == 0) return 1;
        if ($this->b < 0) return "No se hacer exponentes negativos";

        $res = 1;

        if (fmod($this->b, 1) !== 0.0) {
            return pow($this->a, $this->b);
        }

        // Algoritmo de Exponenciación Binaria
        while ($this->b > 0) {
            if ($this->b % 2 == 1) {
                $res *= $this->a;
            }
            $this->a *= $this->a;
            $this->b = (int)($this->b / 2);
        }

        return $res;
    }
}
