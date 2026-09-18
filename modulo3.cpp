// usuario.h
#ifndef USUARIO_H
#define USUARIO_H

#include <string>
#include <vector>
#include <iostream>

struct Usuario {
    std::string Identificacion;    //dpi o carnet de identidad
    std::string nombre;            //nombre del usuario
    std::string apellido;          //apellido del usuario
    std::string correo;            //correo del usuario
    std::vector<std::string> intereses;
    bool activo;                     //estado del usuario (activo o inactivo)
};
#endif

bool validaridentificacion(const std::string& identificacion) {
    // Verificar que la identificación tenga 13 dígitos
    if (identificacion.length() != 13) {
        return false;
    }
    // Verificar que todos los caracteres sean dígitos
    for (char c : identificacion) {
        if (!isdigit(c)) {
            return false;
        }
    }
    return true;
}
 bool existeUsuario(const std::vector<Usuario>& usuarios, const std::string& identificacion) {
    for (const auto& usuario : usuarios) {
        if (usuario.Identificacion == identificacion) {
            return true;
        }
    }
    return false;
}
void registrarUsuario(std::vector<Usuario>& usuarios) {
    Usuario nuevoUsuario;
    std::cout << "Ingrese la identificación (13 dígitos): ";
    std::cin >> nuevoUsuario.Identificacion;

    // Validar la identificación
    if (!validaridentificacion(nuevoUsuario.Identificacion)) {
        std::cout << "Identificación inválida. Debe tener 13 dígitos." << std::endl;
        return;
    }

    // Verificar si el usuario ya existe
    if (existeUsuario(usuarios, nuevoUsuario.Identificacion)) {
        std::cout << "El usuario con esta identificación ya existe." << std::endl;
        return;
    }

    std::cout << "Ingrese el nombre: ";
    std::cin >> nuevoUsuario.nombre;
    std::cout << "Ingrese el apellido: ";
    std::cin >> nuevoUsuario.apellido;
    std::cout << "Ingrese el correo: ";
    std::cin >> nuevoUsuario.correo;

    // Inicializar intereses y estado
    nuevoUsuario.intereses.clear();
    nuevoUsuario.activo = true;

    // Agregar el nuevo usuario a la lista
    usuarios.push_back(nuevoUsuario);
    std::cout << "Usuario registrado exitosamente." << std::endl;
}
void consultarUsuario(const std::vector<Usuario>& listausuarios) {
    std::string idbusqueda;
    std::cout << "Ingrese la identificación del usuario a consultar: ";
    std::cin >> idbusqueda;

    for (const auto& usuario : listausuarios) {
        if (usuario.Identificacion == idbusqueda) {
            std::cout << "Nombre: " << usuario.nombre << std::endl;
            std::cout << "Apellido: " << usuario.apellido << std::endl;
            std::cout << "Correo: " << usuario.correo << std::endl;
            std::cout << "Intereses: ";
            for (const auto& interes : usuario.intereses) {
                std::cout << interes << " ";
            }
            std::cout << std::endl;
            std::cout << "Estado: " << (usuario.activo ? "Activo" : "Inactivo") << std::endl;
            return;
        }
    }
    std::cout << "Usuario no encontrado." << std::endl;
}
