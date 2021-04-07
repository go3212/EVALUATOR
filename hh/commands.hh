#ifndef COMMANDS_HH
#define COMMANDS_HH

#include <iostream>
#include <string>
#include "hh/problemas.hh"
#include "hh/sesiones.hh"
#include "hh/cursos.hh"
#include "hh/usuarios.hh"

using namespace std;

/** @brief Añade un nuevo problema a la lista de problemas.
 *  @param id identificador del problema.
 *  @param problems objeto de tipo 'Problemas'.
 *  \pre existencia de un objeto 'Problemas'.
 *  \post añade un problema al objeto 'Problemas'. 
 *        Devuelve un mensaje de error por pantalla si ya existia el problema, en caso contrario, devuelve por pantalla el número total de problemas.
 */
void nuevo_problema(const string& id, const Problemas& problems);

/** @brief Añade una nueva sesión a la lista de sesiones.
 *  @param id identificador de la sesión.
 *  @param sessions objeto del tipo 'Sesiones'.
 *  \pre existencia de un objeto 'Sesiones', con problemas no repetidos.
 *  \post añade una sesion al objeto 'Sesiones'.
 *        Devuelve un mensaje de error por pantalla si ya existia la sesión, en caso contrario, devuelve por pantalla el número total de problemas.
 */
void nueva_sesion(const string& id, const Sesiones& sessions);

/** @brief Añade un nuevo curso a la lista de cursos.
 *  @param courses objeto del tipo 'Cursos'.
 *  \pre existencia de un objeto 'Cursos', bien definido.
 *  \post Devuelve un mensaje de error por pantalla si el curso a insertar tiene problemas repetidos, en caso contrario, devuelve por pantalla el identificador del curso.
 */
void nuevo_curso(const Cursos& courses);

/** @brief Añade un usuario a la lista de usuarios.
 *  @param uid identificador de usuario ('int').
 *  @param users objeto del tipo 'Users'.
 *  \pre existencia de un objeto 'Users', bien definido.
 *  \post Devuelve un mensaje de error por pantalla si ya existe un usuario con el mismo identificador, en caso contrario, devuelve por pantalla el número de usuarios despues de añadirlo.
 */
void alta_usuario(const int& uid, const Usuario& users);

/** @brief Elimina un usuario de la lista de usuarios.
 *  @param uid identificador de usuario ('int').
 *  @param users objeto del tipo 'Users'.
 *  \pre existencia de un objeto 'Users', bien definido.
 *  \post Devuelve un mensaje de error por pantalla si no existe el usuario a eliminar, en caso contrario, devuelve por pantalla el número de usuarios despues de eliminar el usuario.
 */
void baja_usuario(const int& uid, const Usuario& users);

/** @brief Inscribe un usuario ('Usuario) en un curso ('Curso').
 *  @param uid identificador de usuario ('int').
 *  @param cid objeto del tipo ('Curso').
 *  \pre 
 *  \post Añade el usuario ('user') al curso ('course').
 *        Imprime por pantalla el número de usuarios inscritos en el curso tras añadir el usuario, si no se ha añadido, se imprime un mensaje de error (uid no encontrado o uid inscrito o course no encontrado)
 */
void inscribir_curso(const int& uid, const int& cid);

/** @brief Consulta el curso al que pertenece un usuario.
 *  @param uid identificador de usuario ('int').
 *  \post Imprime por pantalla el curso ('cid') al que pertenece el usuario, si no pertenece a ningún curso se imprime un error.
 */
void curso_usuario(const int& uid);

/** @brief Busca en un curso la sesión que contenga el problema buscado.
 *  @param cid identificador de curso ('int').
 *  @param pid identificador de problema ('string')
 *  \post Imprime el identificador de la sesión en pantalla si se ha encontrado, en caso opuesto, se imprime un error.
 */
void sesion_problema();

/**
 * 
 */




#endif