#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
using namespace std;

// MODULO 4 - PERSISTENCIA Y ARCHIVOS
// Se encarga de guardar y cargar la info de libros, usuarios y
// prestamos en archivos de texto, para que no se pierda al cerrar
// el programa.
//
// NOTA: estas estructuras (Libro, Usuario, Prestamo)
// son una primera version.

struct Libro {
    string codigo;
    string titulo;
    string autor;
    string ubicacion;
    bool disponible;
};

struct Usuario {
    string identificacion;
    string nombre;
    string apellido;
    string correo;
    bool activo;
};

struct Prestamo {
    string codigoLibro;
    string identificacionUsuario;
    string fechaPrestamo;
    string fechaDevolucion;
    bool activo;
};

// usamos "|" como separador entre los datos de cada linea del archivo
const char SEPARADOR = '|';

// LIBROS

// guarda todos los libros en el archivo, regresa true si pudo escribir
bool guardarLibros(vector<Libro>& libros, string nombreArchivo) {
    ofstream archivo(nombreArchivo);

    if (!archivo.is_open()) {
        cout << "No se pudo abrir el archivo " << nombreArchivo << endl;
        return false;
    }

    for (int i = 0; i < libros.size(); i++) {
        archivo << libros[i].codigo << SEPARADOR
                << libros[i].titulo << SEPARADOR
                << libros[i].autor << SEPARADOR
                << libros[i].ubicacion << SEPARADOR
                << libros[i].disponible << endl;
    }

    archivo.close();
    return true;
}

// carga los libros desde el archivo hacia el vector, regresa true si pudo leer
bool cargarLibros(vector<Libro>& libros, string nombreArchivo) {
    ifstream archivo(nombreArchivo);

    if (!archivo.is_open()) {
        cout << "No existe el archivo " << nombreArchivo << " todavia." << endl;
        return false;
    }

    libros.clear();
    string linea;

    while (getline(archivo, linea)) {
        stringstream ss(linea);
        Libro l;
        string disponibleTexto;

        getline(ss, l.codigo, SEPARADOR);
        getline(ss, l.titulo, SEPARADOR);
        getline(ss, l.autor, SEPARADOR);
        getline(ss, l.ubicacion, SEPARADOR);
        getline(ss, disponibleTexto, SEPARADOR);

        l.disponible = (disponibleTexto == "1");
        libros.push_back(l);
    }

    archivo.close();
    return true;
}

// ---------------------------------------------------------------
// USUARIOS
// ---------------------------------------------------------------

bool guardarUsuarios(vector<Usuario>& usuarios, string nombreArchivo) {
    ofstream archivo(nombreArchivo);

    if (!archivo.is_open()) {
        cout << "No se pudo abrir el archivo " << nombreArchivo << endl;
        return false;
    }

    for (int i = 0; i < usuarios.size(); i++) {
        archivo << usuarios[i].identificacion << SEPARADOR
                << usuarios[i].nombre << SEPARADOR
                << usuarios[i].apellido << SEPARADOR
                << usuarios[i].correo << SEPARADOR
                << usuarios[i].activo << endl;
    }

    archivo.close();
    return true;
}

bool cargarUsuarios(vector<Usuario>& usuarios, string nombreArchivo) {
    ifstream archivo(nombreArchivo);

    if (!archivo.is_open()) {
        cout << "No existe el archivo " << nombreArchivo << " todavia." << endl;
        return false;
    }

    usuarios.clear();
    string linea;

    while (getline(archivo, linea)) {
        stringstream ss(linea);
        Usuario u;
        string activoTexto;

        getline(ss, u.identificacion, SEPARADOR);
        getline(ss, u.nombre, SEPARADOR);
        getline(ss, u.apellido, SEPARADOR);
        getline(ss, u.correo, SEPARADOR);
        getline(ss, activoTexto, SEPARADOR);

        u.activo = (activoTexto == "1");
        usuarios.push_back(u);
    }

    archivo.close();
    return true;
}

// PRESTAMOS

