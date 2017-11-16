#ifndef Boleto_h
#define Boleto_h

#include "Evento.h"

using namespace std;

class Boleto {

    private:
        double precio;
        int disponibilidad;

    public:
        // Constructor
        Boleto(double, int);
        // Getters
        double getPrecio()      {return precio;}
        int getDisponibilidad() {return disponibilidad;}
        // Metodos
        void retira(int);
};

Boleto::Boleto(double precio, int disponibilidad){
    this->precio = precio;
    this->disponibilidad = disponibilidad;
}

void Boleto::retira(int cant){
    disponibilidad -= cant;
}

#endif
