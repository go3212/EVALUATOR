#ifndef USERDATA_HH
#define USERDATA_HH

#include <iostream>
#include "tipos.hh"
#include "curso.hh"

/** @struct UserCoursesData
 *  @brief Almacena información genérica sobre todos los 'Curso' que ha cursado un 'Usuario'.
 */
struct UserCoursesData
{
    Attempts attempts;                       //!< Intentos totales a todos los problemas, resueltos o no.
    vector<ProblemData> coursesVect;         //!< Vector que almacena todos los problemas resueltos por el usuario (de todos los cursos). Ordenado crecientemente por 'ProblemData::pid'
    int unique_attempts;                     //!< Problemas a los que se ha realizado al menos un envío (solucionados y no solucionados).
    int sizeCoursesVect;                     //!< Tamaño del vector 'ProblemData::coursesVect', representa el número de problemas solucionados.
    int sizeAttemptedProblemsVect;           //!< Tamaño del vector 'ProblemData::attemptedProblemsVect', representa el número de problemas no solucionados pero que se han intentado.

    UserCoursesData();

    int insert_solved_problem (const ProblemData& problemData);

    bool update_attempts (ProblemData& problemData, const bool& isSolved);

    int find (const problemid& pid);
};

/** @brief Función que actualiza
 *
 */
bool update_tree_problem(const problemid& pid, ProblemData& problemData, const bool& solved, BinTree<ProblemData>& problemTree);


/** @struct UserCourseData
 *  @brief Almacena información genérica sobre 'Curso' que cursa un 'Usuario'.
 */
struct UserCourseData
{
    courseid identifier;                            //!< Identificador de curso ('courseid'). Representa el curso al que pertence la información.
    vector<Curso>::iterator courseIter; 
    vector<ProblemData> availableProblems;
    vector<BinTree<ProblemData>> problemTreeVector; //!< Árbol de problemas del curso, con su respectiva información. (Cada elemento del vector representa un árbol de problemas).
    int sizeAvailableProblems;
    int numProblems;                                //!< Número de problemas que tiene el curso. (Representa el tamaño máximo del vector 'solvedProblems')
    int solvedProblemsSize; s                        //!< Número de problemas solucionados por el usuario. (Representa el tamaño del vector 'solvedProblems')
    int sizeProblemTreeVector;                      //!< Número de sesiones que tiene el curso. (Repesenta el tamaño del vector 'problemTreeVector')

    /** @brief Constructor por defecto de la estructura.
     *  \pre true.
     *  \post Todos los valores son nulos (0 o vacío).
     */
    UserCourseData();

    /** @brief Constructor sobrecargado de la estructura.
     *  @param cid identificador de curso ('courseid').
     *  \pre true.
     *  \post Todos los valores son nulos (0 o vacío), excepto el 'identifier' que será el parámetro del constructor.
     */
    UserCourseData(const courseid& cid);

    /** @brief Functión que devuelve los problemas restantes por solucionar.
     *  \pre true.
     *  \post No modifica ninguna variable de la estructura.
     *  @return int: número de problemas no resueltos.
     */
    int notsolved_problems () const;

    /** @brief Función que actualiza el estado de un problema de un árbol de 'ProblemData'.
     *  @param pid identificador del problema a actualizar. Tipo 'problemid'.
     *  @param problemData objeto del tipo 'ProblemData' al que se le asignará los datos del problema a actualizar. (si se encuentra).
     *  @param solved estado que tendrá el problema cuando se actualice. (true si el problema se soluciona y false si no se soluciona). Tipo 'bool'. 
     *  @param problemTree árbol de 'ProblemData' a modificar.
     *  \pre true.
     *  \post se actualiza el árbol binario 'problemTree' y se almacena el valor del problema encontrado en problemData (si se encuentra).
     *  @return bool: true si se ha encontrado el problema en en árbol (y se ha actualizado), false si no se ha encontrado el problema (y por ende, no se ha actualizado).
     */
    bool update_tree_problem (const problemid& pid, ProblemData& problemData, const bool& solved, BinTree<ProblemData>& problemTree);

    /** @brief Función que marca los problemas solucionados previamente (en otros cursos) en el curso actual.
     *  @param userCoursesData objeto del tipo 'UserCoursesData' que contiene toda la información relevante de los cursos previos.
     *  \pre true.
     *  \post Se actualiza el vector de árboles binarios.
     *  @return void.
     */
    void fetch_solved_problems (UserCoursesData& userCoursesData);

    /** @brief Función con el propósito de actualizar el estado de un problema del curso.
     *  @param pid problema a actualizar. Tipo 'problemid'.
     *  @param isSolved estado que tendrá el problema cuando se actualice. (true si el problema se soluciona y false si no se soluciona). Tipo 'bool'. 
     *  \pre El objeto debe tener identificador y el problema debe existir en el árbol de problemas ('problemTree').
     *  \post Se actualizan todos los datos del problema a modificar.
     *  @return ProblemData: datos del problema despues de ser modificado.
     */
    void update_data (const problemid& pid, ProblemData& problemData, const bool& isSolved);
};

#endif