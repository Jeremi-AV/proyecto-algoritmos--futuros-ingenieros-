#include "prestamos.h"
#include <iostream>
#include <algorithm>
#include <cctype>
#include <ctime>
#include <limits>

using namespace std; 

static string aMinusculas(string s) {
    for (size_t i = 0; i < s.size(); i++)
        s[i] = (char)tolower((unsigned char)s[i]);
    return s;
}

static string recortar(const string& s) {
    size_t ini = s.find_first_not_of(" \t");
    if (ini == string::npos) return "";
    size_t fin = s.find_last_not_of(" \t");
    return s.substr(ini, fin - ini + 1);
}

string fechaActual() {
    time_t t = time(nullptr);
    tm* l = localtime(&t);
    char buf[11];
    strftime(buf, sizeof(buf), "%d/%m/%Y", l);
    return string(buf);
}

string mensajeResultado(Resultado r) {
    switch (r) {
        case OK:                     return "Operacion realizada con exito.";
        case DATOS_INVALIDOS:        return "Datos invalidos (campo vacio o cantidad <= 0).";
        case LIBRO_NO_ENCONTRADO:    return "El libro no existe en el sistema.";
        case SIN_EJEMPLARES:         return "No hay ejemplares disponibles de este libro.";
        case PRESTAMO_DUPLICADO:     return "El usuario ya tiene un prestamo activo de este libro.";
        case PRESTAMO_NO_ENCONTRADO: return "No existe un prestamo con ese ID.";
        case YA_DEVUELTO:            return "Ese prestamo ya fue devuelto.";
    }
    return "Resultado desconocido.";
}

string estadoATexto(EstadoLibro estado) {
    return (estado == DISPONIBLE) ? "DISPONIBLE" : "NO DISPONIBLE";
}

void actualizarEstado(Libro& libro) {
    libro.estado = (libro.disponibles > 0) ? DISPONIBLE : NO_DISPONIBLE;
}

void actualizarTodosLosEstados(vector<Libro>& libros) {
    for (size_t i = 0; i < libros.size(); i++)
        actualizarEstado(libros[i]);
}

int buscarLibro(const vector<Libro>& libros, const string& titulo) {
    string buscado = aMinusculas(recortar(titulo));
    for (size_t i = 0; i < libros.size(); i++)
        if (aMinusculas(libros[i].titulo) == buscado)
            return (int)i;
    return -1;
}

Resultado agregarLibro(vector<Libro>& libros, const string& titulo, int cantidad) {
    string nombre = recortar(titulo);
    if (nombre.empty() || cantidad <= 0) return DATOS_INVALIDOS;

    int pos = buscarLibro(libros, nombre);
    if (pos >= 0) {                   
        libros[pos].total       += cantidad;
        libros[pos].disponibles += cantidad;
        actualizarEstado(libros[pos]);
    } else {                        
        Libro nuevo;
        nuevo.titulo      = nombre;
        nuevo.total       = cantidad;
        nuevo.disponibles = cantidad;
        actualizarEstado(nuevo);
        libros.push_back(nuevo);
    }
    return OK; 
}
Resultado consultarDisponibilidad(const vector<Libro>& libros, const string& titulo,
                                  int& disponibles, int& total) {
    if (recortar(titulo).empty()) return DATOS_INVALIDOS;
    int pos = buscarLibro(libros, titulo);
    if (pos < 0) return LIBRO_NO_ENCONTRADO;
    disponibles = libros[pos].disponibles;
    total       = libros[pos].total;
    return OK;
}

void mostrarDisponibilidad(const vector<Libro>& libros, const string& titulo) {
    int disp = 0, total = 0;
    Resultado r = consultarDisponibilidad(libros, titulo, disp, total);
    if (r != OK) {
        cout << mensajeResultado(r) << endl;
        return;
    }
    int pos = buscarLibro(libros, titulo);
    cout << "Libro: " << libros[pos].titulo << endl;
    cout << "Disponibles: " << disp << " de " << total << endl;
    cout << "Estado: " << estadoATexto(libros[pos].estado) << endl;
}

void mostrarInventario(const vector<Libro>& libros) {
    if (libros.empty()) {
        cout << "El inventario esta vacio." << endl;
        return;
    }
    cout << "--- INVENTARIO ---" << endl;
    for (size_t i = 0; i < libros.size(); i++) {
        cout << i + 1 << ". " << libros[i].titulo
             << " | " << libros[i].disponibles << "/" << libros[i].total
             << " | " << estadoATexto(libros[i].estado) << endl;
    }
}
// Suma 1 ejemplar (lo usa el modulo de devoluciones)
Resultado reponerEjemplar(vector<Libro>& libros, const string& titulo) {
    int pos = buscarLibro(libros, titulo);
    if (pos < 0) return LIBRO_NO_ENCONTRADO;
    if (libros[pos].disponibles < libros[pos].total)
        libros[pos].disponibles++;
    actualizarEstado(libros[pos]); 
    return OK;
}

bool usuarioTienePrestamoActivo(const vector<Prestamo>& prestamos,
                                const string& titulo, const string& usuario) {
    string t = aMinusculas(recortar(titulo));
    string u = aMinusculas(recortar(usuario));
    for (size_t i = 0; i < prestamos.size(); i++)
        if (prestamos[i].activo &&
            aMinusculas(prestamos[i].titulo) == t &&
            aMinusculas(prestamos[i].usuario) == u)
            return true;
    return false;
}

Resultado crearPrestamo(vector<Libro>& libros, vector<Prestamo>& prestamos,
                        const string& titulo, const string& usuario, int& idGenerado) {
    if (recortar(titulo).empty() || recortar(usuario).empty()) return DATOS_INVALIDOS;

    int pos = buscarLibro(libros, titulo);
    if (pos < 0) return LIBRO_NO_ENCONTRADO;
    if (libros[pos].disponibles <= 0) return SIN_EJEMPLARES;
    if (usuarioTienePrestamoActivo(prestamos, libros[pos].titulo, usuario))
        return PRESTAMO_DUPLICADO;
