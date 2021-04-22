/** @file sesion.hh
 *  @brief Especificación de la clase 'Sesion'.
 */

#ifndef SESION_HH
#define SESION_HH

#include <iostream>
#include <vector>
#include <string>
#include "tipos.hh"
#include "BinTree.hh"
#include "problema.hh"

using namespace std;

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
    BinTree<problemid> problems;

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

    /** @brief Devuelve si la sesion tiene identificador.
     *  \post Devuelve 'true' si la sesión tiene identificador y 'false' si no lo tiene.
     */
    const bool has_sessionid() const;

    const int get_problems_as_vector(vector<problemid>& pidVector) const;


    const sessionid session_id() const;

    const int get_number_of_problems() const;

    /** @brief Almacena la infomración de una sesión por el 'stdin'
     *  \pre La información a leer debe estar en un orden correcto.
     *  \post Se almacena el conjunto de problemas y se inicializa el id.
     */
    const void read();

    /** @brief Escribe la información de una sesión en el 'stdout'.
     *  \pre La sesión debe tener identificador y conjunto de problemas.
     *  \post Se escribe el número de problemas, asi como sus identificadores.
     */
    const void write() const;

    
};

#endif