#ifndef PROYECTOALGORITMOS_TRANSACCION_H
#define PROYECTOALGORITMOS_TRANSACCION_H
#include "iostream"
#include <ctime>

struct fecha{
    int dia = int{};
    int mes = int{};
    int anio = int{};
    fecha(){}
    fecha(int d,int m,int a):dia(d),mes(m),anio(a){}
    fecha(const fecha& other){
        dia = other.dia;
        mes = other.mes;
        anio = other.anio;
    }
};

struct transaccion
{

    double monto;
    std::string emisor;
    std::string receptor;
    fecha fechatransaccion;
    transaccion(){
        monto = double{};
    }

    explicit transaccion(double monto_, std::string e, std::string r, int d,int m, int a):fechatransaccion(d,m,a)
    {
        monto = monto_;
        emisor = std::move(e);
        receptor = std::move(r);
    };
    transaccion(const transaccion& other) {
        monto = other.monto;
        emisor = other.emisor;
        receptor = other.receptor;
        fechatransaccion = other.fechatransaccion;
    }
    void display() const{
        string result;
        cout << "MONTO: " << monto <<endl;
        cout << "Emisor: " << emisor << endl;
        cout << "Receptor: " << receptor << endl;
        cout << "FECHA: " << fechatransaccion.dia << "/"<<fechatransaccion.mes << "/"<<fechatransaccion.anio << endl;
    }
    transaccion& operator=(const transaccion& other){
        if (this == &other){return *this;}
        // Ya una vez verificado que no son la misma direccion. hago el mismo proceso que el constructor
        monto = other.monto;
        emisor = other.emisor;
        receptor = other.receptor;
        fechatransaccion = other.fechatransaccion;
    }

    friend bool operator<(const transaccion& other1,const transaccion& other2);
    friend bool operator<(const string& fecha_,const transaccion& other2);
    friend bool operator>(const string& fecha_,const transaccion& other2);
    friend bool operator>=(const string& fecha_,const transaccion& other2);
    friend bool operator<=(const transaccion &other2,const string& fecha_);
    friend bool operator<=(const transaccion& other1,const transaccion& other2);
    friend bool operator>(const transaccion& other1, const transaccion& other2);
    friend bool operator>=(const transaccion& other1, const transaccion& other2);
    friend bool operator==(const transaccion& A, const transaccion& B);

    friend ostream& operator<<(ostream& os,const transaccion& other1);
};

bool operator<=(const transaccion &other2,const string& fecha_) {
    size_t indice_barra_1 = fecha_.find('/');
    size_t indice_barra_2 = fecha_.rfind('/');

    std::string dia_str = fecha_.substr(0, indice_barra_1);
    std::string mes_str = fecha_.substr(indice_barra_1 + 1, indice_barra_2 - indice_barra_1 - 1);
    std::string anio_str = fecha_.substr(indice_barra_2 + 1);

    int dia = std::stoi(dia_str);
    int mes = std::stoi(mes_str);
    int anio = std::stoi(anio_str);
    if (other2.fechatransaccion.anio > anio){
        return false;
    }else{
        if (other2.fechatransaccion.mes > mes){
            return false;
        }
        else if (other2.fechatransaccion.mes < mes){
            return true;
        }
        else{
            if (other2.fechatransaccion.dia > dia){
                return false;
            }
            return true;
        }
    }
}

bool operator>(const string& fecha_, const transaccion &other2) {
    size_t indice_barra_1 = fecha_.find('/');
    size_t indice_barra_2 = fecha_.rfind('/');

    std::string dia_str = fecha_.substr(0, indice_barra_1);
    std::string mes_str = fecha_.substr(indice_barra_1 + 1, indice_barra_2 - indice_barra_1 - 1);
    std::string anio_str = fecha_.substr(indice_barra_2 + 1);

    int dia = std::stoi(dia_str);
    int mes = std::stoi(mes_str);
    int anio = std::stoi(anio_str);
    if (anio < other2.fechatransaccion.anio){
        return false;
    }
    else if (anio > other2.fechatransaccion.anio){
        return true;
    }
    else{
        if (mes < other2.fechatransaccion.mes) {
            return false;
        }
        else if (mes > other2.fechatransaccion.mes){
            return true;
        }
        else{
            if (dia <= other2.fechatransaccion.dia){
                return false;
            }
            return true;
        }
    }
}

