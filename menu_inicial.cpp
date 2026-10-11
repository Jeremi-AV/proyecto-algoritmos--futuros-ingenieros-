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

void moduloCatalogo() {
    int subOpcion = 0;
    do {
        cout << "\n--- [MODULO 1: CATALOGO DE LIBROS] ---" << endl;
        cout << "1. Registrar libro (Carga)" << endl;
        cout << "2. Ver catalogo completo (Recorrido)" << endl;
        cout << "3. Buscar libro por titulo (Busqueda)" << endl;
        cout << "4. Ver mapa de estantes (Matriz)" << endl;
        cout << "5. Volver al menu principal" << endl;
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
            cout << "-> Libro registrado exitosamente en el vector.\n";

        } else if (subOpcion == 2) {
          
            cout << "\n--- LISTADO DE LIBROS EN CATALOGO ---" << endl;
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
                    cout << "¡Encontrado! ID: " << libro.id 
                         << " | Titulo: " << libro.titulo 
                         << " | Autor: " << libro.autor << endl;
                    encontrado = true;
                }
            }
            if (!encontrado) cout << "No se encontro ningun libro con ese titulo.\n";

        } else if (subOpcion == 4) {
           
            cout << "\n--- MATRIZ FISICA DE ESTANTES (3x3) ---" << endl;
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    cout << "[" << matrizEstantes[i][j] << "]\t";
                }
                cout << endl;
            }
        }
    } while (subOpcion != 5);
}

void moduloUsuarios() {
    int subOpcion = 0;
    do {
        cout << "\nMODULO 2: USUARIOS Y LECTORES" << endl;
        cout << "1. Registrar nuevo lector (Carga)" << endl;
        cout << "2. Mostrar todos los lectores (Recorrido)" << endl;
        cout << "3. Buscar usuario por Carne (Busqueda)" << endl;
        cout << "4. Volver al menu principal" << endl;
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
            cout << "-> Lector registrado exitosamente.\n";

        } else if (subOpcion == 2) {
            // RECORRIDO
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
                    cout << "Usuario encontrado: " << u.nombre << " (ID: " << u.id << ")\n";
                    hallado = true;
                    break;
                }
            }
            if (!hallado) cout << "No existe un usuario con ese Carne/DPI.\n";
        }
    } while (subOpcion != 4);
}


void moduloPrestamos() {
    int subOpcion = 0;
    do {
        cout << "\nMODULO 3: PRESTAMOS Y DEVOLUCIONES" << endl;
        cout << "1. Registrar prestamo (Carga)" << endl;
        cout << "2. Ver historial de prestamos (Recorrido)" << endl;
        cout << "3. Volver al menu principal" << endl;
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
            cout << "Ingrese Fecha (DD/MM/AAAA): ";
            cin >> p.fecha;

            for (auto& libro : catalogoLibros) {
                if (libro.id == p.idLibro) {
                    libro.disponible = false;
                    break;
                }
            }

            listaPrestamos.push_back(p);
            cout << "-> Prestamo registrado y libro marcado como prestado.\n";

        } else if (subOpcion == 2) {
         
            cout << "\nHISTORIAL DE PRESTAMOS" << endl;
            if (listaPrestamos.empty()) {
                cout << "No hay prestamos registrados.\n";
            } else {
                for (const auto& p : listaPrestamos) {
                    cout << "Prestamo #" << p.idPrestamo 
                         << " | Libro ID: " << p.idLibro 
                         << " | Usuario ID: " << p.idUsuario 
                         << " | Fecha: " << p.fecha << endl;
                }
            }
        }
    } while (subOpcion != 3);
}


void moduloArchivos() {
    cout << "\nMODULO 4: PERSISTENCIA Y ARCHIVOS" << endl;
    cout << "1. Guardar datos en archivos (.txt)" << endl;
    cout << "2. Cargar datos desde archivos (.txt)" << endl;
    cout << "*(En desarrollo para entregas posteriores)*" << endl;
}


void moduloReportes() {
    cout << "\nMODULO 5: REPORTES Y RECURSIVIDAD" << endl;
    cout << "Total de Libros registrados: " << catalogoLibros.size() << endl;
    cout << "Total de Usuarios registrados: " << listaUsuarios.size() << endl;
    cout << "Total de Prestamos realizados: " << listaPrestamos.size() << endl;
}


int mostrarMenu() {
    int opcion = 0;

    cout << "   SISTEMA DE GESTION DE BIBLIOTECA   " << endl;
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
            cout << "\nCerrando el sistema..." << endl;
            break;
        default:
            cout << "\nOpcion invalida. Intente de nuevo.\n" << endl;
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