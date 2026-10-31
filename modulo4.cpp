// modulo4.cpp
// Modulo 4: persistencia y archivos
// Guarda y carga libros, usuarios y prestamos en archivos .txt
#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include <fstream>
#include <sstream>
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

vector<Libro> catalogoLibros;
vector<Usuario> listaUsuarios;
vector<Prestamo> listaPrestamos;

// ---------- GUARDAR ----------
// cada linea del archivo es un registro y los campos van separados por |

void guardarLibros() {
    ofstream archivo("libros.txt");
    for (int i = 0; i < (int)catalogoLibros.size(); i++) {
        archivo << catalogoLibros[i].id << "|"
                << catalogoLibros[i].titulo << "|"
                << catalogoLibros[i].autor << "|"
                << catalogoLibros[i].disponible << endl;
    }
    archivo.close();
}

void guardarUsuarios() {
    ofstream archivo("usuarios.txt");
    for (int i = 0; i < (int)listaUsuarios.size(); i++) {
        archivo << listaUsuarios[i].id << "|"
                << listaUsuarios[i].nombre << "|"
                << listaUsuarios[i].carne << endl;
    }
    archivo.close();
}

void guardarPrestamos() {
    ofstream archivo("prestamos.txt");
    for (int i = 0; i < (int)listaPrestamos.size(); i++) {
        archivo << listaPrestamos[i].idPrestamo << "|"
                << listaPrestamos[i].idLibro << "|"
                << listaPrestamos[i].idUsuario << "|"
                << listaPrestamos[i].fecha << endl;
    }
    archivo.close();
}

void guardarDatos() {
    guardarLibros();
    guardarUsuarios();
    guardarPrestamos();
}

// ---------- CARGAR ----------
// si el archivo no existe no hace nada; las lineas dañadas se saltan

void cargarLibros() {
    ifstream archivo("libros.txt");
    if (!archivo.is_open()) {
        return;
    }
    catalogoLibros.clear();
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
        try {
            l.id = stoi(id);
        } catch (...) {
            continue;
        }
        l.disponible = (disponible == "1");
        catalogoLibros.push_back(l);
    }
    archivo.close();
}

void cargarUsuarios() {
    ifstream archivo("usuarios.txt");
    if (!archivo.is_open()) {
        return;
    }
    listaUsuarios.clear();
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
        try {
            u.id = stoi(id);
        } catch (...) {
            continue;
        }
        listaUsuarios.push_back(u);
    }
    archivo.close();
}

void cargarPrestamos() {
    ifstream archivo("prestamos.txt");
    if (!archivo.is_open()) {
        return;
    }
    listaPrestamos.clear();
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
        try {
            p.idPrestamo = stoi(idPrestamo);
            p.idLibro = stoi(idLibro);
            p.idUsuario = stoi(idUsuario);
        } catch (...) {
            continue;
        }
        listaPrestamos.push_back(p);
    }
    archivo.close();
}

void cargarDatos() {
    cargarLibros();
    cargarUsuarios();
    cargarPrestamos();
}

// ---------- RECORRIDO Y BUSQUEDA ----------

// recorre el vector y muestra todos los libros
void verLibros() {
    if (catalogoLibros.size() == 0) {
        cout << "No hay libros registrados." << endl;
        return;
    }
    for (int i = 0; i < (int)catalogoLibros.size(); i++) {
        cout << catalogoLibros[i].id << " - " << catalogoLibros[i].titulo
             << " - " << catalogoLibros[i].autor;
        if (catalogoLibros[i].disponible) {
            cout << " - Disponible" << endl;
        } else {
            cout << " - Prestado" << endl;
        }
    }
}

// busca un libro por id, regresa su posicion o -1 si no existe
int buscarLibroPorId(int id) {
    for (int i = 0; i < (int)catalogoLibros.size(); i++) {
        if (catalogoLibros[i].id == id) {
            return i;
        }
    }
    return -1;
}

// ---------- MENU DEL MODULO ----------

void moduloArchivos() {
    int subOpcion = 0;
    do {
        cout << "\nMODULO 4: PERSISTENCIA Y ARCHIVOS" << endl;
        cout << "1. Guardar datos en archivos" << endl;
        cout << "2. Cargar datos desde archivos" << endl;
        cout << "3. Ver libros" << endl;
        cout << "4. Buscar libro por id" << endl;
        cout << "5. Volver al menu principal" << endl;
        cout << "Seleccione una opcion: ";
        cin >> subOpcion;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Opcion invalida." << endl;
            continue;
        }

        if (subOpcion == 1) {
            guardarDatos();
            cout << "Datos guardados: " << catalogoLibros.size() << " libros, "
                 << listaUsuarios.size() << " usuarios, "
                 << listaPrestamos.size() << " prestamos." << endl;
        } else if (subOpcion == 2) {
            cargarDatos();
            cout << "Datos cargados: " << catalogoLibros.size() << " libros, "
                 << listaUsuarios.size() << " usuarios, "
                 << listaPrestamos.size() << " prestamos." << endl;
        } else if (subOpcion == 3) {
            verLibros();
        } else if (subOpcion == 4) {
            int id;
            cout << "Ingrese el id del libro: ";
            cin >> id;
            if (cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Id invalido." << endl;
                continue;
            }
            int pos = buscarLibroPorId(id);
            if (pos == -1) {
                cout << "El libro no existe." << endl;
            } else {
                cout << "Encontrado: " << catalogoLibros[pos].titulo
                     << " - " << catalogoLibros[pos].autor << endl;
            }
        } else if (subOpcion != 5) {
            cout << "Opcion invalida." << endl;
        }
    } while (subOpcion != 5);
}

int main() {
    cargarDatos();

    // datos de ejemplo, solo si todavia no hay archivos guardados
    if (catalogoLibros.size() == 0 && listaUsuarios.size() == 0) {
        catalogoLibros.push_back({1, "Cien anios de soledad", "Gabriel Garcia Marquez", true});
        catalogoLibros.push_back({2, "El principito", "Antoine de Saint-Exupery", false});
        listaUsuarios.push_back({1, "Josue Chavez", "2026001"});
        listaPrestamos.push_back({1, 2, 1, "2026-10-01"});
    }

    moduloArchivos();
    return 0;
}