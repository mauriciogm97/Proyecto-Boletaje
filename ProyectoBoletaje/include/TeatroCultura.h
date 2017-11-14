#include "Evento.h"

using namespace std;

class TeatroCultura : public Evento{

    private:
        string categoria;
        string nombre;

    public:
        // Constructor
        TeatroCultura(string, Date, string, string, string, char);
        // Getters
        string getCategoria();
        string getNombre();

        void muestra();
};

void TeatroCultura:: muestra(){

    cout << "Obra con genero de " << categoria << endl;
    cout << nombre << endl;
    cout << "Ciudad: " << ciudad << endl;
    cout << "Lugar: " << getLugar() << endl;
    cout << "Fecha: "; getFecha().printFecha();
    cout << "Hora: "; getFecha().printHora();
    cout << endl;
}

TeatroCultura::TeatroCultura(string lugar, Date fecha, string categoria, string nombre, string ciudad, char cat): Evento(lugar, fecha, ciudad, cat){
    this->categoria = categoria;
    this->nombre = nombre;
}

string TeatroCultura::getCategoria(){
    return categoria;
}

string TeatroCultura::getNombre(){
    return nombre;
}
