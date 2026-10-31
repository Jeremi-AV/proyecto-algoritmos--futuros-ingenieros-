#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include <fstream>
#include <sstream>

using namespace std;

const int MAX_LIBROS_PRESTAMO = 5;
const int MULTA_QUETZALES = 5;

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
    vector<int> idsLibros;
    int idUsuario;
    string fecha;
    string fechaEntrega;
    vector<int> idsDevueltos;
};

vector<Libro> catalogoLibros;
string matrizEstantes[3][3];
vector<Usuario> listaUsuarios;
vector<Prestamo> listaPrestamos;

void guardarDatos();
void cargarDatos();

Libro* buscarLibro(int id) {
    for (size_t i = 0; i < catalogoLibros.size(); i++) {
        if (catalogoLibros[i].id == id) {
            return &catalogoLibros[i];
        }
    }
    return nullptr;
}

bool parsearFecha(const string& texto, int& valor) {
    string t = texto;
    for (size_t i = 0; i < t.size(); i++) {
        if (t[i] == '-') t[i] = '/';
    }
    stringstream ss(t);
    int dia = 0, mes = 0, anio = 0;
    char s1 = 0, s2 = 0;
    if (!(ss >> dia >> s1 >> mes >> s2 >> anio)) return false;
    if (s1 != '/' || s2 != '/') return false;
    string resto;
    if (ss >> resto) return false;
    if (anio < 1900 || anio > 2200 || mes < 1 || mes > 12 || dia < 1) return false;

    int diasMes[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    bool bisiesto = (anio % 4 == 0 && anio % 100 != 0) || (anio % 400 == 0);
    int maxDia = diasMes[mes - 1];
    if (mes == 2 && bisiesto) maxDia = 29;
    if (dia > maxDia) return false;

    valor = anio * 10000 + mes * 100 + dia;
    return true;
}

string formatearFecha(int valor) {
    int anio = valor / 10000;
    int mes = (valor / 100) % 100;
    int dia = valor % 100;
    stringstream ss;
    ss << (dia < 10 ? "0" : "") << dia << "/" << (mes < 10 ? "0" : "") << mes << "/" << anio;
    return ss.str();
}

string pedirFecha(const string& mensaje, int& valor) {
    string texto;
    while (true) {
        cout << mensaje;
        getline(cin, texto);
        if (parsearFecha(texto, valor)) {
            return formatearFecha(valor);
        }
        cout << "Fecha invalida. Use el formato dd/mm/aaaa (ejemplo: 30/10/2026).\n";
    }
}

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

            int cantidad = 0;
            do {
                cout << "Cuantos libros se llevara (maximo " << MAX_LIBROS_PRESTAMO << "): ";
                cin >> cantidad;
                if (cin.fail()) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cantidad = 0;
                }
                if (cantidad < 1 || cantidad > MAX_LIBROS_PRESTAMO) {
                    cout << "Cantidad invalida. Debe ser de 1 a " << MAX_LIBROS_PRESTAMO << ".\n";
                }
            } while (cantidad < 1 || cantidad > MAX_LIBROS_PRESTAMO);

            bool cancelado = false;
            for (int n = 1; n <= cantidad && !cancelado; n++) {
                bool valido = false;
                while (!valido) {
                    int idL = 0;
                    cout << "Ingrese ID del libro " << n << " de " << cantidad << " (0 para cancelar): ";
                    cin >> idL;

                    if (cin.fail()) {
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "ID invalido.\n";
                        continue;
                    }
                    if (idL == 0) {
                        cancelado = true;
                        break;
                    }

                    Libro* libro = buscarLibro(idL);
                    bool repetido = false;
                    for (size_t k = 0; k < p.idsLibros.size(); k++) {
                        if (p.idsLibros[k] == idL) repetido = true;
                    }

                    if (libro == nullptr) {
                        cout << "No existe el libro.\n";
                    } else if (!libro->disponible) {
                        cout << "El libro no esta disponible.\n";
                    } else if (repetido) {
                        cout << "Ese libro ya esta en este prestamo.\n";
                    } else {
                        p.idsLibros.push_back(idL);
                        valido = true;
                    }
                }
            }

            if (cancelado) {
                cout << "Prestamo cancelado, no se registro nada.\n";
            } else {
                cout << "Ingrese ID del Usuario: ";
                cin >> p.idUsuario;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                int valFecha = 0, valEntrega = 0;
                p.fecha = pedirFecha("Ingrese Fecha del prestamo (dd/mm/aaaa): ", valFecha);
                while (true) {
                    p.fechaEntrega = pedirFecha("Ingrese Fecha de entrega, cuando debe devolver los libros (dd/mm/aaaa): ", valEntrega);
                    if (valEntrega >= valFecha) break;
                    cout << "La fecha de entrega no puede ser antes de la fecha del prestamo.\n";
                }

                for (size_t k = 0; k < p.idsLibros.size(); k++) {
                    buscarLibro(p.idsLibros[k])->disponible = false;
                }
                listaPrestamos.push_back(p);
                cout << "Prestamo registrado con " << p.idsLibros.size() << " libro(s).\n";
                cout << "Tu tiempo limite de entrega es hasta: " << p.fechaEntrega << endl;
                cout << "Si no cumples con la fecha limite se te dara una multa de "
                     << MULTA_QUETZALES << " quetzales.\n";
            }

        } else if (subOpcion == 2) {
            int idEstudiante = 0, idLibroDevolver = 0;
            cout << "Ingrese ID del estudiante: ";
            cin >> idEstudiante;
            cout << "Ingrese ID del libro a devolver: ";
            cin >> idLibroDevolver;

            if (cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Dato invalido.\n";
                continue;
            }
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            Prestamo* prestamo = nullptr;
            for (size_t i = 0; i < listaPrestamos.size() && prestamo == nullptr; i++) {
                if (listaPrestamos[i].idUsuario != idEstudiante) continue;
                for (size_t k = 0; k < listaPrestamos[i].idsLibros.size(); k++) {
                    if (listaPrestamos[i].idsLibros[k] == idLibroDevolver) {
                        prestamo = &listaPrestamos[i];
                        break;
                    }
                }
            }

            if (prestamo == nullptr) {
                cout << "Ese estudiante no tiene prestado ese libro.\n";
            } else {
                int valDevolucion = 0;
                string fechaDevolucion = pedirFecha("Ingrese la fecha de devolucion (dd/mm/aaaa): ", valDevolucion);

                int valLimite = 0;
                if (parsearFecha(prestamo->fechaEntrega, valLimite)) {
                    if (valDevolucion > valLimite) {
                        cout << "No lo entregaste a la fecha limite, tienes una multa de "
                             << MULTA_QUETZALES << " quetzales.\n";
                    }
                } else {
                    cout << "No se pudo comparar con la fecha limite (" << prestamo->fechaEntrega << ").\n";
                }

                for (size_t k = 0; k < prestamo->idsLibros.size(); k++) {
                    if (prestamo->idsLibros[k] == idLibroDevolver) {
                        prestamo->idsLibros.erase(prestamo->idsLibros.begin() + k);
                        break;
                    }
                }
                prestamo->idsDevueltos.push_back(idLibroDevolver);

                Libro* libro = buscarLibro(idLibroDevolver);
                if (libro != nullptr) libro->disponible = true;
                cout << "Devolucion registrada el " << fechaDevolucion << ".\n";
            }

        } else if (subOpcion == 3) {
            if (listaPrestamos.empty()) {
                cout << "No hay prestamos registrados.\n";
            } else {
                for (const auto& p : listaPrestamos) {
                    cout << "Prestamo ID: " << p.idPrestamo
                         << " | Libros prestados ID: ";
                    for (size_t k = 0; k < p.idsLibros.size(); k++) {
                        cout << p.idsLibros[k];
                        if (k + 1 < p.idsLibros.size()) cout << ", ";
                    }
                    if (p.idsLibros.empty()) cout << "(ninguno)";
                    cout << " | Usuario ID: " << p.idUsuario
                         << " | Fecha: " << p.fecha
                         << " | Entrega: " << p.fechaEntrega;
                    if (!p.idsDevueltos.empty()) {
                        cout << " | Devueltos: ";
                        for (size_t k = 0; k < p.idsDevueltos.size(); k++) {
                            cout << p.idsDevueltos[k];
                            if (k + 1 < p.idsDevueltos.size()) cout << ", ";
                        }
                    }
                    cout << endl;
                }
            }

        } else if (subOpcion == 4) {
            int idCancelar = 0;
            cout << "Ingrese ID del prestamo a cancelar: ";
            cin >> idCancelar;
            bool cancelado = false;

            for (size_t i = 0; i < listaPrestamos.size(); i++) {
                if (listaPrestamos[i].idPrestamo == idCancelar) {
                    for (size_t k = 0; k < listaPrestamos[i].idsLibros.size(); k++) {
                        Libro* libro = buscarLibro(listaPrestamos[i].idsLibros[k]);
                        if (libro != nullptr) libro->disponible = true;
                    }
                    listaPrestamos.erase(listaPrestamos.begin() + i);
                    cancelado = true;
                    break;
                }
            }
            if (!cancelado) cout << "No se encontro el prestamo.\n";
        }
    } while (subOpcion != 5);
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
            filePrestamos << p.idPrestamo << "|" << p.idUsuario << "|"
                          << p.fecha << "|" << p.fechaEntrega << "|";
            for (size_t k = 0; k < p.idsLibros.size(); k++) {
                filePrestamos << p.idsLibros[k];
                if (k + 1 < p.idsLibros.size()) filePrestamos << ",";
            }
            filePrestamos << "|";
            for (size_t k = 0; k < p.idsDevueltos.size(); k++) {
                filePrestamos << p.idsDevueltos[k];
                if (k + 1 < p.idsDevueltos.size()) filePrestamos << ",";
            }
            filePrestamos << "\n";
        }
        filePrestamos.close();
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
            string idPStr, idUStr, fecha, fechaEntrega, idsStr, devueltosStr;
            getline(ss, idPStr, '|');
            getline(ss, idUStr, '|');
            getline(ss, fecha, '|');
            getline(ss, fechaEntrega, '|');
            getline(ss, idsStr, '|');
            getline(ss, devueltosStr, '|');

            Prestamo p;
            try {
                p.idPrestamo = stoi(idPStr);
                p.idUsuario = stoi(idUStr);
                p.fecha = fecha;
                p.fechaEntrega = fechaEntrega;

                stringstream ssIds(idsStr);
                string unId;
                while (getline(ssIds, unId, ',')) {
                    if (!unId.empty()) p.idsLibros.push_back(stoi(unId));
                }

                stringstream ssDev(devueltosStr);
                while (getline(ssDev, unId, ',')) {
                    if (!unId.empty()) p.idsDevueltos.push_back(stoi(unId));
                }
            } catch (...) {
                continue;
            }

            if (p.idsLibros.empty() && p.idsDevueltos.empty()) continue;
            listaPrestamos.push_back(p);
        }
        filePrestamos.close();
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
        } else if (subOpcion == 2) {
            cargarDatos();
        }
    } while (subOpcion != 3);
}

void moduloReportes() {
    cout << "\nMODULO 5: REPORTES Y RECURSIVIDAD" << endl;
    cout << "Total de Libros registrados: " << catalogoLibros.size() << endl;
    cout << "Total de Usuarios registrados: " << listaUsuarios.size() << endl;
    cout << "Total de Prestamos realizados: " << listaPrestamos.size() << endl;
    cout << "Libros disponibles: " << conteoRecursivoLibros(0) << endl;
}

int mostrarMenu() {
    int opcion = 0;

    cout << "\nSISTEMA DE GESTION DE BIBLIOTECA" << endl;
    cout << "1. Catalogo de Libros" << endl;
    cout << "2. Usuarios / Lectores" << endl;
    cout << "3. Prestamos y Devoluciones" << endl;
    cout << "4. guardar Archivos" << endl;
    cout << "5. Reportes" << endl;
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