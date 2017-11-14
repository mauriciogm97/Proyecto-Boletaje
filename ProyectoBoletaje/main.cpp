#include <iostream>
#include <vector>
#include <fstream>
#include <iomanip>
#include <ctime>

#include "Deporte.h"
#include "Concierto.h"
#include "Familiar.h"
#include "TeatroCultura.h"
#include "Usuario.h"

using namespace std;

vector<Evento*> eventos;
vector<Usuario> usuarios;
time_t now = time(0);
tm *ltm = localtime(&now);
Date hoy(ltm->tm_mday, 1 + ltm->tm_mon, 1900 + ltm->tm_year);


void iniciarSistema(){
    // Bienvenida y despliegue de fecha;
    cout << "Bienvenido a su sistema TicketMaster" << endl;
    time_t now = time(0);
    string dt = ctime(&now);
    cout << dt << endl;

    // Lectura de archivo eventos
    ifstream fin;
    fin.open("Eventos.txt");
    int cant, d, m, a, h, min, disp;
    char tipo;
    string lugar, ciudad;
    fin >> cant;

    for (int i = 0; i < cant; i++){

        fin >> tipo >> lugar >> d >> m >> a >> h >> min;
        Date fecha(d, m, a, h, min);

        switch (tipo){

            case 'C':{
                string genero, artista;
                fin >> genero >> artista >> ciudad;
                Evento *evento = new Concierto (lugar, fecha, artista, genero, ciudad, 'C');
                eventos.push_back(evento);
                break;
            }

            case 'D':{
                string categoria, detalles;
                fin >> categoria >> detalles >> ciudad;
                Evento *evento = new Deporte (lugar, fecha, categoria, detalles, ciudad, 'D');
                eventos.push_back(evento);
                break;
            }

            case 'T':{
                string categoria, nombre;
                fin >> categoria >> nombre >> ciudad;
                Evento *evento = new TeatroCultura (lugar, fecha, categoria, nombre, ciudad, 'T');
                eventos.push_back(evento);
                break;
            }

            case 'F':{
                string categoria, nombre;
                fin >> categoria >> nombre >> ciudad;
                Evento *evento = new Familiar (lugar, fecha, categoria, nombre, ciudad, 'F');
                eventos.push_back(evento);
                break;
            }
        }
    }
    fin.close();

    // Lectura archivo boletos
    string nombre;
    int disponibilidad;
    double precio;
    Evento* evento = NULL;
    fin.open("Usuarios.txt");
    while (fin >> nombre){
        fin >> cant;
        for (int x = 0; x < eventos.size(); x++){
            if (nombre == eventos[x]->nombre)
        }
    }

    fin.close();

    // Lectura archivo usuarios
    string mail, pass, apellido;
    fin.open("Usuarios.txt");
    while (fin >> mail){
        fin >> pass >> nombre >> apellido;
        usuarios.push_back(Usuario(mail, pass, nombre, apellido));
    }
    fin.close();
}

void cerrarSistema(){
    //ofstream fout;
    //fout.open("Eventos.txt");
    //fout.close();
}

void autenticacion(){
    char opcion;
    string mail, pass;
    bool autenticado = false;
    do {
        cout << endl << "Teclee la opcion: \n1.Iniciar sesion \n2.Registrarse\n";
        cin >> opcion;

        switch (opcion){
            case '1':
                cout << "Ingrese su eMail" << endl;
                cin >> mail;
                cout << "Ingrese su password" << endl;
                cin >> pass;
                for (int x = 0; x < usuarios.size(); x++){
                    if (usuarios[x].getEMail() == mail && usuarios[x].checkPassword(pass)){
                        autenticado = true;
                        cout << "Bienvenido" << endl;
                    }
                }
                if (!autenticado){
                    cout << "Credenciales incorrectas o inexistentes." << endl;
                }
                break;
            case '2':
                char mayor;
                cout << "Teclea 1 si eres mayor de edad, u otra tecla si eres menor" << endl;
                cin >> mayor;
                if (mayor == '1'){
                    usuarios.push_back(Usuario());
                    autenticado = true;
                    cout << "Usuario creado, bienvenido a TICKETMASTER" << endl;
                }
                break;
        };
    }while(!autenticado);
}

