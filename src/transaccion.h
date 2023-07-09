#ifndef PROYECTOALGORITMOS_TRANSACCION_H
#define PROYECTOALGORITMOS_TRANSACCION_H
#include "iostream"
#include <ctime>
#include "string"
#include <vector>
using namespace std;




struct Fecha{
    int dia = int{};
    int mes = int{};
    int anio = int{};
    Fecha(){}
    Fecha(int d, int m, int a): dia(d), mes(m), anio(a){}
    Fecha(const Fecha& other){
        dia = other.dia;
        mes = other.mes;
        anio = other.anio;
    }
};
enum eleccion{
    emisor,
    receptor,
    fechaX,
    monto
};
struct transaccion
{
    double monto;
    std::string emisor;
    std::string receptor;
    Fecha fechatransaccion;
    int id_bloque;
    transaccion(){
        monto = double{};
    }

    explicit transaccion(double monto_, std::string e, std::string r, int d,int m, int a): fechatransaccion(d, m, a)
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
        id_bloque=other.id_bloque;
    }
    void setIdBloque(int idBloque)
    {
        id_bloque=idBloque;
    }

    int getIdBloque() const;

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
        id_bloque=other.id_bloque;
    }
    friend ostream& operator<<(ostream& os,const transaccion& other1);
};
struct comparador{
    static bool igualdad(const transaccion &A, const transaccion &B){
        if (A.fechatransaccion.anio == B.fechatransaccion.anio && A.fechatransaccion.mes == B.fechatransaccion.mes && A.fechatransaccion.dia == B.fechatransaccion.dia){
            return true;
        }
        return false;
    }
    static bool igualdad(const string& fecha, const transaccion &B){
        size_t indice_barra_1 = fecha.find('/');
        size_t indice_barra_2 = fecha.rfind('/');

        std::string dia_str = fecha.substr(0, indice_barra_1);
        std::string mes_str = fecha.substr(indice_barra_1 + 1, indice_barra_2 - indice_barra_1 - 1);
        std::string anio_str = fecha.substr(indice_barra_2 + 1);

        int dia = std::stoi(dia_str);
        int mes = std::stoi(mes_str);
        int anio = std::stoi(anio_str);
        if (anio == B.fechatransaccion.anio && mes == B.fechatransaccion.mes && dia == B.fechatransaccion.dia){
            return true;
        }
        return false;
    }
    static bool igualdad(const Fecha &A, const transaccion &B){

        if (A.anio == B.fechatransaccion.anio && A.mes == B.fechatransaccion.mes && A.dia == B.fechatransaccion.dia){
            return true;
        }
        return false;
    }
    static bool isMayor(const transaccion& other1, const transaccion& other2){
        if (other1.fechatransaccion.anio < other2.fechatransaccion.anio){
            return true;
        }
        else if (other1.fechatransaccion.anio > other2.fechatransaccion.anio){
            return false;
        }
        else{
            if (other1.fechatransaccion.mes < other2.fechatransaccion.mes){
                return true;
            }
            else if (other1.fechatransaccion.mes > other2.fechatransaccion.mes){
                return false;
            }
            else{
                if (other1.fechatransaccion.dia >= other2.fechatransaccion.dia){
                    return false;
                }
                return true;
            }
        }
    }
    static bool isMayorIgual(const transaccion& other1, const transaccion& other2){
        if (other1.fechatransaccion.anio < other2.fechatransaccion.anio){
            return true;
        }
        else if (other1.fechatransaccion.anio > other2.fechatransaccion.anio){
            return false;
        }
        else{
            if (other1.fechatransaccion.mes < other2.fechatransaccion.mes){
                return true;
            }
            else if (other1.fechatransaccion.mes > other2.fechatransaccion.mes){
                return false;
            }
            else{
                if (other1.fechatransaccion.dia > other2.fechatransaccion.dia){
                    return false;
                }
                return true;
            }
        }
    }
    static bool isMenor(const transaccion& other1, const transaccion& other2){
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
                return true;
            }
        }
    }
    static bool isMenorIgual(const transaccion& other1, const transaccion& other2){
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
                return true;
            }
        }
    }
    static bool isMayor(double a, const transaccion& b){
        return a < b.monto;
    }
    static bool isMayorIgual(double a, const transaccion& b){
        return a <= b.monto;
    }
    static bool isMenor(double a, const transaccion& b){
        return a > b.monto;
    }
    static bool isMenorIgual(double a, const transaccion& b){
        return a >= b.monto;
    }

    static bool isMayorIgual(const string& fecha, const transaccion& other2){
        size_t indice_barra_1 = fecha.find('/');
        size_t indice_barra_2 = fecha.rfind('/');

        std::string dia_str = fecha.substr(0, indice_barra_1);
        std::string mes_str = fecha.substr(indice_barra_1 + 1, indice_barra_2 - indice_barra_1 - 1);
        std::string anio_str = fecha.substr(indice_barra_2 + 1);

        int dia = std::stoi(dia_str);
        int mes = std::stoi(mes_str);
        int anio = std::stoi(anio_str);
        if (anio < other2.fechatransaccion.anio){
            return true;
        }
        else if (anio > other2.fechatransaccion.anio){
            return false;
        }
        else{
            if (mes < other2.fechatransaccion.mes){
                return true;
            }
            else if (mes > other2.fechatransaccion.mes){
                return false;
            }
            else{
                if (dia > other2.fechatransaccion.dia){
                    return false;
                }
                return true;
            }
        }
    }
    static bool isMayor(const string& fecha, const transaccion& other2){
        size_t indice_barra_1 = fecha.find('/');
        size_t indice_barra_2 = fecha.rfind('/');

        std::string dia_str = fecha.substr(0, indice_barra_1);
        std::string mes_str = fecha.substr(indice_barra_1 + 1, indice_barra_2 - indice_barra_1 - 1);
        std::string anio_str = fecha.substr(indice_barra_2 + 1);

        int dia = std::stoi(dia_str);
        int mes = std::stoi(mes_str);
        int anio = std::stoi(anio_str);
        if (anio < other2.fechatransaccion.anio){
            return true;
        }
        else if (anio > other2.fechatransaccion.anio){
            return false;
        }
        else{
            if (mes < other2.fechatransaccion.mes){
                return true;
            }
            else if (mes > other2.fechatransaccion.mes){
                return false;
            }
            else{
                if (dia >= other2.fechatransaccion.dia){
                    return false;
                }
                return true;
            }
        }
    }
    static bool isMenorIgual(const string& fecha, const transaccion& other2){
        size_t indice_barra_1 = fecha.find('/');
        size_t indice_barra_2 = fecha.rfind('/');

        std::string dia_str = fecha.substr(0, indice_barra_1);
        std::string mes_str = fecha.substr(indice_barra_1 + 1, indice_barra_2 - indice_barra_1 - 1);
        std::string anio_str = fecha.substr(indice_barra_2 + 1);

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
            if (mes < other2.fechatransaccion.mes){
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
    static bool isMenor(const string& fecha, const transaccion& other2){
        size_t indice_barra_1 = fecha.find('/');
        size_t indice_barra_2 = fecha.rfind('/');

        std::string dia_str = fecha.substr(0, indice_barra_1);
        std::string mes_str = fecha.substr(indice_barra_1 + 1, indice_barra_2 - indice_barra_1 - 1);
        std::string anio_str = fecha.substr(indice_barra_2 + 1);

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
            if (mes < other2.fechatransaccion.mes){
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
};
ostream& operator<<(ostream &os, const transaccion &other1) {
    other1.display();
    os << "exit";
    return os;
}

int transaccion::getIdBloque() const {
    return id_bloque;
}


class Usuario{
private:
    string nombre;
    double ganancias=5000;
    vector<int> bloque_id;

public:
    Usuario(const string &nombre) : nombre(nombre){}

    void nueva_operacion(int index_bloque)
    {
        bloque_id.push_back(index_bloque);
    }

    const string &getNombre() const {
        return nombre;
    }

    double getGanancias() const {
        return ganancias;
    }

    const vector<int> &getBloqueId() const {
        return bloque_id;
    }

    void setNombre(const string &nombre) {
        Usuario::nombre = nombre;
    }

    void setGanancias(double ganancias) {
        Usuario::ganancias = ganancias;
    }



    void increment(double montos){
        ganancias+=montos;
    }
};




#endif //PROYECTOALGORITMOS_TRANSACCION_H