package Persona

    class Persona{
        private String nombre;

        Persona(String name){
            nombre = name;
        }
        String saludar(){
            return "Hola me llamo " + nombre;
        }

        void cambiaNombre(String n){
            nombre = n;
        }
        static void main(){
            Persona pepe = new Persona("Pepe");
            System.out.println(pepe.saludar());
            pepe.cambiaNombre("Samuel");
            System.out.println(pepe.saludar());
        }
    }
