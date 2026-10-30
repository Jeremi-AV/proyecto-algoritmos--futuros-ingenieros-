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
string matrizEstantes[3][3];
vector<Usuario> listaUsuarios;
vector<Prestamo> listaPrestamos;

void guardarDatos();
void cargarDatos();

int conteoRecursivoLibros(int indice) {
    if (indice >= (int)catalogoLibros.size()) {
        return 0;
    }
    int suma = catalogoLibros[indice].disponible ? 1 : 0;
    return suma + conteoRecursivoLibros(indice + 1);
}

void moduloCatalogo() {
    int subOpcion = 0;
    do {
        cout << "\nMODULO 1: CATALOGO DE LIBROS" << endl;
        cout << "1. Registrar libro" << endl;
        cout << "2. Ver catalogo completo" << endl;
        cout << "3. Buscar libro por titulo" << endl;
        cout << "4. Ver mapa de estantes" << endl;
        cout << "5. Asignar libro a estante" << endl;
        cout << "6. Eliminar libro" << endl;
        cout << "7. Volver al menu principal" << endl;
        cout << "Seleccione una opcion: ";
        cin >> subOpcion;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        if (subOpcion == 1) {
            Libro nuevo;
            cout << "Ingrese ID del libro: ";
            cin >> nuevo.id;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Ingrese Titulo: ";
            getline(cin, nuevo.titulo);
            cout << "Ingrese Autor: ";
            getline(cin, nuevo.autor);
            nuevo.disponible = true;

            catalogoLibros.push_back(nuevo);

        } else if (subOpcion == 2) {
            if (catalogoLibros.empty()) {
                cout << "No hay libros registrados.\n";
            } else {
                for (const auto& libro : catalogoLibros) {
                    cout << "ID: " << libro.id 
                         << " | Titulo: " << libro.titulo 
                         << " | Autor: " << libro.autor 
                         << " | Estado: " << (libro.disponible ? "Disponible" : "Prestado") << endl;
                }
            }

        } else if (subOpcion == 3) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            string busqueda;
            cout << "Ingrese el titulo a buscar: ";
            getline(cin, busqueda);
            bool encontrado = false;

            for (const auto& libro : catalogoLibros) {
                if (libro.titulo.find(busqueda) != string::npos) {
                    cout << "ID: " << libro.id 
                         << " | Titulo: " << libro.titulo 
                         << " | Autor: " << libro.autor 
                         << " | Estado: " << (libro.disponible ? "Disponible" : "Prestado") << endl;
                    encontrado = true;
                }
            }
            if (!encontrado) cout << "No se encontro el libro.\n";

        } else if (subOpcion == 4) {
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    cout << "[" << matrizEstantes[i][j] << "]\t";
                }
                cout << endl;
            }

        } else if (subOpcion == 5) {
            int fila = 0, columna = 0;
            string nombreLibro;
            cout << "Ingrese fila (0 a 2): ";
            cin >> fila;
            cout << "Ingrese columna (0 a 2): ";
            cin >> columna;
            
            if (fila >= 0 && fila < 3 && columna >= 0 && columna < 3) {
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Ingrese titulo del libro: ";
                getline(cin, nombreLibro);
                matrizEstantes[fila][columna] = nombreLibro;
            } else {
                cout << "Coordenadas fuera de rango.\n";
            }

        } else if (subOpcion == 6) {
            int idEliminar = 0;
            cout << "Ingrese ID del libro a eliminar: ";
            cin >> idEliminar;
            bool eliminado = false;

            for (size_t i = 0; i < catalogoLibros.size(); i++) {
                if (catalogoLibros[i].id == idEliminar) {
                    catalogoLibros.erase(catalogoLibros.begin() + i);
                    eliminado = true;
                    break;
                }
            }
            if (!eliminado) cout << "No se encontro el ID.\n";
        }
    } while (subOpcion != 7);

    guardarDatos(); // se guarda automaticamente al volver al menu principal
}

