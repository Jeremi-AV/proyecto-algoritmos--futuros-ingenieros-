
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
