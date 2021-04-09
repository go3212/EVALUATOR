/** @file sesiones.hh
 *  @brief Especificación de la clase 'Sesiones'.
 */

#ifndef SESIONES_HH
#define SESIONES_HH

#include <iostream>
#include <map>
#include "tipos.hh"
#include "sesion.hh"

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
    const bool add_session(const string& id, const Sesion& session);

    /** @brief Busca una sesión en el conjunto de sesiones.
     *  @param sid identificador de sesión ('userid').
     *  \post Devuelve el objeto 'Sesion' por referencia constante si se encuentra, en caso contrario, devuelve NULL.
     */
    const Sesion& get_session(const sessionid& sid) const;
};

#endif