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
    char categoria;

public:
    // Constructores
    Evento() = default;
    Evento(string, string, string, Date, char);
    // Getters
    string getNombre() {return nombre;}
    string getLugar() {return lugar;}
    string getCiudad() {return ciudad;}
    Date getFecha() {return fecha;}
    char getCategoria() {return categoria;}
    //Metodos
    void addBoleto(double, int);
    void muestra(int);
    void retiraBoleto();

};

Evento::Evento(string nombre, string lugar, string ciudad, Date fecha, char tipo){
    this->nombre = nombre;
    this->lugar = lugar;
    this->ciudad = ciudad;
    this->fecha = fecha;
    this->categoria = categoria;
}

void Evento::addBoleto(double precio, int disponibilidad){
    boletos.push_back(Boleto(precio,disponibilidad));
}

void Evento::muestra(int num){
    cout << "Resultado #" << num << endl;
    cout << nombre << endl;
    cout << lugar << " " << ciudad << endl;
    fecha.printFecha();
    fecha.printHora();
}

void Evento::retiraBoleto(){
    int seleccion;
    for (int x = 0; x < boletos.size(); x++){
        cout << "Precio"
    }
}

#endif
