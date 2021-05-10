/** @file problema.hh
 *  @brief Especificación de la clase 'Problema' y las estructuras 'Attempts' y 'ProblemData'.
 */
#ifndef PROBLEMA_HH
#define PROBLEMA_HH

#include <iostream>
#include <string>

using namespace std;

/** \typedef courseid 
 *  @brief Identificador de 'Problema'.
*/
typedef string problemid;

/** @struct Attempts
 *  @brief Almacena información sobre los intentos realizados a un 'Problema'.
 *  \pre true.
 *  \post true.
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
     *  \pre true.
     *  \post Se actualizan las variables de la estructura de acuerdo con el formato establecido.
     *  @return bool: true si el parámetro es cierto, false si el parámetro es falso.
     */
    bool update_attempts (const bool& isCorrect);
};

/** @struct ProblemData
 *  @brief Estructura que almacena información sobre un problema desde la perspectiva del usuario.
 *  \pre true.
 *  \post true.
 */
struct ProblemData
{
    Attempts attempts;  //!< Almacena información sobre los intentos realizados al 'Problema'.
    problemid pid;      //!< Identificador del problema al que se refiere la estructura. 
    bool solved;        //!< Variable que indica si el problema ha sido solucionado o no.            

    /** @brief Constructor por defecto de la estructura que inicializa todas las variables excepto el 'pid'.
     *  \pre true.
     *  \post Todas las variables son inicializadas a cero excepto el identificador.
     */
    ProblemData();

    /** @brief Constructor sobrecargado de la estructura que inicializa todas las variables.
     *  @param pid identificador de tipo 'Problema'.
     *  \pre true.
     *  \post Todas las variables son inicializadas a cero excepto el identificador que es inicializado al parámetro.
     */
    ProblemData(const problemid& pid);

    /** @brief Actualiza los datos de todas las variables de la clase frente a un envío. (correcto o no).
     *  @param isCorrect variable que indica si el envío es cierto o falso.
     *  \pre true.
     *  \post Se actualizan las variables de la estructura de acuerdo con el formato establecido.
     *  @return 'void'
     */
    void make_attempt(const bool& isSolved);
};

/** @class Problema
 *  @brief Almacena la información de un problema y facilita su gestión.
 */
class Problema
{
private:
    problemid pid;      //!< Identificador del problema.
    Attempts attempts;  //!< Almacena información sobre todos los intentos realizados al problema.
    bool isNull;        //!< Variable que indica si el objeto ha sido incializado correctamente o no. 

public:
    /** @brief Constructor por defecto de la clase.
     *  \pre true.
     *  \post Todas las variables privadas son inicializadas a cero. El objeto es NULO.
     */ 
    Problema();

    /** @brief Constructor sobrecargado de la calse.
     *  @param pid identificador de problema ('problemid').
     *  \pre true.
     *  \post Todas las variables privadas son inicializadas a cero. El objeto no es NULO y tiene identificador.
     */ 
    Problema(const problemid& pid);

    /** @brief Actualiza el número de intentos al problema.
     *  @param solved valor que indica si el problema ha sido solucionado correctamente o no ('bool').
     *  \pre true.
     *  \post Se incrementa el número de intentos totales en uno. En función de si se ha solucionado correctamente se increamentan los intentos correctos o los incorrectos.
     *  @return 'void';
     */
    void update_problem(const bool& isSolved);

    /**
     * @brief Consultor del estado del problema.
     * \pre true.
     * \post true.
     * @return 'bool': 'true' si el objeto es nulo y 'false' si no lo es
     */
    bool is_null() const;
    
    /**
     * @brief Función que obtiene el ratio del problema.
     * \pre true.
     * \post true.
     * @return double: ratio del problema. 
     */
    double ratio() const;
    
    /** @brief Consultor de intentos realizados al problema.
     *  \pre true.
     *  \post true.
     *  @return 'Attempts&': intentos realizados al problema.
     */
    const Attempts& get_attempts() const;
    
    /** @brief Imprime por pantalla información sobre el problema en el siguiente formato:
     *         pid(intentos totales, intentos exitosos, ratio (t+1)/(e+1))
     *  \pre true.
     *  \post true.
     *  @return true.
     */
    void write() const;
};


#endif