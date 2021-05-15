/** @file usuarios.hh
 *  @brief Especificación de la clase 'Usuarios'.
 */

#ifndef USUARIOS_HH
#define USUARIOS_HH

#include "usuario.hh"

using namespace std;

// N > 0, Sin repeticiones, 

/** @typedef UserMap
 *  @brief Mapa de identificador de usuario a 'Usuario'.
 */
typedef map<userid, Usuario> UserMap;

/** @typedef UserMapPair
 *  @brief Pareja de identificador de usuario y 'Usuario'.
 */
typedef pair<userid, Usuario> UserMapPair;

/** @class Usuarios
 *  @brief Facilita la gestión de un conjunto de usuarios (obj. 'Usuario').
 * 
 *  Gestiona un conjunto de usuarios, puede realizar operaciones sobre el conjunto:
 *      - Añadir/eliminar usuarios.
 *      - Solicitar número de usuarios totales.
 *      - Solicitar un 'Usuario' para operar directamente con él.
 */
class Usuarios
{
private:    
    int total;                //!< Número total de usuarios del conjunto.
    UserMap userMap;          //!< Mapa de relaciona un identificador de usuario con su objeto 'Usuario'.
    static Usuario nullUser;  //!< Objeto "nulo" de 'Usuario' que se devuelve por referencia cuando no se ha encontrado un 'Usuario' en el mapa.

public:
    /** @brief Constructor por defecto de clase sobrecargado.
     *  \pre true.
     *  \post Número total de usuarios es cero. Conjunto de cursos ('userMap') no definido.
     */ 
    Usuarios();

    /** @brief Añade un usuario al conjunto de usuarios si este no existia previamente.
     *  @param user objeto de tipo 'userid'.
     *  \pre true.
     *  \post Registra un usuario si no estaba registrado antes.
     *  @return bool: true si se ha añadido un usuario correctamente, false en cualquier otro caso.
     */
    bool add_user(const userid& user);

    /** @brief Da de baja a un usuario del conjunto de usuarios.
     *  @param uid objeto de tipo 'userid'.
     *  \pre true.
     *  \post Elimina un usuario del conjunto de usuarios ('userMap') si existe el usuario.  
     *  @return bool: true si se ha eliminado correctamente el usuario o false ha habido un problema al eliminar/no existe.
     */
    bool delete_user(const userid& uid, Cursos& courses);

    /** @brief Da de baja a un usuario del conjunto de usuarios.
     *  @param userIter objeto de tipo 'UserMap::iterator'.
     *  \pre El iterador proporcionado debe de ser válido.
     *  \post Elimina un usuario del conjunto de usuarios ('userMap') si existe el iterador.  
     *  @return bool: true si se ha eliminado correctamente el usuario o false ha habido un problema al eliminar/no existe.
     */
    bool delete_user(const UserMap::iterator& userIter);

    /** @brief Busca un usuario en el conjunto de usuarios.
     *  @param uid identificador de usuario ('userid').
     *  \pre true.
     *  \post No se modifica ningún objeto de la clase.
     *  @return devuelve true si se ha asignado correctamente el usuario, en cualquier otro caso, false.
     */
    Usuario& get_user(const userid& uid);

    /** @brief Devuelve los iteradores del mapa de problemas 
     *  @param beginIterator iterador de la posición inicial.
     *  @param endIterator iterador de la posición final.
     *  \post Los argumentos tendran los iteradores correspondientes a la posición inicial y final del mapa de problemas.
     *  @return 'void'.
     */
    void get_iterators(UserMap::const_iterator& beginIterator, UserMap::const_iterator& endIterator) const;

    /** @brief Función que devuelve el número de usuarios registrados.
     *  \pre true.
     *  \post Devuelve el número de usuarios registrados.
     *  @return int: número de usuarios registrados.
     */
    int get_number_of_users() const;

    /** @brief Lee un conjunto de usuarios por la entrada 'stdin' y los guarda.
     *  \pre Número de usuarios a leer en la entrada (U >= 0), seguido de U usuarios.
     *  \post Se almacenan los datos.
     *  @return 'void'
     */
    void read();
};

#endif