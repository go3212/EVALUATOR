/** @file usuario.hh
 *  @brief Especificación de la clase 'Usuario'.
 */

#ifndef USER_HH
#define USER_HH

#include <iostream>
#include <vector>
#include <string>
#include "problema.hh"

typedef int userid;

using namespace std;

/** @struct ProblemData
 *  @brief Almacena el número de intentos (total) al problema, y su identificador. 
 */
struct ProblemData
{
    Attempts attempts;
    problemid pid;
};

/** @struct CourseData
 *  @brief Holds current course data, if inscribed.
 */
struct CourseData
{
    courseid identifier;
    Attempts total_attempts;
    vector<ProblemData> solved_problems;
    vector<ProblemData> available_problems;
};

/** @struct CourseData
 *  @brief Holds current course data, if inscribed.
 */
struct AllCoursesData
{
    Attempts attempts;
    vector<CourseData> course;
};

/** @class User
 *  @brief Holds data for a user: a username ('name') and a sequence of session identifiers ('sessions')
 */
class Usuario
{
private:
    userid id;
    bool has_userid;
    bool is_inscribed;
    CourseData current_course;
    AllCoursesData all_courses;

public:

    /** @brief Overloaded default class null constructor.
     *  \post Null user id ('uid'). All other private variables are also undefined.
     */ 
    Usuario();

    /** @brief Overloaded class constructor.
     *  @param uid identificador de usuario ('userid')
     *  \post Sets the user id ('this->id') to the constructor parameter ('uid'). All other private variables are left undefined.
     */ 
    Usuario(const userid& uid);

    /** @brief Inscribe al usuario en un curso.
     *  @param cid identificador del curso ('courseid').
     *  \pre El usuario debe tener 'uid' != NULL. El curso debe existir.
     *  \post Si el usuario no está inscrito en ningún curso se le inscribe al parámetro de la función y se devuelve ('true'), en caso opuesto, no se modifica la inscripción y se devuelve ('false').
     */
    bool inscribe(const courseid& cid);

    /** @brief Devuelve si el usuario está inscrito en un curso.
     *  \post Devuelve 'true' si el usuario está inscrito y 'false' si no lo está.
     */
    const bool is_inscribed() const;

    /** @brief Devuelve si el usuario tiene identificador
     *  \post Devuelve 'true' si el usuario tiene identificador y 'false' si no lo tiene.
     */
    const bool has_userid() const;

    /** @brief Devuelve la información de todos los cursos cursados por el usuario.
     *  \post Devuelve un puntero no modificable que contiene una estructura 'AllCourseData'. Devuelve NULL si el usuario no está inscrito en un curso.
     */
    const vector<AllCoursesData>& all_courses() const;

    /** @brief Devuelve la información del curso al que está inscrito el usuario.
     *  \post Devuelve un puntero no modificable que contiene una estructura 'CourseData'. Devuelve NULL si el usuario no está inscrito en un curso.
     */
    const vector<CourseData>& current_course() const;

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
};

#endif