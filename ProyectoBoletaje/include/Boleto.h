#include "Evento.h"

using namespace std;

class Boleto {

    private:
        double precio;
        int disponibilidad;

    public:
        // Constructores
        Boleto(double, int);
        // Getters
        double getPrecio() {return precio;}
        int getDisponibilidad() {return disponibilidad;}
};

Boleto::Boleto(double precio, int disponibilidad){
    this->precio = precio;
    this->disponibilidad = disponibilidad;
}