bool operator>=(const string& fecha_, const transaccion &other2) {
    size_t indice_barra_1 = fecha_.find('/');
    size_t indice_barra_2 = fecha_.rfind('/');

    std::string dia_str = fecha_.substr(0, indice_barra_1);
    std::string mes_str = fecha_.substr(indice_barra_1 + 1, indice_barra_2 - indice_barra_1 - 1);
    std::string anio_str = fecha_.substr(indice_barra_2 + 1);

    int dia = std::stoi(dia_str);
    int mes = std::stoi(mes_str);
    int anio = std::stoi(anio_str);
    if (anio < other2.fechatransaccion.anio){
        return false;
    }
    else if (anio > other2.fechatransaccion.anio){
        return true;
    }
    else{
        if (mes < other2.fechatransaccion.mes) {
            return false;
        }
        else if (mes > other2.fechatransaccion.mes){
            return true;
        }
        else{
            if (dia < other2.fechatransaccion.dia){
                return false;
            }
            return true;
        }
    }
}

bool operator<(const string& fecha_, const transaccion &other2) {
    size_t indice_barra_1 = fecha_.find('/');
    size_t indice_barra_2 = fecha_.rfind('/');

    std::string dia_str = fecha_.substr(0, indice_barra_1);
    std::string mes_str = fecha_.substr(indice_barra_1 + 1, indice_barra_2 - indice_barra_1 - 1);
    std::string anio_str = fecha_.substr(indice_barra_2 + 1);

    int dia = std::stoi(dia_str);
    int mes = std::stoi(mes_str);
    int anio = std::stoi(anio_str);
    if (anio > other2.fechatransaccion.anio){
        return false;
    }
    else if (anio < other2.fechatransaccion.anio){
        return true;
    }
    else{
        if (mes > other2.fechatransaccion.mes) {
            return false;
        }
        else if (mes < other2.fechatransaccion.mes){
            return true;
        }
        else{
            if (dia >= other2.fechatransaccion.dia){
                return false;
            }
            return true;
        }
    }
}

bool operator>=(const transaccion &other1, const transaccion &other2) {
    if (other1.fechatransaccion.anio < other2.fechatransaccion.anio){
        return false;
    }
    else if (other1.fechatransaccion.anio > other2.fechatransaccion.anio){
        return true;
    }
    else{
        if (other1.fechatransaccion.mes < other2.fechatransaccion.mes){
            return false;
        }
        else if (other1.fechatransaccion.mes > other2.fechatransaccion.mes){
            return true;
        }
        else{
            if (other1.fechatransaccion.dia < other2.fechatransaccion.dia){
                return false;
            }
            else{
                return true;
            }
        }
    }
}
bool operator>(const transaccion &other1, const transaccion &other2) {
    if (other1.fechatransaccion.anio < other2.fechatransaccion.anio){
        return false;
    }
    else if (other1.fechatransaccion.anio > other2.fechatransaccion.anio){
        return true;
    }
    else{
        if (other1.fechatransaccion.mes < other2.fechatransaccion.mes){
            return false;
        }
        else if (other1.fechatransaccion.mes > other2.fechatransaccion.mes){
            return true;
        }
        else{
            if (other1.fechatransaccion.dia <= other2.fechatransaccion.dia){
                return false;
            }
            else{
                return true;
            }
        }
    }
}

bool operator<(const transaccion& other1, const transaccion& other2){
    if (other1.fechatransaccion.anio > other2.fechatransaccion.anio){
        return false;
    }
    else if (other1.fechatransaccion.anio < other2.fechatransaccion.anio){
        return true;
    }
    else{
        if (other1.fechatransaccion.mes > other2.fechatransaccion.mes){
            return false;
        }
        else if (other1.fechatransaccion.mes < other2.fechatransaccion.mes){
            return true;
        }
        else{
            if (other1.fechatransaccion.dia >= other2.fechatransaccion.dia){
                return false;
            }
            else{
                return true;
            }
        }
    }
}
bool operator<=(const transaccion &other1, const transaccion &other2) {
    if (other1.fechatransaccion.anio > other2.fechatransaccion.anio){
        return false;
    }
    else if (other1.fechatransaccion.anio < other2.fechatransaccion.anio){
        return true;
    }
    else{
        if (other1.fechatransaccion.mes > other2.fechatransaccion.mes){
            return false;
        }
        else if (other1.fechatransaccion.mes < other2.fechatransaccion.mes){
            return true;
        }
        else{
            if (other1.fechatransaccion.dia > other2.fechatransaccion.dia){
                return false;
            }
            else{
                return true;
            }
        }
    }
}



bool operator==(const transaccion &A, const transaccion &B) {
    if (A.fechatransaccion.anio == B.fechatransaccion.anio && A.fechatransaccion.mes == B.fechatransaccion.mes && A.fechatransaccion.dia == B.fechatransaccion.dia){
        return true;
    }
    return false;
}



ostream& operator<<(ostream &os, const transaccion &other1) {
    other1.display();
    os << "exit";
    return os;
}



#endif //PROYECTOALGORITMOS_TRANSACCION_H
