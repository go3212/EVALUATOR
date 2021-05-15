/** @file problemas.hh
 *  @brief Especificación de la clase 'Problemas'.
 */

#ifndef PROBLEMAS_HH
#define PROBLEMAS_HH

#include <vector>
#include <map>
#include "problema.hh"

using namespace std;

/** @typedef ProblemMap 
 *  @brief Representa un mapa de problemas, donde la 'key' es el nombre del problema ('problemid') y el value es el objeto de tipo 'Problema'.
 */
typedef map<problemid, Problema> ProblemMap;

/** @class Problemas
 *  @brief Facilita la gestión de un conjunto de problemas (obj. 'Problema').
 * 
 *  La clase tiene el propósito de gestionar un conjunto de problemas. Se pueden añadir y quitar problemas asi como "adquirirlos" 
 *  y realizar operaciones sobre el conjunto.
 */
class Problemas
{
private:
    int total;                      //!< Número total de problemas.
    ProblemMap problemMap;          //!< Mapa de problemas.
    static Problema nullProblem;    //!< Mapa 'no definido': este mapa se utiliza en algunos métodos para indicar que no se ha encontrado el mapa buscado.  

public:
    /** @brief Constructor por defecto de clase.
     *  \pre true.
     *  \post Número total de problemas es cero. Conjunto de problemas ('problemMap') no definido.
     */ 
    Problemas();

    /** @brief Consultor del número total de problemas.
     *  \pre true.
     *  \post true.
     *  @return 'int': número total de problemas.
     */
    int get_number_of_problems() const;

    /** @brief Añade un nuevo problema al conjunto de problemas.
     *  @param pid identificador del problema ('problemid').
     *  \pre Identificador de problema válido.
     *  \post El tamaño del conjunto de problemas es incrementado en uno, si no exisita un problema con el mismo identificador.
     *  @return 'bool': 'true' si se ha añadido correctamente el problema y 'falso' en caso opuesto.
     */
    bool add_problem(const problemid& pid);

    /** @brief Función que adquiere el problema solicidado.
     *  @param pid identificador de problema ('problemid').
     *  \pre Identificador de problema válido.
     *  \post true.
     *  @return 'Problema&': referencia al 'Problema' con identificador 'pid'.
     */
    Problema& get_problem(const problemid& pid);

    /** @brief Función que aquiere los iteradores del mapa de problemas.
     *  @param myBeginIterator iterador de la posición inicial.
     *  @param myEndIterator iterador de la posición final.
     *  \pre true.
     *  \post true.
     *  @return 'void'
     */
    void get_iterators(ProblemMap::const_iterator& beginIterator, ProblemMap::const_iterator& endIterator) const;

    /** @brief Lee un conjunto de problemas por la entrada 'stdin' y los guarda.
     *  \pre Número de problemas a leer en la entrada (P > 0), seguido de P problemas.
     *  \post Se almacenan los datos.
     *  @return 'void'
     */
    void read();
};

#endif