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
    int unique;

    Attempts()
    {
        accepted = 0;
        total = 0;
        rejected = 0;
        unique = 0;
    }
};

/** @struct ProblemData
 *  @brief Almacena información genérica sobre un 'Problema'.
 */
struct ProblemData
{
    Attempts attempts;
    problemid pid;
    bool solved;

    ProblemData()
    {
        solved = false;
    }

    ProblemData(const problemid& pid)
    {
        this->pid = pid;
        solved = false;
    }
};

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

    // sortedVector(vector<T>& inpVect)
    // {
    //     sort(inpVect.begin(), inpVect.end());
    //     classVectorSize = inpVect.size();
    //     classVector = inpVect; // Mirar de optimizar
    // }

    template<typename U> sortedVector& operator=(const sortedVector<U>& inpVect)
    {
        classVector = inpVect;
        classVectorSize = inpVect.size();
        return *this;
    }

    

    T& operator[] (const int& index)
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
            classVector[i-1] = classVector[i];
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
    courseid identifier;
    Attempts totalAttempts;
    //vector<pair<sessionid, BinTree<pair<bool, problemid>>>> sessions; 
    vector<ProblemData> solvedProblems;
    //vector<ProblemData> availableProblems;
    int num_problemTree;
    vector<BinTree<ProblemData>> problemTreeVector;

    UserCourseData()
    {
        num_problemTree = 0;
        problemTreeVector = vector<BinTree<ProblemData>>(num_problemTree);
    }

    UserCourseData(const courseid& cid)
    {
        identifier = cid;
        num_problemTree = 0;
        problemTreeVector = vector<BinTree<ProblemData>>(num_problemTree);
    }
};

/** @struct UserCoursesData
 *  @brief Almacena información genérica sobre todos los 'Curso' que ha cursado un 'Usuario'.
 */
struct UserCoursesData
{
    Attempts attempts;
    vector<ProblemData> coursesVect; /*Ordenado en orden creciente*/
    int sizeCoursesVect;

    UserCoursesData()
    {
        sizeCoursesVect = 0;
        coursesVect = vector<ProblemData>(sizeCoursesVect);
    }
};

#endif