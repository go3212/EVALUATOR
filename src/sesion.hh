/** @file sesion.hh
 *  @brief Especificación de la clase 'Sesion'.
 */

#ifndef SESION_HH
#define SESION_HH

#include <iostream>
#include <vector>
#include <string>
#include "tipos.hh"
#include "problema.hh"

using namespace std;


/** @typedef ProblemTree
 *  @brief Tipo de variable que almacena problemas de sesiones en forma de árbol binario.
 */
typedef BinTree<problemid> ProblemTree;
typedef sortedVector<problemid> ProblemVector;
typedef map<problemid, TreeNode> ProblemMapNode;

// N > 0, Sin repeticiones, 

/** @class Sesion
 *  @brief Almacena la información de una sesión y facilita su gestión.
 */

class Sesion
{
private:
    sessionid sid;                  //<! Identificador de sesión.
    bool hasSessionid;              //<! Variable 'bool' que indica si la sesión tiene identificador o no.
    int n_problems;                 //<! Número de problemas de la sesión.
    ProblemTree problemTree;        //<! Árbol binario de tipo 'ProblemTree' que almacena los problemas de la clase.
    ProblemVector problemVect;      //<! Vector ordenado crecientemente de tipo 'ProblemVector' que almacena los problemas de la clase.
    ProblemMapNode problemMap;
public:

    /** @brief Overloaded default class null constructor.
     *  \post Null session name. All other private variables are also undefined.
     */ 
    Sesion();

    /** @brief Overloaded class constructor.
     *  \pre La entrada tiene que tener la lista de problemas en preorden (árbol binario).
     *  \post Sets the session id ('this->sid') to the constructor parameter ('sid'). All other private <em>int</em> variables are set to zero.
     */ 
    Sesion(const sessionid& sid);

    void get_problemTree(ProblemTree& problemTree) const;

    void get_next_problem(const problemid& pid, TreeNode& treeNode) const;

    /** @brief Devuelve si la sesion tiene identificador.
     *  \post Devuelve 'true' si la sesión tiene identificador y 'false' si no lo tiene.
     */
    bool has_sessionid() const;

    bool has_problem(const problemid& pid) const;

    int get_problems_as_vector(ProblemVector& pidVector) const;

    int get_problems (ProblemVector& pidVector) const;

    sessionid session_id() const;
    
    int get_problems_iterator(vector<problemid>::const_iterator& beginIter, vector<problemid>::const_iterator& endIter) const;

    int get_number_of_problems() const;

    /** @brief Almacena la infomración de una sesión por el 'stdin'
     *  \pre La información a leer debe estar en un orden correcto.
     *  \post Se almacena el conjunto de problemas y se inicializa el id.
     */
    void read();

    /** @brief Escribe la información de una sesión en el 'stdout'.
     *  \pre La sesión debe tener identificador y conjunto de problemas.
     *  \post Se escribe el número de problemas, asi como sus identificadores.
     */
    void write() const;

    
};

/**
 * @brief Función que lee de la entrada un árbol binario de identificadores de problema en preorden.
 * @param myTree variable de tipo ProblemTree en la que se almacenará la raíz del árbol.
 * \pre En la entrada 'stdin' debe estar un conjunto de 'problemid que representan los nodos del árbol binario.
 *      Se lee en preorden y se considera el '0' como "nodo vacío", es decir, es el marcador de la lectura en preorden.
 * \post Se modifica la variable 'myTree' asignandole el árbol leido.
 * @return int: número de elementos que tiene el árbol binario.
 */
int read_BinTree(ProblemTree& myTree, ProblemMapNode& myMap);

/**
 * @brief Función que imprime un árbol binario de tipo PtoblemTree.
 * @param myTree variable de tipo 'ProblemTree'.
 * \pre El parámetro de entrada debe ser un árbol valido.
 * \post No se modifica ninguna variable.
 * @return void.
 */
void print_BinTree(const ProblemTree& myTree);

/**
 * @brief Función que inserta los elementos de un árbol binario en un vector ordenado crecientemente.
 * @param myVect vector de tipo 'ProblemVector' al que se le insertaran los nodos del árbol.
 * @param myTree árbol binario de tipo 'ProblemTree'.
 * @return void.
 */
void vectorize_BinTree(ProblemVector& myVect, const ProblemTree& myTree);

#endif