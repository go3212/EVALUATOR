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
typedef BinTree<ProblemData> ProblemTree;

typedef sortedVector<problemid> ProblemVector;


// N > 0, Sin repeticiones, 

/** @class Sesion
 *  @brief Almacena la información de una sesión y facilita su gestión.
 */

class Sesion
{
private:
    sessionid sid;
    bool hasSessionid;
    int n_problems;
    ProblemTree problemTree;
    ProblemVector problemVect;
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

    ProblemTree get_problemTree() const;

    /** @brief Devuelve si la sesion tiene identificador.
     *  \post Devuelve 'true' si la sesión tiene identificador y 'false' si no lo tiene.
     */
    bool has_sessionid() const;

    bool has_problem(const problemid& pid) const;

    int get_problems_as_vector(ProblemVector& pidVector) const;

    int get_problems (ProblemVector& pidVector) const;

    sessionid session_id() const;

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

#endif