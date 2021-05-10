/** @file problema.hh
 *  @brief Especificación de la clase 'Problema'.
 */

#ifndef PROBLEMA_HH
#define PROBLEMA_HH

#include <iostream>
#include <string>

using namespace std;

// N > 0, Sin repeticiones, 

/** \typedef courseid 
 *  @brief Identificador de 'Problema'.
*/
typedef string problemid;


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

struct ProblemData
{
    Attempts attempts;
    problemid pid;
    bool solved;

    ProblemData();

    ProblemData(const problemid& pid);

    bool solve(const bool& isSolved);
};


/** @class Problema
 *  @brief Almacena la información de un problema y facilita su gestión.
 */
class Problema
{
private:
    problemid pid;
    Attempts attempts;
    bool isNull;
public:
    /** @brief Overloaded default class constructor.
     *  \post Null problem identifier. All other private <em>int</em> variables are set to zero.
     */ 
    Problema();

    /** @brief Overloaded class constructor.
     *  \post Problem identifier ('this->pid') set to the constructor parameter ('pid'). All other private <em>int</em> variables are set to zero.
     */ 
    Problema(const problemid& pid);

    /** @brief Actualiza el número de intentos al problema.
     *  @param solved valor que indica si el problema ha sido solucionado correctamente o no ('bool').
     *  \post Se incrementa el número de intentos totales en uno. En función de si se ha solucionado correctamente se increamentan los intentos correctos o los incorrectos.
     */
    void update_problem(const bool& isSolved);

    bool is_null() const;
    
    /**
     * @brief Función que obtiene el ratio del problema.
     * \pre true.
     * \post No se modifica ningun parámetro de la clase.
     * @return const double: 
     */
    double ratio() const;

    /** @brief Devuelve los intentos del problema.
     *  \post Se devuelve por referencia un objeto 'Attempts' constante.
     */
    Attempts& get_attempts() const;

    /** @brief Imprime por pantalla información sobre el problema
     *  \post Se imprime por pantalla la infomación del problema en este formato:
     *        pid(intentos totales, intentos exitosos, ratio (t+1)/(e+1))
     */
    void write() const;
};


#endif