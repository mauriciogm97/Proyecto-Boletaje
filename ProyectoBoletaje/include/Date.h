
#ifndef Date_h
#define Date_h

using namespace std;

#define YEAR 2017

class Date{

private:
    bool validDate(int, int, int);
    bool validHora(int, int);
    int dia;
    int mes;
    int year;
    int hora;
    int minuto;
    bool esBisiesto();

public:
    // Constructores
    Date();
    Date(int, int, int);
    Date(int, int, int, int, int);
    // Metodos
    void printFecha();
    void printHora();
    
    //Operadores
    Date operator+(int dias);
    bool operator>=(Date f);
    bool operator<=(Date f);
    bool operator==(Date f);
    
    //Getter
    int getYear(){return year;}
    int getMes(){return mes;}
};

Date::Date(){
//    int dia, mes, year;
//    do {
//        cout << "Ingrese el # de dia (DD)" << endl;
//        cin >> dia;
//        cout << "Ingrese el # de mes (MM)" << endl;
//        cin >> mes;
//        cout << "ingrese el # de anio (AAAA)" << endl;
//        cin >> year;
//    } while(!validDate(dia, mes, year));
//    this->dia = dia;
//    this->mes = mes;
//    this->year = year;
//    
//    int opcion;
//    cout << "Va agregar hora? (1 = SI / 0 = NO)" << endl;
//    cin >> opcion;
//    if (opcion == 1){
//        int hora, minuto;
//        do{
//            cout << "Ingrese la hora (HH)" << endl;
//            cin >> hora;
//            cout << "Ingrese el minuto (MM)" << endl;
//            cin >> minuto;
//        } while (!validHora(hora,minuto));
//    }
}

bool Date::operator==(Date f){
    return (((year == f.year) && (mes == f.mes) && (dia == f.dia)));
}

Date::Date(int dia, int mes , int year){
    this->dia = dia;
    this->mes = mes;
    this->year = year;
}

Date::Date(int dia, int mes, int year, int hora, int minuto){
    this->dia = dia;
    this->mes = mes;
    this->year = year;
    this->hora = hora;
    this->minuto = minuto;
}

bool Date::validDate(int dia, int mes, int year){
    if (year < YEAR && year > YEAR + 2)
        return false;
    if ((mes == 1 || mes == 3 || mes == 5 || mes == 7 || mes == 8 || mes == 10 || mes == 12) && (dia < 1 || dia > 31))
        return false;
    if ((mes == 4 || mes == 6 || mes == 9 || mes == 11) && (dia < 1 || dia > 30))
        return false;
    if (mes == 2){
        if (((year % 4 == 0 && year % 100 != 0) || (year % 4 == 0 &&  year % 400 == 0)) && (dia < 1 || dia > 29))
            return false;
        else if (dia < 1 || dia > 28)
            return false;
    }

    return true;
}

bool Date::validHora(int hora, int minuto){
    if (hora < 0 || hora > 23) return false;
    if (minuto < 0 || minuto > 59) return false;
    return true;
}

void Date::printFecha(){
    cout << dia << "/" << mes << "/" << year << endl;
}

void Date::printHora(){
    cout<<setw(2)<<setfill('0')<<hora<<":"<<setw(2)<<setfill('0')<<minuto<<endl;
}

Date Date::operator+(int dias){
    //Suma una cantidad de dias a una fecha, tomando en cuenta que puede sobrepasar meses y anios, ademas de verificar si el anio es bisiesto para contar el dia extra.
    //Se usa un switch para determinar la cantidad de dias de cada mes. Al pasar de un mes a otro, la variable de dia se hace 0 para sumar los dias restantes al siguiente mes. El metodo se acaba hasta que la cantidad de dias restantes a sumar sea 0.
    
    Date f = Date(dia,mes,year);
    
    do{
        
        bool b = esBisiesto();
        
        switch (f.mes){
                
            case 1:
            case 3:
            case 5:
            case 7:
            case 8:
            case 10:
                
                if (f.dia+dias > 31){
                    dias -= (31-f.dia);
                    f.mes++;
                    f.dia = 0;
                }
                else{
                    f.dia += dias;
                    dias = 0;
                }
                break;
                
            case 2:
                
                if(b){
                    
                    if (f.dia+dias > 29){
                        dias -= (29-f.dia);
                        f.mes++;
                        f.dia = 0;
                    }
                    else{
                        f.dia += dias;
                        dias = 0;
                    }
                }
                
                else{
                    if (f.dia+dias > 28){
                        dias -= (28-f.dia);
                        f.mes++;
                        f.dia = 0;
                    }
                    else{
                        f.dia += dias;
                        dias = 0;
                    }
                }
                break;
                
            case 4:
            case 6:
            case 9:
            case 11:
                
                if (f.dia+dias > 30){
                    dias -= (30-f.dia);
                    f.mes++;
                    f.dia = 0;
                }
                else{
                    f.dia += dias;
                    dias = 0;
                }
                break;
                
            case 12:
                
                if (f.dia+dias > 31){
                    dias -= (31-f.dia);
                    f.mes = 1;
                    f.dia = 0;
                    f.year++;
                }
                else{
                    f.dia += dias;
                    dias = 0;
                }
                break;
                
            default:
                return f;
                break;
        }
    }while(dias>0);
    
    return f;
}

bool Date::operator>=(Date f){
    if (year > f.year) return true;
    if ((year == f.year) && (mes > f.mes)) return true;
    if (((year == f.year) && (mes == f.mes) && (dia > f.dia))) return true;
    if (((year == f.year) && (mes == f.mes) && (dia == f.dia))) return true;
    else return false;
}

bool Date::operator<=(Date f){
    if (year < f.year) return true;
    if ((year == f.year) && (mes < f.mes)) return true;
    if (((year == f.year) && (mes == f.mes) && (dia < f.dia))) return true;
    if (((year == f.year) && (mes == f.mes) && (dia == f.dia))) return true;
    else return false;
}

bool Date::esBisiesto(){
    return (( year % 4 == 0 ) && ((year % 100 != 0)||(year % 400 == 0)));
}

#endif /* Date_h */
