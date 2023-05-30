//
// Created by Jesus Egusquiza on 5/29/2023.
//

#ifndef PROYECTOALGORITMOS_TRANSACCION_H
#define PROYECTOALGORITMOS_TRANSACCION_H
#include "iostream"
#include <ctime>

struct fecha{
    int dia;
    int mes;
    int anio;
    fecha(){}
    fecha(int d,int m,int a):dia(d),mes(m),anio(a){}
};

struct transaccion
{
    double monto;
    std::string emisor;
    std::string receptor;
    fecha fechatransaccion;


    transaccion(double monto_, std::string e, std::string r, int d,int m, int a):fechatransaccion(d,m,a)
    {
        monto = monto_;
        emisor = std::move(e);
        receptor = std::move(r);
    };
    friend bool operator<(const transaccion& other1,const transaccion& other2);
    friend bool operator<(fecha fecha_,const transaccion& other2);

    friend bool operator>(const transaccion& other1, const transaccion& other2);
    friend bool operator==(const transaccion& A, const transaccion& B);
};

bool operator<(const transaccion& other1, const transaccion& other2){
    if (other1.fechatransaccion.anio > other2.fechatransaccion.anio){
        return false;
    }
    else{
        if (other1.fechatransaccion.mes > other2.fechatransaccion.mes){
            return false;
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
bool operator<(fecha fecha_,const transaccion& other2){
    if (fecha_.anio > other2.fechatransaccion.anio){
        return false;
    }
    else{
        if (fecha_.mes > other2.fechatransaccion.mes){
            return false;
        }
        else{
            if (fecha_.dia > other2.fechatransaccion.dia){
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
    else{
        if (other1.fechatransaccion.mes < other2.fechatransaccion.mes){
            return false;
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



bool operator==(const transaccion &A, const transaccion &B) {
    if (A.fechatransaccion.anio == B.fechatransaccion.anio && A.fechatransaccion.mes == B.fechatransaccion.mes && A.fechatransaccion.dia == B.fechatransaccion.dia){
        return true;
    }
    return false;
}

#endif //PROYECTOALGORITMOS_TRANSACCION_H