bool guardarPrestamos(vector<Prestamo>& prestamos, string nombreArchivo) {
    ofstream archivo(nombreArchivo);

    if (!archivo.is_open()) {
        cout << "No se pudo abrir el archivo " << nombreArchivo << endl;
        return false;
    }

    for (int i = 0; i < prestamos.size(); i++) {
        archivo << prestamos[i].codigoLibro << SEPARADOR
                << prestamos[i].identificacionUsuario << SEPARADOR
                << prestamos[i].fechaPrestamo << SEPARADOR
                << prestamos[i].fechaDevolucion << SEPARADOR
                << prestamos[i].activo << endl;
    }

    archivo.close();
    return true;
}

bool cargarPrestamos(vector<Prestamo>& prestamos, string nombreArchivo) {
    ifstream archivo(nombreArchivo);

    if (!archivo.is_open()) {
        cout << "No existe el archivo " << nombreArchivo << " todavia." << endl;
        return false;
    }

    prestamos.clear();
    string linea;

    while (getline(archivo, linea)) {
        stringstream ss(linea);
        Prestamo p;
        string activoTexto;

        getline(ss, p.codigoLibro, SEPARADOR);
        getline(ss, p.identificacionUsuario, SEPARADOR);
        getline(ss, p.fechaPrestamo, SEPARADOR);
        getline(ss, p.fechaDevolucion, SEPARADOR);
        getline(ss, activoTexto, SEPARADOR);

        p.activo = (activoTexto == "1");
        prestamos.push_back(p);
    }

    archivo.close();
    return true;
}

// PRUEBA DEL MODULO (primer avance funcional)

int main() {
    // --- datos de prueba ---
    vector<Libro> libros;
    libros.push_back({"L001", "Cien anios de soledad", "Gabriel Garcia Marquez", "Estante A1", true});
    libros.push_back({"L002", "El principito", "Antoine de Saint-Exupery", "Estante B2", false});

    vector<Usuario> usuarios;
    usuarios.push_back({"1234567890101", "Josue", "Chavez", "josue@correo.com", true});

    vector<Prestamo> prestamos;
    prestamos.push_back({"L002", "1234567890101", "2026-09-10", "2026-09-24", true});

    // --- guardar en archivos ---
    guardarLibros(libros, "libros.txt");
    guardarUsuarios(usuarios, "usuarios.txt");
    guardarPrestamos(prestamos, "prestamos.txt");

    cout << "Datos guardados en los archivos." << endl;

    // --- vaciamos los vectores para simular que el programa se cerro ---
    libros.clear();
    usuarios.clear();
    prestamos.clear();

    // --- volvemos a cargar desde los archivos ---
    cargarLibros(libros, "libros.txt");
    cargarUsuarios(usuarios, "usuarios.txt");
    cargarPrestamos(prestamos, "prestamos.txt");

    cout << endl;
    cout << "----- LIBROS CARGADOS DESDE EL ARCHIVO -----" << endl;
    for (int i = 0; i < libros.size(); i++) {
        cout << libros[i].codigo << " - " << libros[i].titulo
             << " - " << libros[i].autor << " - " << libros[i].ubicacion
             << " - Disponible: " << libros[i].disponible << endl;
    }

    cout << endl;
    cout << "----- USUARIOS CARGADOS DESDE EL ARCHIVO -----" << endl;
    for (int i = 0; i < usuarios.size(); i++) {
        cout << usuarios[i].identificacion << " - " << usuarios[i].nombre
             << " " << usuarios[i].apellido << " - " << usuarios[i].correo << endl;
    }

    cout << endl;
    cout << "----- PRESTAMOS CARGADOS DESDE EL ARCHIVO -----" << endl;
    for (int i = 0; i < prestamos.size(); i++) {
        cout << "Libro " << prestamos[i].codigoLibro << " prestado a "
             << prestamos[i].identificacionUsuario << " desde "
             << prestamos[i].fechaPrestamo << " hasta " << prestamos[i].fechaDevolucion << endl;
    }

    return 0;
}
