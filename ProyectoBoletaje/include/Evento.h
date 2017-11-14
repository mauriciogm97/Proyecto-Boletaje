#ifndef Evento_h
#define Evento_h

#include "Date.h"
#include "Boleto.h"

using namespace std;

class Evento{

protected:
    string nombre;
    string lugar;
    string ciudad;
    Date fecha;
    vector<Boleto> boletos;
    char tipo;

public:
    // Constructores
    Evento() = default;
    Evento(string, string, string, Date, char);
    // Getters
    string getNombre() {return nombre;}
    string getLugar() {return lugar;}
    string getCiudad() {return ciudad;}
    Date getFecha() {return fecha;}

    //Metodos
    virtual void muestra() = 0;
    addBoleto(double, int);

};

Evento::Evento(string nombre, string lugar, string ciudad, Date fecha, char tipo) {
    this->nombre = nombre;
    this->lugar = lugar;
    this->ciudad = ciudad;
    this->fecha = fecha;
    this->tipo = tipo;
}

Evento::addBoleto(double precio, int disponibilidad){
    boletos.push_back(Boleto(precio,disponibilidad));
}

#endif
