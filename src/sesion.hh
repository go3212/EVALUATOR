/** @file sesion.hh
 *  @brief Especificación de la clase 'Sesion'.
 */

#ifndef SESION_HH
#define SESION_HH

#include <vector>
#include <algorithm>
#include "BinTree.hh"
#include "problema.hh"

using namespace std;


/** @typedef sessionid
 *  @brief Idenfificador de 'Sesión'.
 */
typedef string sessionid;

/** @typedef ProblemTree
 *  @brief Tipo de variable que almacena problemas de sesiones en forma de árbol binario.
 */
typedef BinTree<problemid> ProblemTree;

/** @typedef ProblemVector
 *  @brief Tipo de variable que almacena problemas de sesiones en forma de vector de 'problemid'.
 */
typedef vector<problemid> ProblemVector;

/** @class Sesion
 *  @brief Almacena la información de una sesión y facilita su gestión.
 * 
 *  Gestiona toda la información relevante de una sesion:
 *      - Identificador de la sesión.
 *      - Número de problemas de sesión.
 *      - Problemas de la sesión en árbol binário por orden de requisitos.
 *      - Problemas de la sesión en un vector por orden lexicográfico creciente.
 *  Como la sesion en si representa información estática, las operaciones que se pueden realizar a cada sesion son:
 *      - Solicitar el identificador de la sesion.
 *      - Verificar si un problema pertenece a la sesion.
 *      - Solicitar número de problemas que contiene la sesion.
 *      - Solicitar el árbol de problemas de la sesion.
 *      - Solicitar el vector de problemas de la sesion.
 *  Hay algunas operaciones que se deben utilizar para comprobar si se ha podido obtener el problema solicitado, 
 *  si previamente no se conocia su existencia. No estan listadas.
 */

class Sesion
{
private:
    sessionid sid;                  //<! Identificador de sesión.
    bool isNull;                    //<! Variable 'bool' que indica si la sesión tiene identificador o no.
    int numProblems;                //<! Número de problemas de la sesión.
    ProblemTree problemTree;        //<! Árbol binario de tipo 'ProblemTree' que almacena los problemas de la clase.
    ProblemVector problemVect;      //<! Vector ordenado crecientemente de tipo 'ProblemVector' que almacena los problemas de la clase.
    
    /** @brief Función que lee de la entrada un árbol binario de identificadores de problema en preorden.
     *  @param myTree variable de tipo ProblemTree en la que se almacenará la raíz del árbol.
     *  \pre En la entrada 'stdin' debe estar un conjunto de 'problemid que representan los nodos del árbol binario.
     *       Se lee en preorden y se considera el '0' como "nodo vacío", es decir, es el marcador de la lectura en preorden.
     *  \post Se modifica la variable 'myTree' asignandole el árbol leido.
     *  @return 'int': número de elementos que tiene el árbol binario.
     */
    int read_problemTree(ProblemTree& problemTree);

    /** @brief Función que imprime un árbol binario de tipo PtoblemTree.
     *  @param problemTree variable de tipo 'ProblemTree'.
     *  \pre El parámetro de entrada debe ser un árbol valido.
     *  \post true.
     *  @return 'void'.
     */
    void print_problemTree(const ProblemTree& problemTree) const;

    /** @brief Función que inserta los elementos de un árbol binario en un vector.
     *  @param problemVect vector de tipo 'ProblemVector' al que se le insertaran los nodos del árbol.
     *  @param problemTree árbol binario de tipo 'ProblemTree'.
     *  \pre true.
     *  \post Se almacenan en el parámetro 'problemVect' todos los problemas del árbol.
     *  @return 'void'.
     */
    void vectorize_problemTree(ProblemVector& problemVect, const ProblemTree& problemTree, int& index) const;

    /** @brief Función que inserta los problemas de la sesión en un vector.
     *  @param pidVector vector de tipo 'ProblemVector' al que se le insertaran los nodos del árbol.
     *  \pre true.
     *  \post Se alamacenan en el parámetro 'problemVect' todos los problemas del árbol.
     *  @return 'int': número de problemas de la sesión.
     */
    int get_problems_as_vector (ProblemVector& pidVector) const;
public:
    /** @brief Constructor por defecto de la clase.
     *  \pre true.
     *  \post La sesion es NULA.
     */ 
    Sesion();

    /** @brief Constructor sobrecargado de la clase.
     *  \pre La entrada tiene que tener la lista de problemas en preorden (árbol binario).
     *  \post Todas las variables son inicializadas correctamente y el objeto no es NULO.
     */ 
    Sesion(const sessionid& sid);

    /** @brief Consultor de pertenencia de un problema a la sesión.
     *  @param pid identificador de problema ('problemid'). 
     *  \pre El parámetro implicito debe estar ordenando crecientemente.
     *  \post true.
     *  @return 'bool': 'true' si el problema pertenece a la sesión y 'false' si no pertenece a la sesión.
     */
    bool has_problem(const problemid& pid) const;

    /** @brief Adquiere el identificador de la sesión.
     *  \pre La sesión no es nula.
     *  \post true.
     *  @return 'sessionid': identificador de la sesión.
     */
    sessionid get_sessionid() const;

    /** @brief Consultor del estado de la sesión.
     *  \pre true.
     *  \post true.
     *  @return 'bool': 'true' si la sesión es nula, 'false' si no lo es.
     */
    bool is_null() const;

    /** @brief Inserta los problemas de la sesión en un vector. 
     *  @param pidVector vector al que se le insertaran las sesiones.
     *  \pre true.
     *  \post true.
     *  @return int: número de problemas de la sesión.
     */
    int get_problems (ProblemVector& pidVector) const;

    /** @brief Consultor del número de problemas de la sesión.
     *  \pre true.
     *  \post true. 
     *  @return int: número de problemas de la sesión.
     */
    int get_number_of_problems() const;

    /** @brief Adquiere el vector de problemas de la clase.
     *  \pre true.
     *  \post true.
     *  @return 'const ProblemVector&': referencia al vector de la clase. 
     */
    const ProblemVector& get_problem_vector() const;
    
    /** @brief Get the problemTree object
     *  \pre true.
     *  \post true.
     *  @return const BinTree<problemid>& 
     */
    const BinTree<problemid>& get_problemTree() const;

    /** @brief Almacena la infomración de una sesión por el 'stdin'
     *  \pre La información a leer debe estar en un orden correcto.
     *  \post Se almacena el conjunto de problemas y se inicializa el id.
     *  @return 'void'.
     */
    void read();

    /** @brief Escribe la información de una sesión en el 'stdout'.
     *  \pre La sesión debe tener identificador y conjunto de problemas.
     *  \post Se escribe el número de problemas, asi como sus identificadores.
     *  @return 'void'.
     */
    void write() const;
};

#endif