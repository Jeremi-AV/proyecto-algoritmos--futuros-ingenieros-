#ifndef BIBLIOTECA_H
#define BIBLIOTECA_H

#include <string>
#include <vector>

enum EstadoLibro { DISPONIBLE, NO_DISPONIBLE };

struct Libro {
    std::string titulo;
    int total;        
    int disponibles;    
    EstadoLibro estado; 
};

struct Prestamo {
    int id;
    std::string titulo;
    std::string usuario;
    std::string fechaPrestamo;
    bool activo;     
};

struct Devolucion {
    int idPrestamo;
    std::string titulo;
    std::string usuario;
    std::string fechaDevolucion;
};

enum Resultado {
    OK,
    DATOS_INVALIDOS,
    LIBRO_NO_ENCONTRADO,
    SIN_EJEMPLARES,
    PRESTAMO_DUPLICADO,
    PRESTAMO_NO_ENCONTRADO,
    YA_DEVUELTO
};

int         buscarLibro(const std::vector<Libro>& libros, const std::string& titulo); // -1 si no existe
Resultado   agregarLibro(std::vector<Libro>& libros, const std::string& titulo, int cantidad);
Resultado   consultarDisponibilidad(const std::vector<Libro>& libros, const std::string& titulo, int& disponibles, int& total);
void        mostrarDisponibilidad(const std::vector<Libro>& libros, const std::string& titulo);
void        mostrarInventario(const std::vector<Libro>& libros);
Resultado   descontarEjemplar(std::vector<Libro>& libros, const std::string& titulo); // por prestamo
Resultado   reponerEjemplar(std::vector<Libro>& libros, const std::string& titulo);   // por devolucion

void        actualizarEstado(Libro& libro);
void        actualizarTodosLosEstados(std::vector<Libro>& libros);
std::string estadoATexto(EstadoLibro estado);

Resultado   crearPrestamo(std::vector<Libro>& libros, std::vector<Prestamo>& prestamos,
                          const std::string& titulo, const std::string& usuario, int& idGenerado);
bool        usuarioTienePrestamoActivo(const std::vector<Prestamo>& prestamos,
                                       const std::string& titulo, const std::string& usuario);
void        mostrarPrestamosActivos(const std::vector<Prestamo>& prestamos);

Resultado   registrarDevolucion(std::vector<Libro>& libros, std::vector<Prestamo>& prestamos,
                                std::vector<Devolucion>& devoluciones, int idPrestamo);
void        mostrarDevoluciones(const std::vector<Devolucion>& devoluciones);

std::string mensajeResultado(Resultado r);
std::string fechaActual();


void ejecutarModuloPrestamos(std::vector<Libro>& libros,
                             std::vector<Prestamo>& prestamos,
                             std::vector<Devolucion>& devoluciones);

#endif