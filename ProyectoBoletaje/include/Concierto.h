#include "Evento.h"

using namespace std;

class Concierto : public Evento{

    private:
        string artista;
        string genero;

    public:
        // Constructor
        Concierto(string, Date, string, string, string, char);
        // Getters
        string getArtista();
        string getGenero();
        //
        void muestra();
};

void Concierto:: muestra(){

    cout << "Concierto de " << genero << endl;
    cout << artista << endl;
    cout << "Ciudad: " << ciudad << endl;
    cout << "Lugar: " << getLugar() << endl;
    cout << "Fecha: "; getFecha().printFecha();
    cout << "Hora: "; getFecha().printHora();
    cout << endl;
}

Concierto::Concierto(string lugar, Date fecha, string artista, string genero, string ciudad, char cat): Evento(lugar, fecha, ciudad, cat){
    this->artista = artista;
    this->genero = genero;
}

string Concierto::getArtista(){
    return artista;
}

string Concierto::getGenero(){
    return genero;
}

