#ifndef SESIONES_HH
#define SESIONES_HH

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include "hh/sesion.hh"

using namespace std;

// N > 0, Sin repeticiones, 

/** @class Sesiones
 *  @brief Holds data for a session: session name ('name') and a binary tree of problems ('problems') 
 */
class Sesiones
{
private:
    int total;
    map<string, Sesion> sessionMap;
public:
    /** @brief Constructor por defecto de clase sobrecargado.
     *  \post Número total de sesiones es cero. Conjunto de sesiones ('sessionMap') no definido.
     */ 
    Sesiones();

    /** @brief Constructor de clase sobrecargado, añade una sesión al instanciar la clase.
     *  @param id identificador de la sesión.
     *  @param problem objeto del tipo 'Sesion'.
     *  \post Se añade una sesión y se incializa el conjunto de sesiones.
     */ 
    Sesiones(const string& id, const Sesion& session);

    /** @brief Añade una nueva sesión a la lista de sesiones.
     *  @param id identificador de la sesión.
     *  @param session objeto de tipo 'Sesión'.
     *  \post añade una sesión al mapa de sesiones ('sessionMap') si no existia previamente. Devuelve si la sesión se ha añadido ('true') o si ya existia ('false').
     */
    bool add_session(const string& id, const Sesion& session);

};

#endif