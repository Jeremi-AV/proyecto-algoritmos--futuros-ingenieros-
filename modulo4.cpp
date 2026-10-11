// modulo4.cpp
// Modulo 4: persistencia y archivos
// Guarda y carga libros, usuarios y prestamos en archivos .txt
#include <iostream>
#include <string>
#include <limits>
#include <vector>
#include <fstream>
#include <sstream>
using namespace std;

// mismos struct que usa el menu_inicial.cpp
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

//  GUARDAR  

void guardarLibros(vector<Libro>& libros) {
    ofstream archivo("libros.txt");
    for (int i = 0; i < libros.size(); i++) {
        archivo << libros[i].id << "|" << libros[i].titulo << "|"
                << libros[i].autor << "|" << libros[i].disponible << endl;
    }
    archivo.close();
}

void guardarUsuarios(vector<Usuario>& usuarios) {
    ofstream archivo("usuarios.txt");
    for (int i = 0; i < usuarios.size(); i++) {
        archivo << usuarios[i].id << "|" << usuarios[i].nombre << "|"
                << usuarios[i].carne << endl;
    }
    archivo.close();
}

void guardarPrestamos(vector<Prestamo>& prestamos) {
    ofstream archivo("prestamos.txt");
    for (int i = 0; i < prestamos.size(); i++) {
        archivo << prestamos[i].idPrestamo << "|" << prestamos[i].idLibro << "|"
                << prestamos[i].idUsuario << "|" << prestamos[i].fecha << endl;
    }
    archivo.close();
}

//  CARGAR  
// regresan false si el archivo todavia no existe

bool cargarLibros(vector<Libro>& libros) {
    ifstream archivo("libros.txt");
    if (!archivo.is_open()) {
        return false;
    }
    libros.clear();
    string linea;
    while (getline(archivo, linea)) {
        if (linea == "") {
            continue;
        }
        stringstream ss(linea);
        string id, disponible;
        Libro l;
        getline(ss, id, '|');
        getline(ss, l.titulo, '|');
        getline(ss, l.autor, '|');
        getline(ss, disponible, '|');
        l.id = stoi(id);
        l.disponible = (disponible == "1");
        libros.push_back(l);
    }
    archivo.close();
    return true;
}

bool cargarUsuarios(vector<Usuario>& usuarios) {
    ifstream archivo("usuarios.txt");
    if (!archivo.is_open()) {
        return false;
    }
    usuarios.clear();
    string linea;
    while (getline(archivo, linea)) {
        if (linea == "") {
            continue;
        }
        stringstream ss(linea);
        string id;
        Usuario u;
        getline(ss, id, '|');
        getline(ss, u.nombre, '|');
        getline(ss, u.carne, '|');
        u.id = stoi(id);
        usuarios.push_back(u);
    }
    archivo.close();
    return true;
}

bool cargarPrestamos(vector<Prestamo>& prestamos) {
    ifstream archivo("prestamos.txt");
    if (!archivo.is_open()) {
        return false;
    }
    prestamos.clear();
    string linea;
    while (getline(archivo, linea)) {
        if (linea == "") {
            continue;
        }
        stringstream ss(linea);
        string idPrestamo, idLibro, idUsuario;
        Prestamo p;
        getline(ss, idPrestamo, '|');
        getline(ss, idLibro, '|');
        getline(ss, idUsuario, '|');
        getline(ss, p.fecha, '|');
        p.idPrestamo = stoi(idPrestamo);
        p.idLibro = stoi(idLibro);
        p.idUsuario = stoi(idUsuario);
        prestamos.push_back(p);
    }
    archivo.close();
    return true;
}

//   RECORRIDO Y BUSQUEDA  

// recorre el vector y muestra todos los libros
void mostrarLibros(vector<Libro>& libros) {
    if (libros.size() == 0) {
        cout << "No hay libros cargados." << endl;
        return;
    }
    for (int i = 0; i < libros.size(); i++) {
        cout << libros[i].id << " - " << libros[i].titulo << " - " << libros[i].autor;
        if (libros[i].disponible) {
            cout << " - Disponible" << endl;
        } else {
            cout << " - Prestado" << endl;
        }
    }
}

// busca un libro por id, regresa su posicion o -1 si no existe
int buscarLibroPorId(vector<Libro>& libros, int id) {
    for (int i = 0; i < libros.size(); i++) {
        if (libros[i].id == id) {
            return i;
        }
    }
    return -1;
}

// datos de ejemplo para probar mientras los otros modulos no estan listos
void cargarDatosDePrueba(vector<Libro>& libros, vector<Usuario>& usuarios, vector<Prestamo>& prestamos) {
    libros.clear();
    usuarios.clear();
    prestamos.clear();
    libros.push_back({1, "Cien anios de soledad", "Gabriel Garcia Marquez", true});
    libros.push_back({2, "El principito", "Antoine de Saint-Exupery", false});
    usuarios.push_back({1, "Josue Chavez", "2026001"});
    prestamos.push_back({1, 2, 1, "2026-10-01"});
}

//  MENU DEL MODULO  

void moduloArchivos(vector<Libro>& libros, vector<Usuario>& usuarios, vector<Prestamo>& prestamos) {
    int opcion = 0;

    cout << "   [MODULO 4: PERSISTENCIA Y ARCHIVOS]" << endl;
    cout << "1. Guardar datos en archivos (.txt)" << endl;
    cout << "2. Cargar datos desde archivos (.txt)" << endl;
    cout << "3. Ver libros cargados" << endl;
    cout << "4. Buscar libro por id" << endl;
    cout << "5. Cargar datos de prueba" << endl;
    cout << "Seleccione una opcion: ";
    cin >> opcion;

    if (cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Opcion invalida." << endl;
        return;
    }

    if (opcion == 1) {
        guardarLibros(libros);
        guardarUsuarios(usuarios);
        guardarPrestamos(prestamos);
        cout << "Datos guardados en los archivos." << endl;
    } else if (opcion == 2) {
        if (cargarLibros(libros) && cargarUsuarios(usuarios) && cargarPrestamos(prestamos)) {
            cout << "Datos cargados desde los archivos." << endl;
        } else {
            cout << "No se encontraron los archivos. Primero guarde los datos." << endl;
        }
    } else if (opcion == 3) {
        mostrarLibros(libros);
    } else if (opcion == 4) {
        int id;
        cout << "Ingrese el id del libro: ";
        cin >> id;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Id invalido." << endl;
            return;
        }
        int pos = buscarLibroPorId(libros, id);
        if (pos == -1) {
            cout << "El libro no existe." << endl;
        } else {
            cout << "Encontrado: " << libros[pos].titulo << " - " << libros[pos].autor << endl;
        }
    } else if (opcion == 5) {
        cargarDatosDePrueba(libros, usuarios, prestamos);
        cout << "Datos de prueba cargados." << endl;
    } else {
        cout << "Opcion invalida." << endl;
    }
}

// main solo para probar este modulo por separado
int main() {
    vector<Libro> libros;
    vector<Usuario> usuarios;
    vector<Prestamo> prestamos;
    int seguir = 1;

    while (seguir == 1) {
        moduloArchivos(libros, usuarios, prestamos);
        cout << "\nContinuar en el modulo? (1 = si, 0 = salir): ";
        cin >> seguir;
        cout << endl;
    }

    return 0;
}