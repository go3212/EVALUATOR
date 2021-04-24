/** @file curso.hh
 *  @brief Especificación de la clase 'Curso'.
 */

#ifndef COURSE_HH
#define COURSE_HH

#include <iostream>
#include <vector>
#include <string>
#include <set>
#include "tipos.hh"
#include "sesiones.hh"

using namespace std;

// N > 0, Sin repeticiones, 

typedef vector<sessionid> CourseSessionVector; 

/** @class Curso
 *  @brief Almacena la información de un curso y facilita su gestión.
 */

class Curso
{
private:
    int total;
    courseid cid;
    CourseSessionVector sessionVector;

    struct UserData
    {
        int inscribed_users;
        int alltime_users;

        UserData()
        {
            inscribed_users = 0;
            alltime_users = 0;
        }
    };

    UserData userdata;

public:

    /** @brief Overloaded default class null constructor.
     *  \post Null course id ('id'). All other private variables are also undefined.
     */ 
    Curso();

    /** @brief Overloaded class constructor.
     *  \post Sets the course id ('this->cid') to the constructor parameter ('cid'). All other private variables are left undefined.
     */ 
    Curso(const courseid& cid);

    /** @brief Modifica o inicializa el cid.
     *  @param cid identificador de curso ('courseid').
     *  \post El this->cid se modifica por cid.
     */
    const bool set_cid(const courseid& cid);

    /** @brief Asigna los iteradores del vector de identificadores de sesiones a los parámetros
     * 
     */
    const void get_iterators(CourseSessionVector::const_iterator& beginIterator, CourseSessionVector::const_iterator& endIterator) const;

    /** @brief Verifica que el conjunto de sesiones sea válido.
     * 
     */
    const bool is_valid_course(const Sesiones& sessions);

    const int inscribed_users() const;

    const bool inscribe_user(const userid& uid);

    /** @brief Imprime por pantalla información sobre el curso
     *  \post Se imprime por pantalla la infomación del curso en este formato:
     *        cid total_users inscribed_users total (vect[0..total - 1])
     */
    const void write() const;

    /** @brief Almacena la infomración de un curso por el 'stdin'
     *  \pre El formato de entrada 'stdin' ha de ser correcto, primero el número total de sesiones (N>0) y después las N sesiones.
     *  \post Las sesiones estaran definidas en el vector. El único parametro no definido será el 'courseid'.
     */
    const void read();
};

#endif