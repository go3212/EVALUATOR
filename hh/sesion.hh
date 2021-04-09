/** @file sesion.hh
 *  @brief Especificación de la clase 'Sesion'.
 */

#ifndef SESION_HH
#define SESION_HH

#include <iostream>
#include <vector>
#include <string>
#include "BinTree.hh"
#include "problema.hh"

typedef string sessionid;

using namespace std;

// N > 0, Sin repeticiones, 

/** @class Session
 *  @brief Holds data for a session: session name ('name') and a binary tree of problems ('problems') 
 */

class Sesion
{
private:
    sessionid id;
    bool has_sessionid;
    int n_problems;
    BinTree<problemid> problems;

public:

    /** @brief Overloaded default class null constructor.
     *  \post Null session name. All other private variables are also undefined.
     */ 
    Sesion();

    /** @brief Overloaded class constructor.
     *  \post Sets the session id ('this->id') to the constructor parameter ('sid'). All other private <em>int</em> variables are set to zero.
     */ 
    Sesion(const sessionid& sid);

    /** @brief Devuelve si la sesion tiene identificador.
     *  \post Devuelve 'true' si la sesión tiene identificador y 'false' si no lo tiene.
     */
    const bool has_sessionid() const;

    /** @brief Almacena la infomración de una sesión por el 'stdin'
     *  \pre La información a leer debe estar en un orden correcto.
     *  \post Se almacena el conjunto de problemas y se inicializa el id.
     */
    void read();

    /** @brief Escribe la información de una sesión en el 'stdout'.
     *  \pre La sesión debe tener identificador y conjunto de problemas.
     *  \post Se escribe el número de problemas, asi como sus identificadores.
     */
    void write();
};

#endif