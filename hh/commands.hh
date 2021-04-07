#ifndef COMMANDS_HH
#define COMMANDS_HH

#include <iostream>
#include <string>
#include "hh/problemas.hh"
#include "hh/sesiones.hh"

using namespace std;

/** @brief Añade un nuevo problema a la lista de problemas.
 *  @param id identificador del problema.
 *  @param problem objecto del tipo 'Problema'.
 *  @param problems objeto de tipo 'Problemas'.
 *  \pre existencia de un objeto 'Problemas'.
 *  \post añade un problema al objeto 'Problemas'. 
 *        Devuelve un mensaje de error por pantalla si ya existia el problema, en caso contrario, devuelve el número total de problemas.
 */
void nuevo_problema(const string& id, const Problema& problem, const Problemas& problems);

/** @brief Añade una nueva sesión a la lista de sesiones.
 *  @param id identificador de la sesión.
 *  @param session objeto del tipo 'Sesion'.
 *  @param sessions objeto del tipo 'Sesiones'.
 *  \pre existencia de un objeto 'Sesiones', con problemas no repetidos.
 *  \post añade una sesion al objeto 'Sesiones'.
 *        Devuelve un mensaje de error por pantalla si ya existia la sesión, en caso contrario, devuelve el número total de problemas.
 */
void nueva_sesion(const string& id, const Sesion& session, const Sesiones& sessions);



#endif