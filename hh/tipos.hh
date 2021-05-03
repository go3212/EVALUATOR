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
        total = 0;
        accepted = 0;
        rejected = 0;
    }

    bool update_attempts (const bool& isCorrect)
    {
        total += 1;
        if (isCorrect) accepted += 1;
        else rejected += 1;
        return isCorrect;
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

    bool solve(const bool& isSolved)
    {
        solved = isSolved;
        attempts.update_attempts(isSolved);
        return solved;
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

    // sortedVector& operator=(const sortedVector<problemid>& inpVect)
    // {
    //     classVector = inpVect;
    //     classVectorSize = inpVect.size();
    //     sort(classVector.begin(), classVector.end());
    //     return *this;
    // }

    T& operator[] (const int& index)
    {
        return classVector[index];
    };

    int find(const T& classtype) const
    {
        //sort(classVector.begin(), classVector.end());
        // for (int i = 0; i < classVectorSize; ++i)
        // {
        //     cout << classVector[i] << ' ';
        // }
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

const int binary_search_LH (const problemid& item, const vector<ProblemData>& myVect, int vectSize);

int insertion_sort_LH (const ProblemData& problemData, vector<ProblemData>& myVect, int& vectSize);

/** @struct UserCourseData
 *  @brief Almacena información genérica sobre 'Curso' que cursa un 'Usuario'.
 */
struct UserCourseData
{
    courseid identifier;
    Attempts totalAttempts;
    int num_problems;
    vector<ProblemData> solvedProblems;
    int solvedProblemsSize;
    //vector<pair<sessionid, BinTree<pair<bool, problemid>>>> sessions; 
    //vector<ProblemData> availableProblems;
    int num_problemTree;
    vector<BinTree<ProblemData>> problemTreeVector;

    UserCourseData()
    {
        num_problemTree = 0;
        num_problems = 0;
        solvedProblemsSize = 0;
        problemTreeVector = vector<BinTree<ProblemData>>(num_problemTree);
        solvedProblems = vector<ProblemData>(0);
    }

    UserCourseData(const courseid& cid)
    {
        identifier = cid;
        num_problemTree = 0;
        num_problems = 0;
        solvedProblemsSize = 0;
        problemTreeVector = vector<BinTree<ProblemData>>(num_problemTree);
        solvedProblems = vector<ProblemData>(0);
    }

    int notsolved_problems ()
    {
        return num_problems - solvedProblemsSize;
    }

    bool update_attempts (const ProblemData& problemData, const bool& isSolved)
    {
        totalAttempts.update_attempts(isSolved);
        if (isSolved) insertion_sort_LH (problemData, solvedProblems, solvedProblemsSize);
        return isSolved;
    }
};

/** @struct UserCoursesData
 *  @brief Almacena información genérica sobre todos los 'Curso' que ha cursado un 'Usuario'.
 */
struct UserCoursesData
{
    Attempts attempts;
    vector<ProblemData> coursesVect; /*Ordenado en orden creciente por identificador de problema*/
    vector<ProblemData> attemptedProblemsVect; //<! Ordenado crecientemente.
    int unique_attempts;
    int sizeCoursesVect;
    int sizeAttemptedProblemsVect;

    UserCoursesData()
    {
        attemptedProblemsVect = vector<ProblemData>(0);
        coursesVect = vector<ProblemData>(0);
        sizeCoursesVect = 0;
        sizeAttemptedProblemsVect = 0;
        unique_attempts = 0;
    }

    bool insert_attempted_problem(const ProblemData& problemData)
    {
        int i = binary_search_LH (problemData.pid, attemptedProblemsVect, sizeAttemptedProblemsVect);
        if (i != -1) return false;

        insertion_sort_LH(problemData, attemptedProblemsVect, sizeAttemptedProblemsVect);
        unique_attempts += 1;
        return true;
    }

    int insert_solved_problem (const ProblemData& problemData)
    {
        // Se asume que el problema no existe en el vector.
        coursesVect.push_back(problemData);
        ++sizeCoursesVect;
        int i = sizeCoursesVect - 1; 
        ProblemData temp;
        while(i > 0 && coursesVect[i - 1].pid > coursesVect[i].pid)
        {
            temp = coursesVect[i - 1];
            coursesVect[i - 1] = coursesVect[i];
            coursesVect[i] = temp;
            --i;
        }
        return i;
    }

    bool update_attempts (const ProblemData& problemData, const bool& isSolved)
    {
        int i = binary_search_LH (problemData.pid, attemptedProblemsVect, sizeAttemptedProblemsVect);
        attempts.update_attempts(isSolved);
        if (isSolved) insert_solved_problem (problemData);

        if (i == -1)
        {
            insertion_sort_LH (problemData, attemptedProblemsVect, sizeAttemptedProblemsVect);
            unique_attempts += 1;
        }
        return isSolved;
    }

    const int find (const problemid& pid)
    {
        int i = binary_search_LH (pid, coursesVect, sizeCoursesVect);
        if (i == -1) return -1;
        return i;
    }
};

#endif