// Prototipo simulador de sistema de boletaje
// Mauricio Guadiana    A01281897
// Kevin Radtke         A01281950
// Cristian Acosta      A00820013
// Daniel Tijerina      A01281870

// Librerias incluidas
#include <iostream>
#include <vector>
#include <fstream>
#include <iomanip>
#include <ctime>

// Objetos incluidos
#include "Evento.h"
#include "Usuario.h"

using namespace std;

// Variables globales
vector<Evento> eventos;
vector<Usuario> usuarios;
time_t now = time(0);
tm *ltm = localtime(&now);
Date hoy(ltm->tm_mday, 1 + ltm->tm_mon, 1900 + ltm->tm_year);

// Funcion que lee los datos de los archivos para iniciar el sistema
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
        eventos.push_back(Evento(nombre, lugar, ciudad, tipo, d, m, a, h, min));
    }
    fin.close();

    // Lectura archivo boletos
    int cant, disponibilidad;
    double precio;
    fin.open("Boletos.txt");
    while (fin >> nombre){
        fin >> cant;
        for (int i = 0; i < eventos.size(); i++){
            if (nombre == eventos[i].getNombre()){
                for (int j = 0; j < cant; j++){
                    fin >> precio >> disponibilidad;
                    if (disponibilidad > 0) eventos[i].addBoleto(precio, disponibilidad);
                }
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

// Funcion que controla la autenticacion y otorga o restringe el accesso al sistema
void autenticacion(){
    char opcion;
    string mail, pass;
    bool autenticado = false;
    do {
        cout << endl << "Teclee la opcion: \n1.Iniciar sesion \n2.Registrarse\n";
        cin >> opcion;

        switch (opcion){
            // Inicio de sesion
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
            // Creacion de cuenta (se crea en objeto usuario)
            case '2':
                char mayor;
                cout << "Teclea 1 si eres mayor de edad, u otra tecla si eres menor" << endl;
                cin >> mayor;
                if (mayor == '1'){
                    usuarios.push_back(Usuario());
                    autenticado = true;
                    cout << "Usuario creado, bienvenido a TICKETMASTER" << endl;
                } else {
                    cout << "Debes ser mayor de edad para crear una cuenta" << endl;
                }
            break;
        };
    }while(!autenticado);
}

// Funcion que despliega menu y retorna evento seleccionado
Evento* despliegaMenu(char &iOpcion){

    int seleccion = 0, eleccion;
    vector<Evento*> mostrados;
    char tipo, opcfecha;
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

            switch (opcfecha){

                //Eventos de hoy
                case '1':{
                    bool encontrado = false;
                    for (int i=0; i<eventos.size(); i++){
                        if (eventos[i].getFecha() == hoy) {
                            eventos[i].muestra(seleccion++);
                            mostrados.push_back(&eventos[i]);
                            encontrado = true;
                        }
                    }
                    if(!encontrado){
                        cout << "No hay eventos el dia de hoy." << endl;
                        return NULL;
                    }
                    break;
                }

                //Eventos esta semana
                case '2':{
                    bool encontrado = false;
                    Date fecha2 = hoy+7;
                    for (int i=0; i<eventos.size(); i++){
                        if (eventos[i].getFecha() >= hoy && eventos[i].getFecha() <= fecha2) {
                            eventos[i].muestra(seleccion++);
                            mostrados.push_back(&eventos[i]);
                            encontrado = true;
                        }
                    }
                    if(!encontrado){
                        cout << "No hay eventos esta semana." << endl;
                        return NULL;
                    }
                    break;
                }

                //Eventos este mes
                case '3':{
                    bool encontrado = false;
                    for (int i=0; i<eventos.size(); i++){
                        if (eventos[i].getFecha().getMes() == 1 + ltm->tm_mon) {
                            eventos[i].muestra(seleccion++);
                            mostrados.push_back(&eventos[i]);
                            encontrado = true;
                        }
                    }
                    if(!encontrado){
                        cout << "No hay eventos este mes." << endl;
                        return NULL;
                    }
                    break;
                }

                //Eventos este anio
                case '4':{
                    bool encontrado = false;
                    for (int i=0; i<eventos.size(); i++){
                        if (eventos[i].getFecha().getYear()== 1900 + ltm->tm_year) {
                            eventos[i].muestra(seleccion++);
                            mostrados.push_back(&eventos[i]);
                            encontrado = true;
                        }
                    }
                    if(!encontrado){
                        cout << "No hay eventos este mes." << endl;
                        return NULL;
                    }
                    break;
                }

                default:{
                    cout << "Esa opcion no existe." << endl;
                    return NULL;
                }
            };
            break;
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
                    mostrados.push_back(&eventos[i]);
                    encontrado = true;
                }
            }
            if (!encontrado) {
                cout << "La ciudad " << ubicacion << " no existe." << endl;
                return NULL;
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
                            mostrados.push_back(&eventos[i]);
                        }
                    }
                    break;
                case '2':
                    for (int i=0; i<eventos.size(); i++){
                        if (eventos[i].getCategoria()=='C'){
                            eventos[i].muestra(seleccion++);
                            mostrados.push_back(&eventos[i]);
                        }
                    }
                    break;
                case '3':
                    for (int i=0; i<eventos.size(); i++){
                        if (eventos[i].getCategoria()=='F'){
                            eventos[i].muestra(seleccion++);
                            mostrados.push_back(&eventos[i]);
                        }
                    }
                    break;
                case '4':
                    for (int i=0; i<eventos.size(); i++){
                        if (eventos[i].getCategoria()=='T'){
                            eventos[i].muestra(seleccion++);
                            mostrados.push_back(&eventos[i]);
                        }
                    }
                    break;
                default:
                    cout << "Esa opcion no existe." << endl;
                    return NULL;
            };
            break;
        }

        case '4':
            return NULL;

        default:
            cout << "Esa opcion no existe." << endl;
            return NULL;
    };

    // Pedir al usuario la seleccion de evento (solo si pidio busqueda)
    cout << "Seleccione el evento por su numero" << endl;
    cin >> eleccion;
    if (eleccion >= 0 && eleccion < mostrados.size()){
        return mostrados[eleccion];
    }
    cout << "Seleccion incorrecta" << endl;
    return NULL;
}

