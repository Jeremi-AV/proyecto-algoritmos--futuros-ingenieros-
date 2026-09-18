// usuario.h
#ifndef USUARIO_H
#define USUARIO_H

#include <string>
#include <vector>
#include <iostream>

struct Usuario {
    std::string Identificacion; // dpi o carnet de identidad
    std::string nombre; // nombre del usuario
    std::string apellido; // apellido del usuario
    std::string correo;  // correo del usuario
    std::vector<std::string> intereses;    bool activo; // indica si el usuario esta activo o no
};
    #endif // USUARIO_H

