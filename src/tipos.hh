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
    int total;      //!< Número total de envíos.
    int accepted;   //!< Problemas aceptados (envios correctos)
    int rejected;   //!< Problemas rechazados (envíos incorrectos).

    /** @brief Constructor por defecto de la estructura que inicializa todas las variables a cero.
     *  \pre true
     *  \post Todas las variables son inicializadas a cero.
     */
    Attempts();

    /** @brief Actualiza los datos de todas las variables de la clase frente a un envío. (correcto o no).
     *  @param isCorrect variable que indica si el envío es cierto o falso.
     *  \pre true
     *  \post Se actualizan las variables de la estructura de acuerdo con el formato establecido.
     *  @return bool: true si el parámetro es cierto, false si el parámetro es falso.
     */
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

int binary_search_LH (const problemid& item, const vector<BinTree<ProblemData>>& myVect, int vectSize);

int insertion_sort_LH (const ProblemData& problemData, vector<ProblemData>& myVect, int& vectSize);

int insertion_sort_LH (const BinTree<ProblemData>& problemData, vector<BinTree<ProblemData>>& myVect, int& vectSize);

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

    void begin_iterator(vector<problemid>::const_iterator& inp) const
    {  
        inp = classVector.begin();
    }

    void end_iterator(vector<problemid>::const_iterator& inp) const
    {
        inp = classVector.end();
    }

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



struct TreeNode
{
    BinTree<problemid> root;

    TreeNode()
    {
        
    }

    TreeNode(BinTree<problemid>& problemTree)
    {
        root = problemTree; 
    }


    // TreeNode(const problemid left, const problemid& right)
    // {
        // BinTree
    // }
};

#endif
