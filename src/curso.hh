/** @file curso.hh
 *  @brief Especificación de la clase 'Curso'.
 */

#ifndef COURSE_HH
#define COURSE_HH

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include "tipos.hh"
#include "sesiones.hh"
#include "problemas.hh"

using namespace std;

// N > 0, Sin repeticiones, 

typedef vector<sessionid> CourseSessionVector; 

/** @class Curso
 *  @brief Almacena la información de un curso y facilita su gestión.
 */

class Curso
{
private:
    int total;                          //!< Número de sesiones que tiene el curso.
    courseid cid;                       //!< Identificador del curso.
    CourseSessionVector sessionVector;  //!< Vector de sesiones del curso, contiene 'total' elementos.   
    bool valid;

    /** @struct UserData
     *  @brief Estructura que almacena información general sobre los usuarios que se han inscrito al curso.
     */
    struct UserData
    {
        int inscribed_users;            //!< Usuarios inscritos actualmente en el curso.
        int alltime_users;              //!< Usuarios que han completado el curso.

        /** @brief Constructor por defecto de la estructura.
         *  \pre true.
         *  \post Todas las variables son inicializadas a cero.
         */
        UserData();
    };

    UserData userdata;                  //!< Objeto del tipo 'UserData'

    bool initializedHintMap;
    map<problemid, int> hintMap; 
public:

    /** @brief Constructor por defecto de la clase.
     *  \pre true.
     *  \post Todas las variables son inicializadas excepto el identificador del curso ('courseid').
     */ 
    Curso();

    /** @brief Constructor sobrecargado de la clase.
     *  @param cid identificador de curso ('courseid').
     *  \pre true.
     *  \post Todas las variables de la clase son inicializadas y el identificador del curso es el parámetro.
     */ 
    Curso(const courseid& cid);

    /** @brief Modifica o inicializa el cid.
     *  @param cid identificador de curso ('courseid').
     *  \pre true.
     *  \post El this->cid se modifica por cid.
     *  @return bool: true.
     */
    bool set_cid(const courseid& cid);

    /** @brief Inscribe a un usuario en un curso.
     *  \pre true.
     *  \post Se aumenta (en uno) el número de usuarios inscritos en el curso.
     *  @return true
     */
    bool inscribe_user(); // const userid& uid

    /** @brief Desincribe a un usuario en un curso.
     *  \pre true.
     *  \post Se disminuye (en uno) el número de usuarios inscritos en el curso.
     *  @return true
     */    
    bool uninscribe_user(); // const userid& uid

    bool initialized_hintMap() const;

    /** @brief Función que indica el número de usuarios inscritos en el curso.
     *  \pre true.
     *  \post No se modifica ningún objeto de la clase.
     *  @return int: número de usuarios inscritos en el curso. (int >= 0).
     */    
    int inscribed_users() const;

    int vector_session_position_of_problem(const problemid& pid) const;

    /**
     * @brief 
     * 
     */
    int get_number_of_sessions() const;
    /**
     * @brief Función que actualiza el estado de los problemas del curso resueltos por un usuario.
     * @param pid identificador de problema que ha resuelto el usuario. Tipo 'problemid'.
     * @param isInscribed si el usuario está inscrito o no en el curso.
     * \pre El usuario estaba (o está) inscrito en el curso.
     * \post Se actualiza el registro de problemas del curso en función de si el usuario ha solucionado el problema o no.
     */
    void update_problem (const bool& isInscribed);

    /** @brief Asigna los iteradores del vector 'sessionVector' a los parámetros.
     *  @param beginIterator iterador del inicio del vector 'sessionVector'. Tipo 'CourseSessionVector::const_iterator'.
     *  @param endIterator iterador del final del vector 'sessionVector'. Tipo 'CourseSessionVector::const_iterator'.
     *  \pre true.
     *  \post No se modifica ningún objeto de la clase.
     *  @return int: número total de elementos 
     */
    int get_iterators(CourseSessionVector::const_iterator& beginIterator, CourseSessionVector::const_iterator& endIterator) const;

    /** @brief Verifica que el curso sea válido de acuerdo con el objeto 'Sesiones'.
     *  @param sessions objeto del tipo 'Sesiones' que se utilizará para verificar si el 'Curso' es válido.
     *  \pre EL parámetro 'sessions' no está incializado, el curso contiene sesiones. 
     *       Todas las sesiones del curso existen en el objeto 'Sesiones' (son válidas).
     *  \post No se modifica ningún objeto de la clase.
     *  @return bool: true si el 'Curso' es válido y false si no lo es.
     */
    bool is_valid_course(const Sesiones& sessions);

    /** @brief Imprime por pantalla información sobre el curso
     *  \pre true.
     *  \post Se imprime por pantalla la infomación del curso en este formato:
     *        cid total_users inscribed_users total (vect[0..total - 1])
     *  @return void.
     */
    void write() const;

    bool read_and_check();

    /** @brief Almacena la infomración de un curso por el 'stdin'
     *  \pre El formato de entrada 'stdin' ha de ser correcto, primero el número total de sesiones (N>0) y después las N sesiones.
     *  \post Las sesiones estaran definidas en el vector. El único parametro que no se modifica es el 'courseid'.
     *  @return void.
     */
    void read();

    void read(const Sesiones& sessions);
};

#endif
