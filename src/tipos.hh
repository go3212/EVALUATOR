/** @file tipos.hh
 *  @brief Archivo que contiene todos los tipos de variable diferentes utilizados en la practica.
 */

#ifndef TIPOS_HH
#define TIPOS_HH

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "BinTree.hh"

using namespace std;

/* TIPOS DE VARIABLES/OBJETOS */

/** @typedef sessionid
 *  @brief Idenfificador de 'Sesión'.
 */
typedef string sessionid;

/** @typedef userid 
 *  @brief Idenfificador de 'Usuario'.
*/
typedef string userid;

/** @typedef courseid 
 *  @brief Identificador de 'Curso'.
*/
typedef int courseid;

/** \typedef courseid 
 *  @brief Identificador de 'Problema'.
*/
typedef string problemid;

/** \typedef command
 *  @brief Identificador de 'Comandos'.
*/
typedef string command;

/** @struct Attempts
 *  @brief Almacena información sobre los intentos realizados a un 'Problema'.
 *  \post Todos los tipos de intentos son inicializados a cero.
 */
struct Attempts
{
    int accepted;
    int total;
    int rejected;

    Attempts();

    bool update_attempts (const bool& isCorrect);
};


/** @struct ProblemData
 *  @brief Almacena información genérica sobre un 'Problema'.
 */
struct ProblemData
{
    Attempts attempts;
    problemid pid;
    bool solved;

    ProblemData();

    ProblemData(const problemid& pid);

    bool solve(const bool& isSolved);
};

int binary_search_LH (const problemid& item, const vector<ProblemData>& myVect, int vectSize);

int binary_search_LH (const problemid& item, const vector<problemid>& myVect, int vectSize);

int insertion_sort_LH (const ProblemData& problemData, vector<ProblemData>& myVect, int& vectSize);

int insertion_sort_LH (const problemid& problemData, vector<problemid>& myVect, int& vectSize);

template <typename T> class sortedVector
{
private:
    vector<T> classVector;
    int classVectorSize;  
public:
    sortedVector()
    {
        classVectorSize = 0;
    }

    sortedVector(int size)
    {
        classVector = vector<T>(size);
        classVectorSize = size;
    };

    template<typename U> sortedVector& operator=(const sortedVector<U>& inpVect)
    {
        classVector = inpVect;
        classVectorSize = inpVect.size();
        return *this;
    }

    const T& operator[] (const int& index) const
    {
        return classVector[index];
    };

    int find(const T& classtype) const
    {
        int left = 0, right = classVectorSize - 1, m;
        while (left <= right)
        {   
            m = (left+right)/2;
            if (classVector[m] < classtype) left = m + 1;
            else if (classVector[m] > classtype) right = m - 1;
            else return m;
        }
        return -1;
    }

    bool push_back(const T& classtype)
    {
        classVector.push_back(classtype);
        ++classVectorSize;
        int i = classVectorSize - 1; 
        T temp;
        while(i > 0 && classVector[i - 1] > classVector[i])
        {
            temp = classVector[i - 1];
            classVector[i - 1] = classVector[i];
            classVector[i] = temp;
            --i;
        }
        return true;
    }

    int size() const
    {
        return classVectorSize;
    }
};

/** @struct UserCourseData
 *  @brief Almacena información genérica sobre 'Curso' que cursa un 'Usuario'.
 */
struct UserCourseData
{
    courseid identifier;                            //!< Identificador de curso ('courseid'). Representa el curso al que pertence la información.
    Attempts totalAttempts;                         //!< Intentos totales realizados al curso.
    vector<ProblemData> solvedProblems;             //!< Registro de problemas solucionados del curso, desde que se inscribió el usuario. Con su respectiva información ('ProblemData'). 
    vector<BinTree<ProblemData>> problemTreeVector; //!< Árbol de problemas del curso, con su respectiva información. (Cada elemento del vector representa un árbol de problemas).
    int numProblems;                                //!< Número de problemas que tiene el curso. (Representa el tamaño máximo del vector 'solvedProblems')
    int solvedProblemsSize;                         //!< Número de problemas solucionados por el usuario. (Representa el tamaño del vector 'solvedProblems')
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

    /** @brief Función con el propósito de actualizar el estado de un problema del curso.
     *  @param pid problema a actualizar. Tipo 'problemid'.
     *  @param isSolved estado que tendrá el problema cuando se actualice. (true si el problema se soluciona y false si no se soluciona). Tipo 'bool'. 
     *  \pre El objeto debe tener identificador y el problema debe existir en el árbol de problemas ('problemTree').
     *  \post Se actualizan todos los datos del problema a modificar.
     *  @return ProblemData: datos del problema despues de ser modificado.
     */
    ProblemData update_data (const problemid& pid, const bool& isSolved);
};

/** @struct UserCoursesData
 *  @brief Almacena información genérica sobre todos los 'Curso' que ha cursado un 'Usuario'.
 */
struct UserCoursesData
{
    Attempts attempts;
    vector<ProblemData> coursesVect; /*Ordenado en orden creciente por identificador de problema*/
    vector<problemid> attemptedProblemsVect; //<! Ordenado crecientemente.
    int unique_attempts;
    int sizeCoursesVect;
    int sizeAttemptedProblemsVect;

    UserCoursesData();

    // HACER UN REWORK COMPLETO A ESTA CLASE POR FAVOR
    bool insert_attempted_problem(const ProblemData& problemData);

    int insert_solved_problem (const ProblemData& problemData);

    bool update_attempts (const ProblemData& problemData, const bool& isSolved);

    int find (const problemid& pid);
};

/**
 * @brief Función que actualiza
 *
 */
bool update_tree_problem(const problemid& pid, ProblemData& problemData, const bool& solved, BinTree<ProblemData>& problemTree);

#endif
