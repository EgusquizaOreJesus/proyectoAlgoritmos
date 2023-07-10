#include <iostream>
#include "transaccion.h"
#include "BlockChain.h"
#include <fstream>
#include <sstream>

using namespace std;



int main() {
    std::ifstream inFile("../python/transacciones.txt" , std::ios::in);
    if (!inFile) {
        std::cerr << "No se pudo abrir el archivo";
        return 1;
    }

    double monto;
    std::string emisor;
    std::string receptor;
    int dia, mes, year;
    std::string linea;

    std::vector<transaccion> Transacciones;
    std::vector<transaccion> Transacciones_start;

    while (inFile >> monto >> emisor  >> receptor  >> dia  >> mes >> year) {
        transaccion t(monto, emisor, receptor, dia, mes, year);
        Transacciones.push_back(t);
    }

    for (int i = 0; i < 5 && i < Transacciones.size(); ++i) {
        Transacciones_start.push_back(Transacciones[i]);
    }

    blockchain BLOCK(Transacciones_start);

    std::vector<transaccion> prov;
    for (int i = 5; i < Transacciones.size(); ++i) {
        prov.push_back(Transacciones[i]);
        if (prov.size() == 5) {
            BLOCK.insert_block_with_transaction(prov);
            prov.clear();
        }
    }

    if (!prov.empty()) {
        BLOCK.insert_block_with_transaction(prov);
    }


    while (true) {

        std::cout << "Selecciona una opcion:\n";
        std::cout << "1. Busqueda por emisor\n";
        std::cout << "2. Busqueda por receptor\n";
        std::cout << "3. Busqueda por monto\n";
        std::cout << "4. Busqueda por monto en un bloque especifico\n";
        std::cout << "5. Busqueda por rango de monto\n";
        std::cout << "6. Busqueda por rango de fecha de transaccion\n";
        std::cout << "7. Busqueda por rango de monto de transaccion\n";
        std::cout << "8. Busqueda por cadenas que inician con un patron\n";
        std::cout << "9. Busqueda por contenido en cadena\n";
        std::cout << "10. Busqueda por el maximo valor\n";
        std::cout << "11. Busqueda por el minimo valor\n";
        std::cout << "0. Salir\n";

        int opcion;
        std::cin >> opcion;

        if (opcion == 0) {
            break;
        }

        // Variables para los argumentos de getFiltrados
        std::string str_data = "";
        double dbl_data = 0;
        double ini = 0, end = 0;
        int index = -1;
        std::string fecha_ini = "", fecha_end = "";

        switch (opcion) {
            case 1:  // Búsqueda por emisor
                std::cout << "Introduce el nombre del emisor: ";
                std::cin >> str_data;
                {
                    auto ids = BLOCK.getFiltrados(CriterioBusqueda::IgualA_X_String_emisor, str_data);
                    for (int id : ids) {
                        std::cout << "ID_BLOQUE: " << id << "\n";
                    }
                }
                break;

            case 2:  // Búsqueda por receptor
                std::cout << "Introduce el nombre del receptor: ";
                std::cin >> str_data;
                {
                    auto ids = BLOCK.getFiltrados(CriterioBusqueda::IgualA_X_String_receptor, str_data);
                    for (int id : ids) {
                        std::cout << "ID_BLOQUE: " << id << "\n";
                    }
                }
                break;

            case 3:  // Búsqueda por monto
                std::cout << "Introduce el monto de la transacción: ";
                std::cin >> dbl_data;
                {
                    auto ids = BLOCK.getFiltrados(CriterioBusqueda::IgualA_X_Double, "", dbl_data);
                    for (int id : ids) {
                        std::cout << "ID_BLOQUE: " << id << "\n";
                    }
                }
                break;

            case 4: // Búsqueda por monto en un bloque específico
                std::cout << "Introduce el monto y el índice del bloque (separado por un espacio): ";
                std::cin >> dbl_data >> index;
                {
                    auto ids = BLOCK.getFiltrados(CriterioBusqueda::IgualA_X_Double_Bloque, "", dbl_data, 0, 0, index);
                    for (int id : ids) {
                        std::cout << "ID_BLOQUE: " << id << "\n";
                    }
                }
                break;

            case 5: // Búsqueda por rango de monto
                std::cout << "Introduce el rango de monto (separado por un espacio): ";
                std::cin >> ini >> end;
                {
                    auto ids = BLOCK.getFiltrados(CriterioBusqueda::RangoMonto, "", 0, ini, end);
                    for (int id : ids) {
                        std::cout << "ID_BLOQUE: " << id << "\n";
                    }
                }
                break;

            case 6: // Búsqueda por rango de fecha de transacción
                std::cout << "Introduce el rango de fechas de transacción (separado por un espacio): ";
                std::cin >> fecha_ini >> fecha_end;
                {
                    auto ids = BLOCK.getFiltrados(CriterioBusqueda::RangoFechaTransaccion, "", 0, 0, 0, -1, fecha_ini, fecha_end);
                    for (int id : ids) {
                        std::cout << "ID_BLOQUE: " << id << "\n";
                    }
                }
                break;

            case 7: // Búsqueda por rango de monto de transacción
                std::cout << "Introduce el rango de montos de transacción (separado por un espacio): ";
                std::cin >> ini >> end;
                {
                    auto ids = BLOCK.getFiltrados(CriterioBusqueda::RangoMontoTransaccion, "", 0, ini, end);
                    for (int id : ids) {
                        std::cout << "ID_BLOQUE: " << id << "\n";
                    }
                }
                break;

            case 8: // Búsqueda por cadenas que inician con un patrón
                std::cout << "Introduce el patrón con el que debe iniciar la cadena: ";
                std::cin >> str_data;
                {
                    auto ids = BLOCK.getFiltrados(CriterioBusqueda::IniciaCon, str_data);
                    for (int id : ids) {
                        std::cout << "ID_BLOQUE: " << id << "\n";
                    }
                }
                break;

            case 9: // Búsqueda por contenido en cadena
                std::cout << "Introduce el contenido a buscar en la cadena: ";
                std::cin >> str_data;
                {
                    auto ids = BLOCK.getFiltrados(CriterioBusqueda::ContenidoEn, str_data);
                    for (int id : ids) {
                        std::cout << "IDBLOQUE: " << id << "\n";
                    }
                }
                break;

            case 10: // Búsqueda por el máximo valor
            {
                auto ids = BLOCK.getFiltrados(CriterioBusqueda::MaximoValor);
                for (int id : ids) {
                    std::cout << "ID_BLOQUE: " << id << "\n";
                }
            }
                break;

            case 11: // Búsqueda por el mínimo valor
            {
                auto ids = BLOCK.getFiltrados(CriterioBusqueda::MinimoValor);
                for (int id : ids) {
                    std::cout << "ID_BLOQUE: xx" << id << "xx\n";
                }
            }
                break;

            default:
                std::cout << "Opción no válida. Intenta de nuevo.\n";
                break;
        }
    }


    return 0;
}