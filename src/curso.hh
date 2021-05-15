/** @file curso.hh
 *  @brief Especificación de la clase 'Curso'.
 */

#ifndef COURSE_HH
#define COURSE_HH

#include "sesiones.hh"

using namespace std;

/** @typedef courseid 
 *  @brief Identificador de 'Curso'.
 *  
 *  El 'courseid' es el identificador del 'Curso' al que representa. 
 *  Tiene algunas propiedades "simbólicas" respecto al 'Curso':
 *      1) Si tiene valor 0, representa que no le ha sido asignado un valor correcto.
 *      2) Si tiene valor >0, representa que el identificador es válido.
*/
typedef int courseid;

/** @typedef CourseSessionVector
 *  @brief Vector de identificadores de sesiones.
 * 
 *  El 'CourseSessionVector' es un vector de 'sessionid' que representa las sesiones que contiene el 'Curso' al que representa.
 */
typedef vector<sessionid> CourseSessionVector; 

/** @class Curso
 *  @brief Almacena la información de un curso y facilita su gestión.
 * 
 *  Gestiona la información sobre un curso:
 *      - Identificador de curso.
 *      - Número total de sesiones que contiene.
 *      - Vector de identificadores de sesiones que pertenecen al curso.
 *      - Datos sobre los usuarios (inscritos/que han cursado el curso).
 *  Se pueden realizar algunas operaciones:
 *      - Solicitar/re-asignar identificador.
 *      - Inscribir/desinscribir usuario.
 *      - Solicitar número total de sesiones.
 *      - Solicitar sesion a la que pertence un problema.
 *      - Escribir/leer sesion.
 *  Algunas operaciones requieren de precondiciones en los parámetros implícitos.
 */
class Curso
{
private:
    courseid cid;                       //!< Identificador del curso.
    int total;                          //!< Número de sesiones que tiene el curso.
    bool isNull;                        //!< Determina si el curso esta "determinado", es decir, sus elementos estan todos inicializados.
    CourseSessionVector sessionVector;  //!< Vector de sesiones del curso, contiene 'total' elementos.

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

    bool isHintMapInitialized;          //!< Determina si el 'hintMap' ha sido inicializado. Por defecto está en 'false' para cualquier constructor.
    map<problemid, sessionid> hintMap;  //!< Mapa que relaciona los problemas que contiene el 'Curso', con la sesión a la que pertenecen
                                        //!< Por defecto, no se inicializa su estado por si nunca se llega a utilizar, por lo que no puede ser utilizada. 
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

    /** @brief Consultor del identificador de sesión del curso
     *  \pre Curso no debe ser nulo.
     *  \post true.
     *  @return 'courseid': identificador de curso válido.
     */
    courseid get_cid() const;

    /** @brief Modifica o inicializa el cid.
     *  @param cid identificador de curso ('courseid').
     *  \pre true.
     *  \post El this->cid se modifica por cid.
     *  @return 'void'.
     */
    void set_cid(const courseid& cid);

    /** @brief Inscribe a un usuario en un curso.
     *  \pre Curso no debe ser nulo..
     *  \post Se aumenta (en uno) el número de usuarios inscritos en el curso.
     *  @return 'void'.
     */
    void inscribe_user(); // const userid& uid

    /** @brief Desincribe a un usuario del curso.
     *  \pre Curso no debe ser nulo, al menos un 'Usuario' en el curso.
     *  \post Se disminuye (en uno) el número de usuarios inscritos en el curso y se aumenta el número de usuarios que han cursado el curso.
     *  @return 'void'.
     * 
     *  La función actualiza los datos del curso cuando un 'Usuario' se ha desinscrito correctamente del curso, es decir,
     *  pasa de estar inscrito en el curso a formar parte de los 'Usuarios' que lo han cursado. 
     */    
    void uninscribe_user(); // const userid& uid

