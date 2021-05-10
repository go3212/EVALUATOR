/** @file problemas.hh
 *  @brief Especificación de la clase 'Problemas'.
 */

#ifndef PROBLEMAS_HH
#define PROBLEMAS_HH

#include <vector>
#include <map>
#include "problema.hh"

using namespace std;


typedef map<problemid, Problema> ProblemMap;
typedef pair<problemid, Problema> ProblemPair;

/** @class Problemas
 *  @brief Facilita la gestión de un conjunto de problemas (obj. 'Problema').
 */
class Problemas
{
private:
    int total;
    ProblemMap problemMap;
    static Problema nullProblem;

public:
    /** @brief Constructor por defecto de clase sobrecargado.
     *  \post Número total de problemas es cero. Conjunto de problemas ('problemMap') no definido.
     */ 
    Problemas();

    /** @brief Constructor de clase sobrecargado, añade un problema al instanciar la clase.
     *  @param pid identificador del problema ('problemid').
     *  \post Se añade un problema y se incializa el conjunto de problemas.
     */ 
    Problemas(const problemid& pid);

    /** @brief Devuelve el número total de problemas.
     * 
     */
    int get_number_of_problems() const;

    /** @brief Añade un nuevo problema a la lista de problemas.
     *  @param pid identificador del problema ('problemid').
     *  @param problem objeto de tipo 'Problema'.
     *  \post añade un problema al objeto 'Problemas' si no existia previamente. Devuelve si el problema se ha añadido ('true') o si ya existia ('false').
     */
    bool add_problem(const problemid& pid);

    /** @brief Busca un problema en el conjunto de problemas.
     *  @param pid identificador de problema ('problemid').
     *  \post devuelve el objeto 'Problema' por referencia si se ha encontrado, en caso opuesto, devuelve NULL.
     */
    Problema& search_problem(const problemid& pid);

    /** @brief Función que busca problemas y devuelve un puntero.
     *  @param pid identificador de problema ('problemid').
     *  \post Devuelve un puntero al objeto 'Problema' buscado. Si no se ha encontrado, devuelve NULL. 
     */
    Problema& get_problem(const problemid& pid);

    /** @brief Devuelve los iteradores del mapa de problemas 
     *  @param myBeginIterator iterador de la posición inicial.
     *  @param myEndIterator iterador de la posición final.
     *  \post Los argumentos tendran los iteradores correspondientes a la posición inicial y final del mapa de problemas.
     */
    void get_iterators(ProblemMap::const_iterator& beginIterator, ProblemMap::const_iterator& rndIterator);

    /** @brief Función que actualiza el número de intentos a un problema.
     *  @param pid identificador de problema ('problemid').
     *  \post Devuelve 'true' si el problema a actualizar se ha encontrado y 'false' si no se ha encontrado.
     */
    bool updateProblemAttempt(const problemid& pid);

    /** @brief Lee un conjunto de problemas por la entrada 'stdin' y los guarda.
     *  \pre Número de problemas a leer en la entrada (P > 0), seguido de P problemas.
     *  \post Se almacenan los datos.
     */
    void read();

    /** @brief Escribe por pantalla todos los problemas del conjunto de problemas
     *  \post Se imprime por 'stdout' los problemas, de manera ordenada ascendentemente.
     */
    void write();
};

#endif