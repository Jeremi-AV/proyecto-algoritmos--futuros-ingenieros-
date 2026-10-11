
#include <string>
#include <vector>
#include <iostream>

struct Prestamo {
    int idPrestamo;
    int idUsuario;
    int idLibro;
    std::string fechaPrestamo;
    std::string fechaDevolucion;
    bool devuelto;
};

const int MAX_PRESTAMOS = 100;
extern Prestamo listaPrestamos[MAX_PRESTAMOS];
extern int totalPrestamos;

// Prototipos del Módulo 3
void menuPrestamos();
void registrarPrestamo();
void registrarDevolucion();

void menuPrestamos() {
    int opcion;
    do {
        std::cout << "\n--- MODULO DE PRESTAMOS Y DEVOLUCIONES ---\n";
        std::cout << "1. Registrar nuevo prestamo\n";
        std::cout << "2. Registrar devolucion de libro\n";
        std::cout << "3. Regresar al menu principal\n";
        std::cout << "Seleccione una opcion: ";
        std::cin >> opcion;

        switch(opcion) {
            case 1: registrarPrestamo(); break;
            case 2: registrarDevolucion(); break;
            case 3: break;
            default: std::cout << "[X] Opcion invalida.\n";
        }
    } while(opcion != 3);
}
