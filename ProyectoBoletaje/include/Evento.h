#ifndef Evento_h
#define Evento_h

#include <sstream>
#include "Date.h"
#include "Boleto.h"

using namespace std;

class Evento{

private:
    string nombre;
    string lugar;
    string ciudad;
    Date fecha;
    vector<Boleto> boletos;
    char categoria;

public:
    // Constructores
    Evento() = default;
    Evento(string, string, string, char, int, int, int ,int ,int);
    // Getters
    string getNombre()      {return nombre;}
    string getLugar()       {return lugar;}
    string getCiudad()      {return ciudad;}
    Date getFecha()         {return fecha;}
    char getCategoria()     {return categoria;}
    // Metodos
    void addBoleto(double, int);
    void muestra(int);
    Boleto* muestraBoletos();
    string salvaBoletos();
};

Evento::Evento(string nombre, string lugar, string ciudad, char categoria, int d, int m, int a, int h, int min){
    this->nombre = nombre;
    this->lugar = lugar;
    this->ciudad = ciudad;
    fecha = Date(d, m, a, h, min);
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

Boleto* Evento::muestraBoletos(){
    if (boletos.empty()){
        cout << "Ya no hay boletos disponibles" << endl;
        return NULL;
    }
    int seleccion, confirm;
    for (int x = 0; x < boletos.size(); x++){
        if (boletos[x].getDisponibilidad() > 0){
            cout << "Opcion #" << x << " Precio: " << boletos[x].getPrecio()
                 << " Disponibilidad: " << boletos[x].getDisponibilidad() << endl;
        }
    }
    cout << "Seleccione el boleto a comprar con el numero de opcion"
         << "Para cancelar teclea otro digito" << endl;
    cin >> seleccion;
    if (seleccion >= 0 && seleccion < boletos.size()){
        return &boletos[seleccion];
    }
    cout << "No se selecciono boleto valido" << endl;
    return NULL;
}

string Evento::salvaBoletos(){
    stringstream str;
    str << nombre << " " << boletos.size();
    for (int x = 0; x < boletos.size(); x++){
        str << " " << boletos[x].getPrecio() << " " << boletos[x].getDisponibilidad();
    }
    str << endl;
    return str.str();
}

#endif