Evento* despliegaMenu(){

    char iOpcion, tipo, opcfecha;
    string ubicacion;
    cout<<"\nMENU (Teclea el numero)\n---------------------\n1) Consultar eventos por fecha\n2) Consultar eventos por ubicacion\n3) Consultar evento por tipo\n4) Terminar\n";
    cin >> iOpcion;

    switch (iOpcion){

        //BUSQUEDA POR FECHA
        case '1':{

            cout << endl << "Elija una fecha." << endl << "_________________" << endl;
            cout << "1) Hoy" << endl << "2) Esta semana" << endl << "3) Este mes" << endl << "4) Este anio" << endl;
            cin >> opcfecha;
            cout << endl;

            switch (opcfecha) {

                //Eventos de hoy
                case '1':{
                    bool encontrado = false;
                    for (int i=0; i < eventos.size(); i++){
                        if (eventos[i]->getFecha() == hoy) {
                            eventos[i]->muestra();
                            encontrado = true;
                        }
                    }
                    if(!encontrado) cout << "No hay eventos el dia de hoy." << endl;
                    break;
                }

                //Eventos esta semana
                case '2':{
                    bool encontrado = false;
                    Date fecha2 = hoy+7;
                    for (int i=0; i<eventos.size(); i++){
                        if (eventos[i]->getFecha() >= hoy && eventos[i]->getFecha() <= fecha2) {
                            eventos[i]->muestra();
                            encontrado = true;
                        }
                    }
                    if(!encontrado) cout << "No hay eventos esta semana." << endl;
                    break;
                }

                //Eventos este mes
                case '3':{
                    bool encontrado = false;
                    for (int i=0; i<eventos.size(); i++){
                        if (eventos[i]->getFecha().getMes() == 1 + ltm->tm_mon) {
                            eventos[i]->muestra();
                            encontrado = true;
                        }
                    }
                    if(!encontrado) cout << "No hay eventos este mes." << endl;
                    break;
                }

                //Eventos este anio
                case '4':{
                    bool encontrado = false;
                    for (int i=0; i<eventos.size(); i++){
                        if (eventos[i]->getFecha().getYear()== 1900 + ltm->tm_year) {
                            eventos[i]->muestra();
                            encontrado = true;
                        }
                    }
                    if(!encontrado) cout << "No hay eventos este mes." << endl;
                    break;
                }

                default:{
                    cout << "Esa opcion no existe." << endl;
                    break;
                }
            }
            break;
        }

        //BUSQUEDA POR CIUDAD
        case '2':{
            cout << "Teclee su ciudad." << endl;
            cin >> ubicacion;
            cout << endl;
            bool encontrado = false;
            for (int i=0; i<eventos.size(); i++){
                if (eventos[i]->getCiudad() == ubicacion){
                    eventos[i]->muestra();
                    encontrado = true;
                }
            }
            if (!encontrado) {
                cout << "La ciudad " << ubicacion << " no existe." << endl;
            }
            break;
        }

        //BUSQUEDA POR TIPO DE EVENTO
        case '3':{
            cout << "Que tipo de evento busca? (1=Deporte, 2=Concierto, 3=Familiar, 4=Teatro y Cultura)" << endl;
            cin >> tipo;
            cout << endl;
            switch(tipo){
                case '1':
                    for (int i=0; i<eventos.size(); i++){
                        if (eventos[i]->getCategoria()=='D') eventos[i]->muestra();
                    }
                    break;
                case '2':
                    for (int i=0; i<eventos.size(); i++){
                        if (eventos[i]->getCategoria()=='C') eventos[i]->muestra();
                    }
                    break;
                case '3':
                    for (int i=0; i<eventos.size(); i++){
                        if (eventos[i]->getCategoria()=='F') eventos[i]->muestra();
                    }
                    break;
                case '4':
                    for (int i=0; i<eventos.size(); i++){
                        if (eventos[i]->getCategoria()=='T') eventos[i]->muestra();
                    }
                    break;
                default:
                    cout << "Esa opcion no existe." << endl;
                    break;
            }
            break;
        }

        case '4':
            break;

        default:
            cout << "Esa opcion no existe." << endl;
            break;
    }
}


int main(){
    iniciarSistema();
    autenticacion();

    Evento *evento = NULL;
    while(evento == NULL){
        evento = despliegaMenu();
    }

    cerrarSistema();

}
