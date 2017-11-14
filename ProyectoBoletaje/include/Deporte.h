#include "Evento.h"
#include "Date.h"

using namespace std;

class Deporte : public Evento{

    private:
        string categoria;
        string detalles;

    public:
        // Constructor
        Deporte(string, Date, string, string, string);
        // Getters
        string getCategoria();
        string getDetalles();
        //
        void muestra();
};

void Deporte:: muestra(){

    cout << "Evento Deportivo de " << categoria << endl;
    cout << detalles << endl;
    cout << "Ciudad: " << ciudad << endl;
    cout << "Lugar: " << getLugar() << endl;
    cout << "Fecha: "; getFecha().printFecha();
    cout << "Hora: "; getFecha().printHora();
    cout << endl;
}

Deporte::Deporte(string lugar, Date fecha, string categoria, string detalles, string ciudad): Evento(lugar, fecha, ciudad){
    this->categoria = categoria;
    this->detalles = detalles;
}

string Deporte::getCategoria(){
    return categoria;
}

string Deporte::getDetalles(){
    return detalles;
}
