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
 *  @param pid identificador del problema ('problemid').
 *  @param problems objeto de tipo 'Problemas'.
 *  \pre existencia de un objeto 'Problemas'.
 *  \post añade un problema al objeto 'Problemas'. 
 *        Devuelve un mensaje de error por pantalla si ya existia el problema, en caso contrario, devuelve por pantalla el número total de problemas.
 */
void nuevo_problema(const problemid& pid, const Problemas& problems);

/** @brief Añade una nueva sesión a la lista de sesiones.
 *  @param sid identificador de la sesión ('sessionid').
 *  @param sessions objeto del tipo 'Sesiones'.
 *  \pre existencia de un objeto 'Sesiones', con problemas no repetidos.
 *  \post añade una sesion al objeto 'Sesiones'.
 *        Devuelve un mensaje de error por pantalla si ya existia la sesión, en caso contrario, devuelve por pantalla el número total de problemas.
 */
void nueva_sesion(const sessionid& sid, const Sesiones& sessions);

/** @brief Añade un nuevo curso a la lista de cursos.
 *  @param courses objeto del tipo 'Cursos'.
 *  \pre existencia de un objeto 'Cursos', bien definido.
 *  \post Devuelve un mensaje de error por pantalla si el curso a insertar tiene problemas repetidos, en caso contrario, devuelve por pantalla el identificador del curso.
 */
void nuevo_curso(const Cursos& courses);

/** @brief Añade un usuario a la lista de usuarios.
 *  @param uid identificador de usuario ('userid').
 *  @param users objeto del tipo 'Users'.
 *  \pre existencia de un objeto 'Users', bien definido.
 *  \post Devuelve un mensaje de error por pantalla si ya existe un usuario con el mismo identificador, en caso contrario, devuelve por pantalla el número de usuarios despues de añadirlo.
 */
void alta_usuario(const userid& uid, const Usuario& users);

/** @brief Elimina un usuario de la lista de usuarios.
 *  @param uid identificador de usuario ('userid').
 *  @param users objeto del tipo 'Users'.
 *  \pre existencia de un objeto 'Users', bien definido.
 *  \post Devuelve un mensaje de error por pantalla si no existe el usuario a eliminar, en caso contrario, devuelve por pantalla el número de usuarios despues de eliminar el usuario.
 */
void baja_usuario(const userid& uid, const Usuario& users);

/** @brief Inscribe un usuario ('Usuario) en un curso ('Curso').
 *  @param uid identificador de usuario ('userid').
 *  @param cid objeto del tipo ('courseid').
 *  \post Añade el usuario ('user') al curso ('course').
 *        Imprime por pantalla el número de usuarios inscritos en el curso tras añadir el usuario, si no se ha añadido, se imprime un mensaje de error (uid no encontrado o uid inscrito o course no encontrado)
 */
void inscribir_curso(const userid& uid, const courseid& cid);

/** @brief Consulta el curso al que pertenece un usuario.
 *  @param uid identificador de usuario ('userid').
 *  \post Imprime por pantalla el curso ('cid') al que pertenece el usuario, si no pertenece a ningún curso se imprime un error.
 */
void curso_usuario(const userid& uid);

/** @brief Busca en un curso la sesión que contenga el problema buscado.
 *  @param cid identificador de curso ('courseid').
 *  @param pid identificador de problema ('problemid')
 *  \post Imprime el identificador de la sesión en pantalla si se ha encontrado, en caso opuesto, se imprime un error.
 */
void sesion_problema(const courseid& cid, const problemid& pid);

/** @brief Se listan los problemas resueltos por un usuario y más información.
 *  @param uid identificador de usuario ('userid').
 *  \post Se imprimen todos los problemas (de todos lo cursos que haya podido cursar el usuario) en orden ascendente por identificador. 
 *        Además se imprime el número de envios realizados por el usuario (envios>=1) a cada problema listado. Si el usuario no existe en la plataforma,
 *        se imprime un mensaje de error.
 */
void problemas_resueltos(const userid& uid);

/** @brief Se listan los problemas los problemas no solucionados (y que cumple los prerequisitos para solucionarlos) por un usuario en el curso al que está inscrito.
 *  @param uid identificador de usuario ('userid').
 *  \post Se listan los problemas en orden creciente por identificador. Además se imprime el número de envios totales a cada problema por el usuario (envios>=0).
 *        Si no existe el usuario o no está inscrito en ningún curso, se imprime un mensaje de error.
 */
void problemas_enviables(const userid& uid);

/** @brief Envia un intento de solución de problema de un usuario.
 *  @param uid identificador de usuario ('userid').
 *  @param pid identificador de problema ('problemid').
 *  @param solved marcador que indica si el problema ('pid') se ha solucionado ('bool').
 *  \pre Usuario registrado e inscirito en un curso donde aparece el problema ('pid') y el problema pertenece al conjunto de problemas solucionables por el usuario.
 *  \post Actualiza las estadísticas del objeto usuario ('Usuario') y del problema ('Problema'). Si el usuario, al completar el problema (solved = 1), completa el curso, se da de baja del curso.
 */
void envio(const userid& uid, const problemid& pid, const bool& solved);


#endif