// Funcion que escribe documento de texto con datos de compra
void outputCompra(Evento evento, Boleto boleto, int cant){
    // Escritura de archivo
    ofstream fout;
    fout.open("Compra.txt");
    fout << "Entrada: " << evento.getNombre() << endl;
    fout << "Fecha: " << evento.getFecha().getFechaStr() << endl;
    fout << "Lugar: " << evento.getLugar() << " " << evento.getCiudad() << endl;
    fout << "Precio: $" << boleto.getPrecio() << endl;
    fout << "Cantidad comprada: " << cant << endl;
    fout << "Cobro: $" << boleto.getPrecio() * cant << endl;
    fout.close();
    // Despliegue de info de compra al usuario
    cout << endl;
    cout << "Entrada: " << evento.getNombre() << endl;
    cout << "Fecha: " << evento.getFecha().getFechaStr() << endl;
    cout << "Lugar: " << evento.getLugar() << " " << evento.getCiudad() << endl;
    cout << "Precio: $" << boleto.getPrecio() << endl;
    cout << "Cantidad comprada: " << cant << endl;
    cout << "Cobro: $" << boleto.getPrecio() * cant << endl;
}

// Funcion que controla la realizacion de una compra
void realizaCompra(Evento* evento){
    int count = 0, confirm, cant;
    cout << "A continuacion se presentan los boletos disponibles" << endl;
    // La muestra y seleccion de boletos se da en evento
    Boleto *compra = evento->muestraBoletos();
    if (compra){
        do {
            cout << "Digite la cantidad de boletos a comprar" << endl;
            cin >> cant;
            if (cant > compra->getDisponibilidad()){
                cout << "No hay tantos boletos disponibles" << endl;
            }
        } while (cant > compra->getDisponibilidad());
        cout << "Confirme su compra presionando 1, u otro boton para cancelar" << endl;
        cin >> confirm;
        if (confirm == 1){
            compra->retira(cant);
            outputCompra(*evento, *compra, cant);
            cout << "Se creo archivo de recibo con la informacion de compra" << endl;
        }
    } else {
        cout << "No se realizo compra" << endl;
    }
}

// Funcion que cierra sistema y salva cambios en archivos txt
void cerrarSistema(){
    // Reescribe archivo de boletos
    ofstream fout;
    fout.open("Boletos.txt");
    for (int x = 0; x < eventos.size(); x++){
        fout << eventos[x].salvaBoletos();
    }
    fout.close();
}

// Funcion que lleva el control del programa
int main(){
    iniciarSistema();
    autenticacion();

    char opcion;
    Evento *seleccion = new Evento;
    do {
        seleccion = despliegaMenu(opcion);
        if (opcion == '4') return -1;
    } while (!seleccion);

    realizaCompra(seleccion);
    cerrarSistema();

    return 0;
}
