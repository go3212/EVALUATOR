/** @file usuario.hh
 *  @brief Especificación de la clase 'Usuario'.
 */

#ifndef USER_HH
#define USER_HH

#include <iostream>
#include <vector>
#include <string>
#include "tipos.hh"
#include "problema.hh"

using namespace std;

/** @class Usuario
 *  @brief Almacena la información de un usuario y facilita su gestión.
 */
class Usuario
{
private:
    userid uid;
    bool hasUserid;
    bool isInscribed;
    UserCourseData currentCourse;
    UserCoursesData allCourses;

public:

    /** @brief Overloaded default class null constructor.
     *  \post Null user id ('uid'). All other private variables are also undefined.
     */ 
    Usuario();

    /** @brief Overloaded class constructor.
     *  @param uid identificador de usuario ('userid')
     *  \post Sets the user id ('this->uid') to the constructor parameter ('uid'). All other private variables are left undefined.
     */ 
    Usuario(const userid& uid);

    /** @brief Inscribe al usuario en un curso.
     *  @param cid identificador del curso ('courseid').
     *  \pre El usuario debe tener 'uid' != NULL. El curso debe existir.
     *  \post Si el usuario no está inscrito en ningún curso se le inscribe al parámetro de la función y se devuelve ('true'), en caso opuesto, no se modifica la inscripción y se devuelve ('false').
     */
    const bool inscribe(const courseid& cid);

    /** @brief Devuelve si el usuario está inscrito en un curso.
     *  \post Devuelve 'true' si el usuario está inscrito y 'false' si no lo está.
     */
    const bool is_inscribed() const;

    /** @brief Devuelve si el usuario tiene identificador
     *  \post Devuelve 'true' si el usuario tiene identificador y 'false' si no lo tiene.
     */
    const bool has_userid() const;

    const bool inscribed_course_id() const;

    /** @brief Devuelve la información de todos los cursos cursados por el usuario.
     *  \post Devuelve un puntero no modificable que contiene una estructura 'AllCourseData'. Devuelve NULL si el usuario no está inscrito en un curso.
     */
    const vector<UserCoursesData>& all_courses() const;

    /** @brief Devuelve la información del curso al que está inscrito el usuario.
     *  \post Devuelve un puntero no modificable que contiene una estructura 'UserCourseData'. Devuelve NULL si el usuario no está inscrito en un curso.
     */
    const vector<UserCourseData>& current_course() const;

    /** @brief Actualiza el estado del curso al enviar un problema.
     *  @param pid identificador de problema ('problemid').
     *  @param solved valor que indica si el problema ha sido solucionado correctamente o no ('bool').
     *  \post Actualiza el número de intentos y la lista de problemas disponibles para el usuario. Si no quedan más problemas a solucionar, se desinscribre al usuario del curso.
     *        Devuelve 'true' si se ha encontrado el problema en el curso y 'false' si no sse ha encontrado.
     */
    bool update_problems(const problemid& pid, const bool& solved);

    /** @brief Almacena la información de un usuario.
     *  \pre Los datos en 'stdin' deben estar ordenados correctamente: identificador ('userid').
     *  \post Se almacena un identificador en el usuario y se establece a 'true' el parámetro implícito ('has_userid').
     */
    void read();

    /** @brief Imprime por pantalla información sobre el usuario
     *  \post Se imprime por pantalla la infomación del problema en este formato:
     *        uid(intentos totales, intentos exitosos, problemas intentados (número), courseid)
     */
    const void write() const;
};

#endif