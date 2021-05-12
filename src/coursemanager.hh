#ifndef COURSEMANAGER_HH
#define COURSEMANAGER_HH

#include "cursos.hh"

typedef map<problemid, ProblemData> ProblemDataMap;
typedef map<problemid, ProblemDataMap::const_iterator> ProblemDataIteratorMap;

/** @struct UserCoursesData
 *  @brief Almacena información genérica sobre todos los 'Curso' que ha cursado un 'Usuario'.
 */
class CourseManager
{
private:
    Attempts attempts;                           //!< Intentos generales a los problemas de los cursos.
    ProblemDataMap problemDataMap;               //!< Mapa que almacena los problemas a los que el usuario ha realizado al menos un envío.
    vector<pair<problemid, int>> solvedProblems; //!< Vector de problemas que almacena los problemas solucionados con sus intentos.
    int sizeSolvedProblems;                      //!< Tamaño del vector de problemas.
    int uniqueAttempts;                          //!< Tamaño del mapa de problemas.

    /** @struct UserCourseData
    *   @brief Almacena información genérica sobre 'Curso' que cursa un 'Usuario'.
    */
    struct CurrentCourse
    {
        courseid identifier;                                      //!< Identificador del curso inscrito, 0 si no está inscrito.
        vector<SessionMap::const_iterator> sessionProblemMapIter; //!< Vector de iteradores de las sesiones del curso al que está inscrito.
        int numSessions;                                          //!< Número de sesiones del curso al que está inscrito.                    
        int numProblems;                                          //!< Número de problemas del curso al que está inscrito.

        /** @brief Constructor por defecto de la clase.
         *  \pre true.
         *  \post Todos los parámetros implicitos son cero o no definidos.
         */
        CurrentCourse();

        /** @brief Constructor sobrecargado de la clase.
         *  \pre true.
         *  \post Todos los parámetros implicitos son inicializados correctamente.
         *  @param courseIter iterador al curso en el que se ha inscrito el usuario. 
         *  @param sessions conjunto total de sesiones.
         */
        CurrentCourse(const Curso& course, const Sesiones& sessions);
        
        /** @brief Consultor del número de problemas no solucionados de una sesión.
         *  \pre Parámetro sum inicializado.
         *  \post true.
         *  @param sum número de elementos no solucionados.
         *  @param problemDataMap mapa de problemas a los que se ha hecho al menos un envío.
         *  @param problemTree árbol que contiene todos los problemas de la sesión.
         *  @return 'void'.
         */
        void not_solved_problems(int& sum, const ProblemDataMap& problemDataMap, const ProblemTree& problemTree) const;
        
        /** @brief Consultor de los problemas disponibles de una sesión
         *  \pre Parámetro sum inicializado.
         *  \post true.
         *  @param problemDataMap mapa de problemas a los que se ha hecho al menos un envío.
         *  @param sum número de elementos no solucionados. 
         *  @param myVect vector donde se insertaran los identificadores de los problemas disponibles. 
         *  @param problemTree árbol que contiene todos los problemas de la sesión.
         *  @return 'void'.
         */
        void insert_available_problems(const ProblemDataMap& problemDataMap, int& sum, vector<pair<problemid, int>>& myVect, const ProblemTree& problemTree) const;
    };

    CurrentCourse currentCourse;    //!< Objeto que almacena los datos del curso al que está inscrito el usuario.

public:

    /** @brief Constructor por defecto de la clase.
     *  \pre true.
     *  \post true.
     */
    CourseManager();

    /** @brief Consultor del identificador al que está inscrito. 
     *  \pre true.
     *  \post true.
     *  @return 'courseid': 0 si el usuario no está inscrito en ningún curso, cualquier otra cosa si lo está. 
     */
    courseid current_course_id() const;

    /** @brief Inscribe al usuario en un curso.
     *  \pre Los parámetros de entrada deben estar relacionados y el usario no está inscrito en un curso.
     *  \post El usuario se inscribe en el curso.
     *  @param courseIter iterador del curso al que se desea inscribir el usuario.
     *  @param sessions conjunto de sesiones general.
     *  @return 'void'.
     */
    void inscribe(Curso& course, const Sesiones& sessions);

    /** @brief Consultor de si se ha terminado el curso o no.
     *  \pre true.
     *  \post true.
     *  @return 'bool': true si el curso se ha acabado y false si no se ha acabado.
     */
    bool course_finished() const;

    /** @brief Desinscribe al usuario del curso.
     *  \pre El usuario debe haber acabado el curso.
     *  \post Se desincribe al usuario del curso.
     *  @return 'bool': true si se ha desinscrito correctamente, false en caso contrario.
     * 
     *  La función no debe confundirse con force_uninscribe(). La diferencia entre estas dos es que la primera
     *  actualiza el número de usuarios que han cursado el curso correctamente y la segunda no. Ambas actualizan
     *  el número de usuarios del curso.
     */
    bool uninscribe(Cursos& courses);

    /** @brief Desinscribe al usuario del curso.
     *  \pre true.
     *  \post El usuario no estará inscrito en ningún curso.
     *  @return 'void'.
     * 
     *  La función no debe confundirse con force_uninscribe(). La diferencia entre estas dos es que la primera
     *  actualiza el número de usuarios que han cursado el curso correctamente y la segunda no. Ambas actualizan
     *  el número de usuarios del curso.
     */
    void force_uninscribe(Cursos& courses);

    /** @brief Realiza un envio a un problema del curso que cursa el usuario.
     *  \pre El usuario está inscrito en un curso.
     *  \post Se realiza el envio al problema.
     *  @param pid identificador del problema.
     *  @param status estado del problema despues de realizar el envío (true: solucionado,  false: no solucionado).
     *  @return 'void'.
     */
    void send_attempt(const problemid& pid, const bool& status);

    /** @brief Imprime por pantalla los problemas disponibles a solucionar.
     *  \pre true.
     *  \post true.
     *  @return 'void'.
     */
    void print_available_problems() const;

    /** @brief Imprime por pantalla los problemas solucionados con su respectiva información.
     *  \pre true.
     *  \post true.
     *  @return 'void'.
     */
    void print_solved_problems();

    /** @brief Imprime por pantalla la información general de los cursos cursados.
     *  \pre true.
     *  \post true.
     */
    void print_course_info() const
    {
        cout <<'(' << attempts.total;
        cout << ',' << attempts.accepted << ',' << uniqueAttempts << ',';
        cout << currentCourse.identifier << ')'; 
    }

};

#endif