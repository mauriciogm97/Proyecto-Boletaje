#include "Evento.h"

using namespace std;

class Familiar : public Evento{

    private:
        string categoria;
        string nombre;

    public:
        // Constructor
        Familiar(string, Date, string, string, string, char);
        // Getters
        string getCategoria();
        string getNombre();

        void muestra();
};

void Familiar:: muestra(){

    cout << "Evento Familiar de " << categoria << endl;
    cout << nombre << endl;
    cout << "Ciudad: " << ciudad << endl;
    cout << "Lugar: " << getLugar() << endl;
    cout << "Fecha: "; getFecha().printFecha();
    cout << "Hora: "; getFecha().printHora();
    cout << endl;
}

Familiar::Familiar(string lugar, Date fecha, string categoria, string nombre, string ciudad, char cat): Evento(lugar, fecha, ciudad, cat){
    this->categoria = categoria;
    this->nombre = nombre;
}

string Familiar::getCategoria(){
    return categoria;
}

string Familiar::getNombre(){
    return nombre;
}
