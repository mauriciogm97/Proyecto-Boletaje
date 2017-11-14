#include "Date.h"

using namespace std;

class DateTime: public Date{

    private:
        int hora;
        int minuto;

    public:
        // Constructores
        DateTime() = default;
        DateTime(int, int, int, int, int);
        // Metodos
        void printFecha();
};

DateTime::DateTime(int dia, int mes, int year, int hora, int minuto): Date(dia, mes, year){
    this->hora = hora;
    this->minuto = minuto;
}

void DateTime::printFecha(){
    cout << dia << "/" << mes << "/" << year << " " << hora << ":" << minuto << endl;
}
