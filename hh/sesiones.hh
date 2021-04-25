/** @file sesiones.hh
 *  @brief Especificación de la clase 'Sesiones'.
 */

#ifndef SESIONES_HH
#define SESIONES_HH

#include <iostream>
#include <map>
#include "tipos.hh"
#include "sesion.hh"

typedef map<sessionid, Sesion> SessionMap;

typedef pair<sessionid, Sesion> SessionMapPair;

using namespace std;

// N > 0, Sin repeticiones, 

/** @class Sesiones
 *  @brief Facilita la gestión de un conjunto de sesiones (obj. 'Sesion').
 */
class Sesiones
{
private:
    int total;
    SessionMap sessionMap;
public:
    /** @brief Constructor por defecto de clase sobrecargado.
     *  \post Número total de sesiones es cero. Conjunto de sesiones ('sessionMap') no definido.
     */ 
    Sesiones();

    /** @brief Constructor de clase sobrecargado, añade una sesión al instanciar la clase.
     *  @param id identificador de la sesión.
     *  @param problem objeto del tipo 'Sesion'.
     *  \post Se añade una sesión y se incializa el conjunto de sesiones.
     */ 
    Sesiones(const string& id, const Sesion& session);

    /** @brief Devuelve el número de sesiones
     * 
     */
    int get_number_of_sessions() const;

    /** @brief Añade una nueva sesión a la lista de sesiones.
     *  @param sid identificador de la sesión.
     *  \post añade una sesión al mapa de sesiones ('sessionMap') si no existia previamente. Devuelve si la sesión se ha añadido ('true') o si ya existia ('false').
     */
    bool add_session(const sessionid& sid);

    /** @brief Busca una sesión en el conjunto de sesiones.
     *  @param sid identificador de sesión ('userid').
     *  \post Devuelve el objeto 'Sesion' por referencia constante si se encuentra, en caso contrario, devuelve NULL.
     */
    bool get_session(const sessionid& sid, SessionMap::const_iterator& mapIter) const;

    /** @brief Devuelve los iteradores del mapa de sesiones 
     *  @param myBeginIterator iterador de la posición inicial.
     *  @param myEndIterator iterador de la posición final.
     *  \post Los argumentos tendran los iteradores correspondientes a la posición inicial y final del mapa de problemas.
     */
    void get_iterators(SessionMap::const_iterator& beginIterator, SessionMap::const_iterator& endIterator) const;

    /** @brief Lee un conjunto de sesiones por la entrada 'stdin' y los guarda.
     *  \pre Número de sesiones a leer en la entrada (S > 0), seguido de S sesiones.
     *  \post Se almacenan los datos.
     */
    void read();
};

#endif