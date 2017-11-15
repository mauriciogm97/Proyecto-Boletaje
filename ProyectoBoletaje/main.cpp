#include <iostream>
#include <vector>
#include <fstream>
#include <iomanip>
#include <ctime>

#include "Evento.h"
#include "Usuario.h"

using namespace std;

vector<Evento> eventos;
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
    int d, m, a, h, min;
    char tipo;
    string nombre, lugar, ciudad;
    while (fin >> tipo){
        fin >> nombre >> lugar >> ciudad >> d >> m >> a >> h >> min;
        Date fecha(d, m, a, h, min);
        eventos.push_back(Evento(nombre, lugar, ciudad, fecha, 'C'));
    }
    fin.close();

    // Lectura archivo boletos
    int cant, disponibilidad;
    double precio;
    fin.open("Usuarios.txt");
    while (fin >> nombre){
        fin >> cant >> precio >> disponibilidad;
        for (int x = 0; x < eventos.size(); x++){
            if (nombre == eventos[x].getNombre()){
                eventos[x].addBoleto(precio, disponibilidad);
            }
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

    int seleccion = 0, eleccion;
    vector<Evento> mostrados;
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
                    for (int i=0; i<eventos.size(); i++){
                        if (eventos[i].getFecha() == hoy) {
                            eventos[i].muestra(seleccion++);
                            mostrados.push_back(eventos[i]);
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
                        if (eventos[i].getFecha() >= hoy && eventos[i].getFecha() <= fecha2) {
                            eventos[i].muestra(seleccion++);
                            mostrados.push_back(eventos[i]);
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
                        if (eventos[i].getFecha().getMes() == 1 + ltm->tm_mon) {
                            eventos[i].muestra(seleccion++);
                            mostrados.push_back(eventos[i]);
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
                        if (eventos[i].getFecha().getYear()== 1900 + ltm->tm_year) {
                            eventos[i].muestra(seleccion++);
                            mostrados.push_back(eventos[i]);
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
        }

        //BUSQUEDA POR CIUDAD
        case '2':{
            cout << "Teclee su ciudad." << endl;
            cin >> ubicacion;
            cout << endl;
            bool encontrado = false;
            for (int i=0; i<eventos.size(); i++){
                if (eventos[i].getCiudad() == ubicacion){
                    eventos[i].muestra(seleccion++);
                    mostrados.push_back(eventos[i]);
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
                        if (eventos[i].getCategoria()=='D'){
                            eventos[i].muestra(seleccion++);
                            mostrados.push_back(eventos[i]);
                        }
                    }
                    break;
                case '2':
                    for (int i=0; i<eventos.size(); i++){
                        if (eventos[i].getCategoria()=='C'){
                            eventos[i].muestra(seleccion++);
                            mostrados.push_back(eventos[i]);
                        }
                    }
                    break;
                case '3':
                    for (int i=0; i<eventos.size(); i++){
                        if (eventos[i].getCategoria()=='F'){
                            eventos[i].muestra(seleccion++);
                            mostrados.push_back(eventos[i]);
                        }
                    }
                    break;
                case '4':
                    for (int i=0; i<eventos.size(); i++){
                        if (eventos[i].getCategoria()=='T'){
                            eventos[i].muestra(seleccion++);
                            mostrados.push_back(eventos[i]);
                        }
                    }
                    break;
                default:
                    cout << "Esa opcion no existe." << endl;
                    break;
            }
            break;
        }

        case '4':
            return NULL;

        default:
            cout << "Esa opcion no existe." << endl;
            return NULL;
    }
    cout << "Seleccione el evento por su numero" << endl;
    cin >> eleccion;
    if (eleccion >= 0 && eleccion < mostrados.size()){
        return &mostrados[eleccion];
    }
    cout << "Seleccion incorrecta" << endl;
    return NULL;
}

void outputCompra(Evento evento, Boleto boleto){
    ofstream fout;
    fout.open("Compra.txt");
    fout << "Entrada: " << evento.getNombre() << endl;
    fout << "Fecha: " << evento.getFecha().getFechaStr() << endl;
    fout << "Lugar: " << evento.getLugar() << " " << evento.getCiudad() << endl;
    fout << "Precio " << "$" << boleto.getPrecio() << endl;
    fout.close();
}

void realizaCompra(Evento evento){
    int count = 0, cant, confirm;
    cout << "A continuacion se presentan los boletos disponibles" << endl;
    Boleto *compra = evento.muestraBoletos();
    if (compra){
        cout << "Digite la cantidad de boletos a comprar" << endl;
        cin >> cant;
        cout << "Confirme su compra presionando 1, u otro boton para cancelar" << endl;
        cin >> confirm;
        if (confirm == 1){
            compra->retira(cant);
            outputCompra(evento, *compra);
            cout << "Se creo archivo con informacion de compra" << endl;
        } else {
            cout << "Compra cancelada" << endl;
        }
    }
}

void cerrarSistema(){
    // Reescribe archivo de boletos
    ofstream fout;
    fout.open("Boletos.txt");
    for (int x = 0; x < eventos.size(); x++){
        fout << eventos[x].salvaBoletos();
    }
    fout.close();
}

int main(){
    iniciarSistema();

    autenticacion();

    Evento *seleccion = new Evento;
    do {
        seleccion = despliegaMenu();
    } while (!seleccion);

    realizaCompra(*seleccion);

    cerrarSistema();
}