    /** @brief Fuerza la desincripción de un usuario en el curso.
     *  \pre Curso no debe ser nulo, al menos un 'Usuario' en el curso.
     *  \post Se disminuye (en uno) el número de usuarios inscritos en el curso.
     *  @return 'void'. 
     * 
     *  La función actualiza los datos del curso cuando un 'Usuario' se ha desinscrito forzosamente del curso, es decir,
     *  pasa de estar inscrito en el curso a formar parte de los 'Usuarios' que, por algún motivo, no lo han podido seguir cursando.
     *  Se considera que esos 'Usuarios' nunca han existido en la base de datos del curso (excepto sus intentos a los problemas). 
     */
    void force_uninscribe();

    /** @brief Consultor del estado del 'hintMap'.
     *  \pre Curso no debe ser nulo.
     *  \post true.
     *  @return 'bool': 'true' si el 'hintMap' está inicializado y 'false' si no lo está.
     */
    bool is_hintMap_initialized() const;

    /** @brief Consultor del estado del curso.
     *  \pre true.
     *  \post true.
     *  @return 'bool': 'true' si el curso es nulo y 'false' si no lo es.
     */
    bool is_null () const;

    /** @brief Inicializa el 'hintMap' desde un conjunto de 'Sesiones'.
     *  @param sessions conjunto de 'Sesiones'.
     *  \pre true.
     *  \post Se modifica el estado del 'hintMap'.
     *  @return 'bool': 'true' si se ha podido inicializar correctamente el 'hintMap' y 'false' en caso contrario.
     *
     *  Inicializa el 'hintMap' desde el conjunto de 'Sesiones', se considera que el 'hintMap' se ha inicializado correctamente si
     *  el curso no tiene ningún problema repetido.
     */ 
    bool initialize_hintMap(const Sesiones& sessions);

    /** @brief Función que indica el número de usuarios inscritos en el curso.
     *  \pre Curso no debe ser nulo.
     *  \post true.
     *  @return 'int': número de usuarios inscritos en el curso. ( >= 0).
     */    
    int inscribed_users() const;

    /** @brief Get the problem session object
     *  \pre El 'hintMap' debe estar inicializado, el curso no debe ser nulo.
     *  \post true.
     *  @param pid identificador del problema a buscar en el curso.
     *  @return 'sessionid': "0" si no se ha encontrado la sesión, un identificador válido en cualquier otro caso.
     */
    sessionid get_problem_session (const problemid& pid) const;

    /** @brief Consultor del número de 'Sesiones' que tiene el curso.
     *  \pre Curso no debe ser nulo.
     *  \post true.
     *  @return 'int': número de sesiones que tiene el curso (>= 0).
     */
    int get_number_of_sessions() const;

    /** @brief Asigna los iteradores del vector 'sessionVector' a los parámetros.
     *  @param beginIterator iterador del inicio del vector 'sessionVector'. Tipo 'CourseSessionVector::const_iterator'.
     *  @param endIterator iterador del final del vector 'sessionVector'. Tipo 'CourseSessionVector::const_iterator'.
     *  \pre Curso no debe ser nulo.
     *  \post 'true'.
     *  @return int: número total de elementos (>= 0).
     */
    int get_iterators(CourseSessionVector::const_iterator& beginIterator, CourseSessionVector::const_iterator& endIterator) const;

    /** @brief Imprime por pantalla información sobre el curso
     *  \pre true.
     *  \post Se imprime por pantalla la infomación del curso en este formato:
     *        cid total_users inscribed_users total (vect[0..total - 1])
     *  @return 'void'.
     */
    void write() const;

    /** @brief Almacena la infomración de un curso por el 'stdin'
     *  \pre El formato de entrada 'stdin' ha de ser correcto, primero el número total de sesiones (N>0) y después las N sesiones.
     *  \post Las sesiones estaran definidas en el vector. El único parametro que no se modifica es el 'courseid'.
     *  @return void.
     */
    void read();
};

#endif
