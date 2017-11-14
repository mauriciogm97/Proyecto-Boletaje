#ifndef Evento_h
#define Evento_h

#include "Date.h"
#include "Boleto.h"

using namespace std;

class Evento{

protected:
    string name;
    string lugar;
    string ciudad;
    Date fecha;
    vector<Boleto> boletos;

public:
    // Constructores
    Evento() = default;
    Evento(string lugar, Date fecha, string ciudad);
    // Getters
    string getLugar() {return lugar;}
    string getCiudad() {return ciudad;}
    Date getFecha() {return fecha;}

    //Metodos
    virtual void muestra() = 0;
    addBoleto(double, int);

};

Evento::Evento(string lugar, Date fecha, string ciudad) {
    this->lugar = lugar;
    this->fecha = fecha;
    this->ciudad = ciudad;

}

Evento::addBoleto(double precio, int disponibilidad){
    boletos.push_back(Boleto(precio,disponibilidad));
}

#endif