void moduloUsuarios() {
    int subOpcion = 0;
    do {
        cout << "\nMODULO 2: USUARIOS Y LECTORES" << endl;
        cout << "1. Registrar nuevo lector" << endl;
        cout << "2. Mostrar todos los lectores" << endl;
        cout << "3. Buscar usuario por Carne" << endl;
        cout << "4. Eliminar usuario" << endl;
        cout << "5. Volver al menu principal" << endl;
        cout << "Seleccione una opcion: ";
        cin >> subOpcion;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        if (subOpcion == 1) {
            Usuario u;
            cout << "Ingrese ID de Usuario: ";
            cin >> u.id;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Ingrese Nombre completo: ";
            getline(cin, u.nombre);
            cout << "Ingrese Carne/DPI: ";
            getline(cin, u.carne);

            listaUsuarios.push_back(u);

        } else if (subOpcion == 2) {
            if (listaUsuarios.empty()) {
                cout << "No hay usuarios registrados.\n";
            } else {
                for (size_t i = 0; i < listaUsuarios.size(); i++) {
                    cout << "ID: " << listaUsuarios[i].id 
                         << " | Nombre: " << listaUsuarios[i].nombre 
                         << " | Carne: " << listaUsuarios[i].carne << endl;
                }
            }

        } else if (subOpcion == 3) {
            string carneBuscar;
            cout << "Ingrese Carne o DPI a buscar: ";
            cin >> carneBuscar;
            bool hallado = false;

            for (const auto& u : listaUsuarios) {
                if (u.carne == carneBuscar) {
                    cout << "ID: " << u.id << " | Nombre: " << u.nombre << endl;
                    hallado = true;
                    break;
                }
            }
            if (!hallado) cout << "No existe el usuario.\n";

        } else if (subOpcion == 4) {
            int idEliminar = 0;
            cout << "Ingrese ID de usuario a eliminar: ";
            cin >> idEliminar;
            bool eliminado = false;

            for (size_t i = 0; i < listaUsuarios.size(); i++) {
                if (listaUsuarios[i].id == idEliminar) {
                    listaUsuarios.erase(listaUsuarios.begin() + i);
                    eliminado = true;
                    break;
                }
            }
            if (!eliminado) cout << "No se encontro el ID.\n";
        }
    } while (subOpcion != 5);

    guardarDatos(); // se guarda automaticamente al volver al menu principal
}

void moduloPrestamos() {
    int subOpcion = 0;
    do {
        cout << "\nMODULO 3: PRESTAMOS Y DEVOLUCIONES" << endl;
        cout << "1. Registrar prestamo" << endl;
        cout << "2. Registrar devolucion" << endl;
        cout << "3. Ver historial de prestamos" << endl;
        cout << "4. Cancelar prestamo" << endl;
        cout << "5. Volver al menu principal" << endl;
        cout << "Seleccione una opcion: ";
        cin >> subOpcion;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        if (subOpcion == 1) {
            Prestamo p;
            cout << "Ingrese ID del Prestamo: ";
            cin >> p.idPrestamo;
            cout << "Ingrese ID del Libro: ";
            cin >> p.idLibro;
            cout << "Ingrese ID del Usuario: ";
            cin >> p.idUsuario;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Ingrese Fecha: ";
            getline(cin, p.fecha);

            bool libroExiste = false;
            for (auto& libro : catalogoLibros) {
                if (libro.id == p.idLibro) {
                    libroExiste = true;
                    if (libro.disponible) {
                        libro.disponible = false;
                        listaPrestamos.push_back(p);
                    } else {
                        cout << "El libro no esta disponible.\n";
                    }
                    break;
                }
            }
            if (!libroExiste) cout << "No existe el libro.\n";

        } else if (subOpcion == 2) {
            int idLibroDevolver = 0;
            cout << "Ingrese ID del libro a devolver: ";
            cin >> idLibroDevolver;
            bool devuelto = false;

            for (auto& libro : catalogoLibros) {
                if (libro.id == idLibroDevolver) {
                    libro.disponible = true;
                    devuelto = true;
                    break;
                }
            }
            if (!devuelto) cout << "No se encontro el libro.\n";

        } else if (subOpcion == 3) {
            if (listaPrestamos.empty()) {
                cout << "No hay prestamos registrados.\n";
            } else {
                for (const auto& p : listaPrestamos) {
                    cout << "Prestamo ID: " << p.idPrestamo 
                         << " | Libro ID: " << p.idLibro 
                         << " | Usuario ID: " << p.idUsuario 
                         << " | Fecha: " << p.fecha << endl;
                }
            }

        } else if (subOpcion == 4) {
            int idCancelar = 0;
            cout << "Ingrese ID del prestamo a cancelar: ";
            cin >> idCancelar;
            bool cancelado = false;

            for (size_t i = 0; i < listaPrestamos.size(); i++) {
                if (listaPrestamos[i].idPrestamo == idCancelar) {
                    int idLibro = listaPrestamos[i].idLibro;
                    for (auto& libro : catalogoLibros) {
                        if (libro.id == idLibro) {
                            libro.disponible = true;
                            break;
                        }
                    }
                    listaPrestamos.erase(listaPrestamos.begin() + i);
                    cancelado = true;
                    break;
                }
            }
            if (!cancelado) cout << "No se encontro el prestamo.\n";
        }
    } while (subOpcion != 5);

    guardarDatos(); // se guarda automaticamente al volver al menu principal
}

void guardarDatos() {
    ofstream fileLibros("libros.txt");
    if (fileLibros.is_open()) {
        for (const auto& l : catalogoLibros) {
            fileLibros << l.id << "|" << l.titulo << "|" << l.autor << "|" << l.disponible << "\n";
        }
        fileLibros.close();
    }

    ofstream fileUsuarios("usuarios.txt");
    if (fileUsuarios.is_open()) {
        for (const auto& u : listaUsuarios) {
            fileUsuarios << u.id << "|" << u.nombre << "|" << u.carne << "\n";
        }
        fileUsuarios.close();
    }

    ofstream filePrestamos("prestamos.txt");
    if (filePrestamos.is_open()) {
        for (const auto& p : listaPrestamos) {
            filePrestamos << p.idPrestamo << "|" << p.idLibro << "|" << p.idUsuario << "|" << p.fecha << "\n";
        }
        filePrestamos.close();
    }

    // Mapa de estantes: una celda por linea (9 lineas)
    ofstream fileEstantes("estantes.txt");
    if (fileEstantes.is_open()) {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                fileEstantes << matrizEstantes[i][j] << "\n";
            }
        }
        fileEstantes.close();
    }
}

