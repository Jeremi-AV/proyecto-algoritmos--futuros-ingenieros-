#ifndef USUARIO_H
#define USUARIO_H

#include <cstring>
#include <vector>
#include <iostream>

struct Usuario {
    std::string Identificacion; // dpi o carnet de identidad
    std::string nombre;         // nombre del usuario
    std::string apellido;       // apellido del usuario
    std::string correo;         // correo del usuario
    std::vector<std::string> intereses;
    bool activo;                // indica si el usuario esta activo o no
};

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

void registrarPrestamo() {
    std::cout << "[OK] Prestamo registrado.\n";
}

void registrarDevolucion() {
    std::cout << "[OK] Devolucion registrada.\n";
}

#endif // USUARIO_H
