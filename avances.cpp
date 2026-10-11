#include <iostream>
#include <string>
#include <vector>
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

vector<Libro> catalogoLibros;
string matrizEstantes[3][3];
vector<Usuario> listaUsuarios;
vector<Prestamo> listaPrestamos;

int conteoRecursivoLibros(int indice) {
    if (indice >= catalogoLibros.size()) {
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

        if (subOpcion == 1) {
            Libro nuevo;
            cout << "\nIngrese ID del libro: ";
            cin >> nuevo.id;
            cin.ignore();
            cout << "Ingrese Titulo: ";
            getline(cin, nuevo.titulo);
            cout << "Ingrese Autor: ";
            getline(cin, nuevo.autor);
            nuevo.disponible = true;

            catalogoLibros.push_back(nuevo);
            cout << "Libro registrado exitosamente.\n";

        } else if (subOpcion == 2) {
            cout << "\nLISTADO DE LIBROS EN CATALOGO" << endl;
            if (catalogoLibros.empty()) {
                cout << "No hay libros registrados aun.\n";
            } else {
                for (const auto& libro : catalogoLibros) {
                    cout << "ID: " << libro.id 
                         << " | Titulo: " << libro.titulo 
                         << " | Autor: " << libro.autor 
                         << " | Estado: " << (libro.disponible ? "Disponible" : "Prestado") << endl;
                }
            }

        } else if (subOpcion == 3) {
            cin.ignore();
            string busqueda;
            cout << "\nIngrese el titulo a buscar: ";
            getline(cin, busqueda);
            bool encontrado = false;

            for (const auto& libro : catalogoLibros) {
                if (libro.titulo.find(busqueda) != string::npos) {
                    cout << "Encontrado ID: " << libro.id 
                         << " | Titulo: " << libro.titulo 
                         << " | Autor: " << libro.autor << endl;
                    encontrado = true;
                }
            }
            if (!encontrado) cout << "No se encontro ningun libro con ese titulo.\n";

        } else if (subOpcion == 4) {
            cout << "\nMATRIZ FISICA DE ESTANTES" << endl;
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    cout << "[" << matrizEstantes[i][j] << "]\t";
                }
                cout << endl;
            }

        } else if (subOpcion == 5) {
            int fila = 0, columna = 0;
            string nombreLibro;
            cout << "\nIngrese fila (0 a 2): ";
            cin >> fila;
            cout << "Ingrese columna (0 a 2): ";
            cin >> columna;
            
            if (fila >= 0 && fila < 3 && columna >= 0 && columna < 3) {
                cin.ignore();
                cout << "Ingrese titulo del libro para el estante: ";
                getline(cin, nombreLibro);
                matrizEstantes[fila][columna] = nombreLibro;
                cout << "Estante actualizado exitosamente.\n";
            } else {
                cout << "Coordenadas fuera de rango.\n";
            }

        } else if (subOpcion == 6) {
            int idEliminar = 0;
            cout << "\nIngrese ID del libro a eliminar: ";
            cin >> idEliminar;
            bool eliminado = false;

            for (size_t i = 0; i < catalogoLibros.size(); i++) {
                if (catalogoLibros[i].id == idEliminar) {
                    catalogoLibros.erase(catalogoLibros.begin() + i);
                    eliminado = true;
                    cout << "Libro eliminado del catalogo exitosamente.\n";
                    break;
                }
            }
            if (!eliminado) cout << "No se encontro un libro con ese ID.\n";
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

        if (subOpcion == 1) {
            Usuario u;
            cout << "\nIngrese ID de Usuario: ";
            cin >> u.id;
            cin.ignore();
            cout << "Ingrese Nombre completo: ";
            getline(cin, u.nombre);
            cout << "Ingrese Carne/DPI: ";
            getline(cin, u.carne);

            listaUsuarios.push_back(u);
            cout << "Lector registrado exitosamente.\n";

        } else if (subOpcion == 2) {
            cout << "\nLISTA DE LECTORES REGISTRADOS" << endl;
            if (listaUsuarios.empty()) {
                cout << "No hay usuarios registrados.\n";
            } else {
                for (size_t i = 0; i < listaUsuarios.size(); i++) {
                    cout << i + 1 << ". ID: " << listaUsuarios[i].id 
                         << " | Nombre: " << listaUsuarios[i].nombre 
                         << " | Carne: " << listaUsuarios[i].carne << endl;
                }
            }

        } else if (subOpcion == 3) {
            string carneBuscar;
            cout << "\nIngrese Carne o DPI a buscar: ";
            cin >> carneBuscar;
            bool hallado = false;

            for (const auto& u : listaUsuarios) {
                if (u.carne == carneBuscar) {
                    cout << "Usuario encontrado: " << u.nombre << " ID: " << u.id << endl;
                    hallado = true;
                    break;
                }
            }
            if (!hallado) cout << "No existe un usuario con ese Carne/DPI.\n";

        } else if (subOpcion == 4) {
            int idEliminar = 0;
            cout << "\nIngrese ID de usuario a eliminar: ";
            cin >> idEliminar;
            bool eliminado = false;

            for (size_t i = 0; i < listaUsuarios.size(); i++) {
                if (listaUsuarios[i].id == idEliminar) {
                    listaUsuarios.erase(listaUsuarios.begin() + i);
                    eliminado = true;
                    cout << "Usuario eliminado exitosamente.\n";
                    break;
                }
            }
            if (!eliminado) cout << "No se encontro un usuario con ese ID.\n";
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

        if (subOpcion == 1) {
            Prestamo p;
            cout << "\nIngrese ID del Prestamo: ";
            cin >> p.idPrestamo;
            cout << "Ingrese ID del Libro a prestar: ";
            cin >> p.idLibro;
            cout << "Ingrese ID del Usuario: ";
            cin >> p.idUsuario;
            cout << "Ingrese Fecha: ";
            cin >> p.fecha;

            bool libroExiste = false;
            for (auto& libro : catalogoLibros) {
                if (libro.id == p.idLibro) {
                    libroExiste = true;
                    if (libro.disponible) {
                        libro.disponible = false;
                        listaPrestamos.push_back(p);
                        cout << "Prestamo registrado con exito.\n";
                    } else {
                        cout << "El libro ya esta prestado.\n";
                    }
                    break;
                }
            }
            if (!libroExiste) cout << "No se encontro el libro especificado.\n";

        } else if (subOpcion == 2) {
            int idLibroDevolver = 0;
            cout << "\nIngrese ID del libro a devolver: ";
            cin >> idLibroDevolver;
            bool devuelto = false;

            for (auto& libro : catalogoLibros) {
                if (libro.id == idLibroDevolver) {
                    if (!libro.disponible) {
                        libro.disponible = true;
                        devuelto = true;
                        cout << "Libro devuelto exitosamente.\n";
                    } else {
                        cout << "El libro ya estaba disponible.\n";
                        devuelto = true;
                    }
                    break;
                }
            }
            if (!devuelto) cout << "No se encontro el libro para devolucion.\n";

        } else if (subOpcion == 3) {
            cout << "\nHISTORIAL DE PRESTAMOS" << endl;
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
            cout << "\nIngrese ID del prestamo a cancelar: ";
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
                    cout << "Prestamo cancelado y libro vuelto a disponible.\n";
                    break;
                }
            }
            if (!cancelado) cout << "No se encontro un prestamo con ese ID.\n";
        }
    } while (subOpcion != 5);
}

void moduloArchivos() {
    cout << "\nMODULO 4: PERSISTENCIA Y ARCHIVOS" << endl;
    cout << "1. Guardar datos en archivos" << endl;
    cout << "2. Cargar datos desde archivos" << endl;
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
            cout << "\nOpcion invalida Intente de nuevo" << endl;
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
    int opcion = 0;

    do {
        opcion = mostrarMenu();
        procesarOpcion(opcion);
    } while (opcion != 6);

    return 0;
}