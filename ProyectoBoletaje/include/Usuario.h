#ifndef Usuario_h
#define Usuario_h

#include <string>
#include "Boleto.h"

using namespace std;

class Usuario{

    private:
        string eMail;
        string password;
        string nombre;
        string apellido;

    public:
        // Constructores
        Usuario();
        Usuario(string, string, string, string);
        // Setters
        void setEMail();
        void setPassword();
        void setNombreCompleto();
        void addCompra(Boleto);
        // Getters
        string getEMail();
        bool checkPassword(string);
        string getNombre();
        string getApellido();
        string getPais();
};

Usuario::Usuario(string eMail, string password, string nombre, string apellido){
    this->eMail = eMail;
    this->password = password;
    this->nombre = nombre;
    this->apellido = apellido;
}

Usuario::Usuario(){
    setNombreCompleto();
    setEMail();
    setPassword();
    fstream fs;
    fs.open ("Usuarios.txt", std::fstream::in | std::fstream::out | std::fstream::app);
    fs << eMail << " " << password << " " << nombre << " " << apellido << endl;
    fs.close();
}

void Usuario::setEMail(){
    string eMail;
    do {
        cout << "Teclee su correo electronico." << endl;
        cin >> eMail;
    } while (eMail.find('@') == string::npos || eMail.substr(eMail.find('@'), eMail.length()).find('.') == string::npos);
    this->eMail = eMail;
}

void Usuario::setPassword(){
    string pass1, pass2;
    do {
        cout << "Cree su contrasenia de 8 digitos." << endl;
        cin >> pass1;
        cout << "Confirme su contrasenia a continuacion." << endl;
        cin >> pass2;
    } while(pass1.length() < 8 || pass1.length() >= 15 || pass1 != pass2);
    password = pass1;
}

void Usuario::setNombreCompleto(){
    string nombre, apellido;
    cout << "Ingrese su primer nombre." << endl;
    cin >> nombre;
    cout << "Ingrese su apellido." << endl;
    cin >> apellido;
    this->nombre = nombre;
    this->apellido = apellido;
}

string Usuario::getEMail(){
    return eMail;
}

bool Usuario::checkPassword(string pass){
    return password == pass;
}

string Usuario::getNombre(){
    return nombre;
}

string Usuario::getApellido(){
    return apellido;
}

#endif