void cargarDatos() {
    catalogoLibros.clear();
    listaUsuarios.clear();
    listaPrestamos.clear();

    ifstream fileLibros("libros.txt");
    if (fileLibros.is_open()) {
        string linea;
        while (getline(fileLibros, linea)) {
            if (linea.empty()) continue;
            stringstream ss(linea);
            string idStr, titulo, autor, dispStr;
            getline(ss, idStr, '|');
            getline(ss, titulo, '|');
            getline(ss, autor, '|');
            getline(ss, dispStr, '|');

            Libro l;
            l.id = stoi(idStr);
            l.titulo = titulo;
            l.autor = autor;
            l.disponible = (dispStr == "1");
            catalogoLibros.push_back(l);
        }
        fileLibros.close();
    }

    ifstream fileUsuarios("usuarios.txt");
    if (fileUsuarios.is_open()) {
        string linea;
        while (getline(fileUsuarios, linea)) {
            if (linea.empty()) continue;
            stringstream ss(linea);
            string idStr, nombre, carne;
            getline(ss, idStr, '|');
            getline(ss, nombre, '|');
            getline(ss, carne, '|');

            Usuario u;
            u.id = stoi(idStr);
            u.nombre = nombre;
            u.carne = carne;
            listaUsuarios.push_back(u);
        }
        fileUsuarios.close();
    }

    ifstream filePrestamos("prestamos.txt");
    if (filePrestamos.is_open()) {
        string linea;
        while (getline(filePrestamos, linea)) {
            if (linea.empty()) continue;
            stringstream ss(linea);
            string idPStr, idLStr, idUStr, fecha;
            getline(ss, idPStr, '|');
            getline(ss, idLStr, '|');
            getline(ss, idUStr, '|');
            getline(ss, fecha, '|');

            Prestamo p;
            p.idPrestamo = stoi(idPStr);
            p.idLibro = stoi(idLStr);
            p.idUsuario = stoi(idUStr);
            p.fecha = fecha;
            listaPrestamos.push_back(p);
        }
        filePrestamos.close();
    }

    // Mapa de estantes
    ifstream fileEstantes("estantes.txt");
    if (fileEstantes.is_open()) {
        string linea;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (getline(fileEstantes, linea)) {
                    matrizEstantes[i][j] = linea;
                }
            }
        }
        fileEstantes.close();
    }
}

void moduloArchivos() {
    int subOpcion = 0;
    do {
        cout << "\nMODULO 4: PERSISTENCIA Y ARCHIVOS" << endl;
        cout << "1. Guardar datos en archivos" << endl;
        cout << "2. Cargar datos desde archivos" << endl;
        cout << "3. Volver al menu principal" << endl;
        cout << "Seleccione una opcion: ";
        cin >> subOpcion;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        if (subOpcion == 1) {
            guardarDatos();
            cout << "Datos guardados correctamente.\n";
        } else if (subOpcion == 2) {
            cargarDatos();
            cout << "Datos cargados desde los archivos.\n";
        }
    } while (subOpcion != 3);
}

void moduloReportes() {
    cout << "\nMODULO 5: REPORTES Y RECURSIVIDAD" << endl;
    cout << "Total de Libros registrados: " << catalogoLibros.size() << endl;
    cout << "Total de Usuarios registrados: " << listaUsuarios.size() << endl;
    cout << "Total de Prestamos realizados: " << listaPrestamos.size() << endl;
    cout << "Libros disponibles (Conteo Recursivo): " << conteoRecursivoLibros(0) << endl;
}

int mostrarMenu() {
    int opcion = 0;

    cout << "\nSISTEMA DE GESTION DE BIBLIOTECA" << endl;
    cout << "1. Catalogo de Libros" << endl;
    cout << "2. Usuarios / Lectores" << endl;
    cout << "3. Prestamos y Devoluciones" << endl;
    cout << "4. Persistencia y Archivos" << endl;
    cout << "5. Reportes y Recursividad" << endl;
    cout << "6. Salir" << endl;
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
            guardarDatos();
            break;
        default:
            cout << "Opcion invalida." << endl;
            break;
    }
}

void inicializarMatriz() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            matrizEstantes[i][j] = "Disponible";
        }
    }
}

int main() {
    inicializarMatriz();
    cargarDatos();
    
    int opcion = 0;

    do {
        opcion = mostrarMenu();
        procesarOpcion(opcion);
    } while (opcion != 6);

    return 0;
}