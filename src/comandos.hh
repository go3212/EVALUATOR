#ifndef COMMANDS_HH
#define COMMANDS_HH

#include <iostream>
#include <string>
#include "problemas.hh"
#include "sesiones.hh"
#include "cursos.hh"
#include "usuarios.hh"

using namespace std;

/** @class Comandos
 *  @brief Contiene funciones para gestionar los 'Cursos', 'Usuarios' y 'Problemas'.
 */
class Comandos
{
private:
    Usuarios users;
    Cursos courses;
    Problemas problems;
    Sesiones sessions;

    map<command, int> commandsMap;

    /** @brief Funcion que inicializa todos los valores del mapa y asigna el número de comandos.
     *  \post El mapa contiene todos los valores de los comandos.
     */
    void set_default_commandsMap();
    
public:
    /** @brief Constructor que incicializa los usuarios, cursos y problemas.
     *  \pre En la entrada debe de estar toda la información a inicializar sobre los usuarios, cursos y problemas.
     *  \post Se inicializan los usuarios, cursos y problemas.
     */
    Comandos(Usuarios& users, Cursos& courses, Problemas& problems, Sesiones& sessions);

    /** @brief Ejecuta la consola de comandos.
     *  \post Si los parámetros implícitos no están definidos devuelve false, a modo de error.
     */
    bool run();

    bool run_time_mode();

    /** @brief Añade un nuevo problema a la lista de problemas.
     *  @param pid identificador del problema ('problemid').
     *  @param problems objeto de tipo 'Problemas'.
     *  \pre existencia de un objeto 'Problemas'.
     *  \post añade un problema al objeto 'Problemas'. 
     *        Devuelve un mensaje de error por pantalla si ya existia el problema, en caso contrario, devuelve por pantalla el número total de problemas.
     */
    void nuevo_problema(const problemid& pid);

    /** @brief Añade una nueva sesión a la lista de sesiones.
     *  @param sid identificador de la sesión ('sessionid').
     *  \pre existencia de un objeto 'Sesiones', con problemas no repetidos.
     *  \post añade una sesion al objeto 'Sesiones'.
     *        Devuelve un mensaje de error por pantalla si ya existia la sesión, en caso contrario, devuelve por pantalla el número total de problemas.
     */
    void nueva_sesion(const sessionid& sid);

    /** @brief Añade un nuevo curso a la lista de cursos.
     *  \pre existencia de un objeto 'Cursos', bien definido.
     *  \post Devuelve un mensaje de error por pantalla si el curso a insertar tiene problemas repetidos, en caso contrario, devuelve por pantalla el identificador del curso.
     */
    void nuevo_curso();

    /** @brief Añade un usuario a la lista de usuarios.
     *  @param uid identificador de usuario ('userid').
     *  \pre existencia de un objeto 'Users', bien definido.
     *  \post Devuelve un mensaje de error por pantalla si ya existe un usuario con el mismo identificador, en caso contrario, devuelve por pantalla el número de usuarios despues de añadirlo.
     */
    void alta_usuario(const userid& uid);

    /** @brief Elimina un usuario de la lista de usuarios.
     *  @param uid identificador de usuario ('userid').
     *  \pre existencia de un objeto 'Users', bien definido.
     *  \post Devuelve un mensaje de error por pantalla si no existe el usuario a eliminar, en caso contrario, devuelve por pantalla el número de usuarios despues de eliminar el usuario.
     */
    void baja_usuario(const userid& uid);

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

    /** @brief Función que imprime por pantalla información sobre los problemas.
     *  \post Se imprime por pantalla los envios totales a cada problema asi como los envios exitosos. Además se muestra el ratio (totales+1)/(enviados+1). Los problemas
     *        se muestran en orden creciente por dicho ratio, en caso de empate, por orden creciente de identificador.
     */
    void listar_problemas();

    /** @brief Función que imprime por pantalla información sobre un problema.
     *  @param pid identificador de problema ('problemid').
     *  \post Se imprime por pantalla los envios totales asi como los envios exitosos. Además se muestra el ratio (totales+1)/(enviados+1). 
     *        Si el problema no existe, se muestra un error por pantalla.
     */
    void escribir_problema(const problemid& pid);

    /** @brief Función que imprime por pantalla todas las sesiones de la plataforma con su respectiva información. 
     *  \post Se listan por pantalla todas las sesiones ordenadas crecientemente según su identificador. Para cada sesión se muestra el número de problemas
     *        que la forman y los identificadores de los problemas, siguiendo su estructura de requisitos en postorden.
     */
    void listar_sesiones();

    /** @brief Función que imprime por pantalla la información de una sesión.
     *  @param sid identificador de sesión ('sid').
     *  \post Se muestra el número de problemas que la forman y los identificadores de los problemas, siguiendo su estructura de requisitos en postorden.
     *        Si no existe la sesión en la plataforma se muestra un mensaje de error.
     */
    void escribir_sesion(const sessionid& sid);

    /** @brief Función que imprime por pantalla todos los cursos de la plataforma con su respectiva información. 
     *  \post Se listan por pantalla todos los cursos ordenados crecientemente según su identificador. Para cada curso se muestra el número de usuarios que han accedido
     *      , los usuarios actuales, el numero de sesiones que tiene el curso y sus identificadores, todo en orden cronologico.
     */
    void listar_cursos();

    /** @brief Función que imprime por pantalla la información de un curso.
     *  @param cid identificador de curso ('courseid').
     *  \post Se muestra el número de usuarios que han accedido, los usuarios actuales, el numero de sesiones que tiene el curso y sus identificadores,
     *        todo en orden cronologico. En caso de que no exista el curso se muestra un mensaje de error.
     */
    void escribir_curso(const courseid& cid);

    /** @brief Función que imprime por pantalla todos los usuarios de la plataforma con su respectiva información. 
     *  \post Se listan los usuarios registrados actualmente en la plataforma, ordenados crecientemente por su nombre y mostrando, para cada usuario, cuántos envios
     *        en total ha realizado, cuántos problemas ha resuelto satisfactoriamente, cuántos problemas ha intentado resolver (al menos ha hecho un envio), y el identificador
     *        del curso en el que está inscrito o un cero si no está inscrito en ninguno.
     */
    void listar_usuarios();

    /** @brief Función que imprime por pantalla la información de un usuario.
     *  @param uid identificador de usuario ('userid').
     *  \post Para el usuario en cuestion se imprime, cuántos envios
     *        en total ha realizado, cuántos problemas ha resuelto satisfactoriamente, cuántos problemas ha intentado resolver (al menos ha hecho un envio), y el identificador
     *        del curso en el que está inscrito o un cero si no está inscrito en ninguno.
     */
    void escribir_usuario(const userid& uid);
};
#endif