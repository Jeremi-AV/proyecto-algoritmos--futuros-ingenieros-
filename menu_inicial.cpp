#include <iostream>
#include <string>
#include <limits>

using namespace std;

struct Libro {
    int id;
    string titulo;
    string autor;
    bool disponible;
};

struct Usuario {
    int id;
    string nombre;
    string carne;
};

struct Prestamo {
    int idPrestamo;
    int idLibro;
    int idUsuario;
    string fecha;
};

void moduloCatalogo() {
    cout << "MODULO 1: CATALOGO DE LIBROS" << endl;
    cout << "1. Registrar libro" << endl;
    cout << "2. Buscar libro por titulo/autor" << endl;
    cout << "3. Ver ubicacion en matriz fisica" << endl;
}

void moduloUsuarios() {
    cout << "MODULO 2: USUARIOS Y LECTORES" << endl;
    cout << "1. Registrar nuevo lector" << endl;
    cout << "2. Consultar perfil por carne/DPI" << endl;
}

void moduloPrestamos() {
    cout << "   [MODULO 3: PRESTAMOS Y DEVOLUCIONES]" << endl;
    cout << "1. Registrar prestamo de libro" << endl;
    cout << "2. Registrar devolucion de libro" << endl;
}

void moduloArchivos() {
    cout << "   [MODULO 4: PERSISTENCIA Y ARCHIVOS]" << endl;
    cout << "1. Guardar datos en archivos (.txt)" << endl;
    cout << "2. Cargar datos desde archivos (.txt)" << endl;
}

void moduloReportes() {
    cout << "   [MODULO 5: REPORTES Y RECURSIVIDAD]" << endl;
    cout << "1. Mostrar estadisticas generales" << endl;
    cout << "2. Ejecutar conteo recursivo de libros disponibles" << endl;
}

int mostrarMenu() {
    int opcion = 0;

    cout << "\nSISTEMA DE GESTION DE BIBLIOTECA" << endl;
    cout << "1: Catalogo de Libros" << endl;
    cout << "2: Usuarios / Lectores" << endl;
    cout << "3: Prestamos y Devoluciones" << endl;
    cout << "4: Persistencia y Archivos" << endl;
    cout << "5: Reportes y Recursividad" << endl;
    cout << "6: Salir" << endl;
    cout << "Seleccione una opcion: ";
    
    cin >> opcion;

    if (cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return -1; 
    }

    return opcion;
}

void procesarOpcion(int opcion) {
    switch (opcion) {
        case 1:
            moduloCatalogo();
            break;
        case 2:
            moduloUsuarios();
            break;
        case 3:
            moduloPrestamos();
            break;
        case 4:
            moduloArchivos();
            break;
        case 5:
            moduloReportes();
            break;
        case 6:
            cout << "\nCerrando el sistema" << endl;
            break;
        default:
            cout << "\nOpcion invalida Intente de nuevo\n" << endl;
            break;
    }
    
    if (opcion >= 1 && opcion <= 5) {
        cout << "\nPresione cualquier tecla";
        cin.ignore();
        cin.get();
    }
}

int main() {
    int opcion = 0;

    do {
        opcion = mostrarMenu();
        procesarOpcion(opcion);
    } while (opcion != 6);

    return 0;
}