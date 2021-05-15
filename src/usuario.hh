/** @file usuario.hh
 *  @brief Especificación de la clase 'Usuario'.
 */

#ifndef USER_HH
#define USER_HH

#include "coursemanager.hh"

using namespace std;

/** @typedef userid 
 *  @brief Idenfificador de 'Usuario'.
*/
typedef string userid;

/** @class Usuario
 *  @brief Almacena la información de un usuario y facilita su gestión.
 * 
 *  Gestiona toda la información relevante de un usuario:
 *      - Identificador del usuario.
 *      - Estado del usuario (incrito/no inscrito)
 *      - Información sobre los cursos que ha realizado/está realizando.
 *  Las operaciones que se pueden realizar sobre un usuario son las siguientes:
 *      - Solicitar identificador de usuario.
 *      - Solicitar el estado de inscripción a un curso.
 *      - Solicitar identificador del curso al que está inscrito.
 *      - Inscribir al usuario en un curso.
 *      - Desincribir al usuario de un curso.
 *      - Realizar un envio/actualizacion de problema.
 *      - Imprimir problemas solucionados/ problemas disponibles a resolver.
 */
class Usuario
{
private:
    userid uid;                     //!< Identificador del usuario.
    bool isNull;                    //!< Determina si el usuario está "determinado", es decir, sus elementos estan todos inicializados.
    bool isInscribed;               //!< Determina si el usuario está inscrito en un 'Curso'.
    CourseManager courseManager;    //!< Objeto que gestiona toda la información de los 'Cursos' del usuario.

public:

    /** @brief Constructor por defecto de la clase.
     *  \pre true.
     *  \post Todas las variables son inicializadas excepto el identificador de usuario ('uid').
     */ 
    Usuario();

    /** @brief Constructor sobrecargado de la clase.
     *  @param uid identificador de usuario ('userid').
     *  \pre true.
     *  \post Todas las variables de la clase son inicializadas y el identificador de usuario es el parámetro.
     */ 
    Usuario(const userid& uid);

    /** @brief Función que indica si el usuario está inscrito en un curso.
     *  \pre true.
     *  \post El usuario mantiene el estado que tenia anteriormente.
     *  @return 'bool': 'true' si el usuario está inscrito y 'false' si no lo está.
     */
    bool is_inscribed() const;

    /** @brief Consultor del estado del usuario.
     *  \pre 'true'.
     *  \post 'true'.
     *  @return 'bool':
     */
    bool is_null() const;

    /** @brief Función que indica el identificador del curso al que está inscrito el usuario.
     *  \pre El usuario debe estar inscrito en un curso.
     *  \post El usuario mantiene el estado que tenia anteriormente.
     *  @return 'courseid': devuelve el identificador del curso al que está inscrito el usuario.
     */
    courseid inscribed_course_id() const;

    /** @brief Inscribe al usuario en un curso.
     *  @param course objeto de tipo 'Curso'.
     *  @param sessions objeto del tipo 'Sesiones'.
     *  \pre El usuario debe tener identificador. El curso al que se quiere inscribir debe existir en el objeto 'Curso' y todas sus sesiones 
     *       deben pertenecer al conjunto de sesiones del objeto 'Sesiones' proporcionado por los parámetros.
     *  \post Si el usuario no está inscrito en ningún curso se le inscribe al parámetro de la función y se devuelve ('true'), 
     *        en caso opuesto, no se modifica la inscripción y se devuelve ('false').
     *  @return bool: 'true' si se ha inscrito al usuario correctamente, 'false' si el usuario ya estaba inscrito en un curso.
     */
    bool inscribe(Curso& course, Sesiones& sessions);

    /** @brief 
     *  @param courses 
     *  \pre true.
     *  \post El usuario deja de estar inscrito en el 'Curso'.
     *  @return 'void'.
     */
    void force_uninscribe(Cursos& courses);

    /** @brief Función que actualiza el conjunto de problemas de acuerdo con las reglas establecidas previamente.
     *  \pre El usuario está inscrito y el problema a solucionar no ha sido solucionado previamente y existe en el curso.
     *  \post Se actualiza la estructura 'currentCourse' y la estructura 'allCourses'. Se actualiza el estado del curso en el que está inscrito el usuario
     *  @return bool: 'true' si el curso se ha completado, 'false' si no ha sido completado.
     */
    bool update_problem(const problemid& pid, const bool& isSolved, Cursos& courses);

    /** @brief Función que sirve para "visualizar" los problemas que tiene el usuario disponibles a solucionar.
     *  @param problemVect objeto que contendrá todos los problemas disponibles (que cumple todos los requisitos) a solucionar por el usuario. 
     *  \pre true.
     *  \post El vector tiene tamaño superior o igual al inicial. Si el return es diferente de -1, el vector estará ordenado crecientemente, si el return es -1,
     *        el vector no se habrá modificado.
     *  @return int: '-1' si el usuario no está inscrito en ningun curso. El tamaño del vector del parámetro tras la ejecución en cualquier otro caso.
     */
    int available_problems() const;

    /** @brief Función que imprime por pantalla todos los cursos solucionados por un usuario.
     *  \pre El usuario debe tener identificador.
     *  \post No se realizan modificaciones en ningún objeto.
     *  @return int: número de problemas resueltos.
     */
    int print_all_time_solved_problems();

    /** @brief Imprime por pantalla los problemas disponibles del usuario.
     *  @return 'void'.
     */
    void print_available_problems() const;

    /** @brief Imprime por pantalla información sobre el usuario
     *  \pre true.
     *  \post Se imprime por pantalla la infomación del problema en este formato:
     *        uid(intentos totales, intentos exitosos, problemas intentados (número), courseid)
     *  @return void.
     */
    void write() const;

};
#endif
