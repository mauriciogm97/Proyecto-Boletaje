#ifndef Evento_h
#define Evento_h

#include <sstream>
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
    Boleto* compraBoletos(int&);
    string salvaBoletos();
};

Evento::Evento(string nombre, string lugar, string ciudad, Date fecha, char categoria){
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

Boleto* Evento::compraBoletos(int &cant){
    if (boletos.empty()){
        cout << "Ya no hay boletos disponibles" << endl;
        return NULL;
    }
    int seleccion, confirm;
    for (int x = 0; x < boletos.size(); x++){
        if (boletos[x].getDisponibilidad() > 0){
            cout << "Opcion #" << x << " Precio: " << boletos[x].getPrecio() << endl;
        }
    }
    cout << "Seleccione el boleto a comprar con el numero de opcion" << endl;
    cin >> seleccion;
    if (seleccion >= 0 && seleccion < boletos.size()){
        cout << "Digite la cantidad de boletos a comprar" << endl;
        cin >> cant;
        cout << "Confirme su compra presionando 1, u otro boton para cancelar" << endl;
        cin >> confirm;
        if (confirm == 1){
            boletos[seleccion].retira(cant);
            cout << boletos[seleccion].getDisponibilidad() << endl;
            return &boletos[seleccion];
        }
    }
    cout << "No se realizo compra" << endl;
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
