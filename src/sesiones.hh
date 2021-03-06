/** @file sesiones.hh
 *  @brief Especificación de la clase 'Sesiones'.
 */

#ifndef SESIONES_HH
#define SESIONES_HH

#include <map>
#include "sesion.hh"

/** @typedef SesionMap
 *  @brief Mapa para almacenar objetos del tipo 'Sesion'. La key es de tipo 'sessionid'. 
 */
typedef map<sessionid, Sesion> SessionMap;

/** @typedef SesionMapPair
 *  @brief Par de valores del 'SessionMap'. 
 */
typedef pair<sessionid, Sesion> SessionMapPair;

using namespace std;

// N > 0, Sin repeticiones, 

/** @class Sesiones
 *  @brief Facilita la gestión de un conjunto de sesiones (obj. 'Sesion').
 * 
 *  Gestiona un conjunto de sesiones, puede realizar diferentes operaciones sobre el conjunto:
 *      - Añadir sesiones, directamente o por lectura.
 *      - Solicitar número de sesiones.
 *      - Solicitar una 'Sesion' para operar directamente sobre ella.
 */
class Sesiones
{
private:
    int total;                  //<! Número de sesiones en el 'sessionMap'.
    SessionMap sessionMap;      //<! Mapa de sesiones. Tipo 'SessionMap'.
    static Sesion nullSession;
public:
    /** @brief Constructor por defecto de clase sobrecargado.
     *  \pre true.
     *  \post Número total de sesiones es cero. Mapa 'sessionMap' no definido.
     */ 
    Sesiones();

    /** @brief Devuelve el número de sesiones
     *  \pre true.
     *  \post No se modifica ningún objeto de la clase.
     *  @return int: número de sesiones almacenadas en el 'sessionMap'.
     */
    int get_number_of_sessions() const;

    /** @brief Añade una nueva sesión a la lista de sesiones.
     *  @param sid identificador de la sesión.
     *  \pre La sesión a añadir es válida. (Se encuentra en el 'stdin' y sigue el formato de declaración de sesion del objeto 'Sesion').
     *  \post Añade una sesión al mapa de sesiones, si no existia previamente. 
     *  @return bool: true si la sesión se ha añadido correctamente y false si ya existia.
     */
    bool add_session(const sessionid& sid);

    /** @brief Busca una sesión en el conjunto de sesiones.
     *  @param sid identificador de sesión ('userid').
     *  \pre true.
     *  \post No se modifica ningún objeto de la clase.
     *  @return true si se encuentra la sesión o false si no se encuentra.
     */
    const Sesion& get_session(const sessionid& sid) const;

    /** @brief Busca una sesión en el conjunto de sesiones.
     *  @param sid identificador de sesión ('userid').
     *  @param mapIter iterador del tipo 'SessionMap::const_iterator' al que se le asignará la sesión encontrada, si se encuentra.
     *  \pre true.
     *  \post No se modifica ningún objeto de la clase.
     *  @return true si se encuentra la sesión o false si no se encuentra.
     */
    const Sesion& get_session_with_iterator (const sessionid& sid, SessionMap::const_iterator& mapIter) const;

    /** @brief Devuelve los iteradores del mapa de sesiones 
     *  @param beginIterator iterador de la posición inicial.
     *  @param endIterator iterador de la posición final.
     *  \pre true.
     *  \post Los argumentos tendran los iteradores correspondientes a la posición inicial y final del mapa de sesiones.
     *  @return void.
     */
    void get_iterators(SessionMap::const_iterator& beginIterator, SessionMap::const_iterator& endIterator) const;

    /** @brief Lee un conjunto de sesiones por la entrada 'stdin' y los guarda.
     *  \pre Número de sesiones a leer en la entrada (S > 0), seguido de S sesiones.
     *  \post Se almacenan los datos.
     *  @return void.
     */
    void read();
};

#endif