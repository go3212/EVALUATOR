/** @file usuarios.hh
 *  @brief Especificación de la clase 'Usuarios'.
 */

#ifndef USUARIOS_HH
#define USUARIOS_HH

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include "tipos.hh"
#include "usuario.hh"
#include "curso.hh"
#include "cursos.hh"

using namespace std;

// N > 0, Sin repeticiones, 

/** @class Usuarios
 *  @brief Facilita la gestión de un conjunto de usuarios (obj. 'Usuario').
 */
class Usuarios
{
private:
    int total;
    map<userid, Usuario> userMap;

public:
    /** @brief Constructor por defecto de clase sobrecargado.
     *  \post Número total de usuarios es cero. Conjunto de cursos ('userMap') no definido.
     */ 
    Usuarios();

    /** @brief Constructor de clase sobrecargado, añade un usuario al instanciar la clase.
     *  @param user objeto del tipo 'Usuario'.
     *  \post Se añade un usuario y se incializa el conjunto de usuarios ('userMap').
     */ 
    Usuarios(const Usuario& user);

    /** @brief Añade un nuevo usuario al conjunto de usuarios.
     *  @param user objeto de tipo 'userid'.
     *  \post añade un usuario al conjunto de usuarios ('userMap') si no existe otro usuario con el mismo identificador.  
     *        Devuelve si se ha añadido correctamente el usuario ('true') o ha habido un problema al añadirlo ('false').
     */
    const bool add_user(const userid& user);

    const int get_number_of_users() const;

    /** @brief Elimina un usuario del conjunto de usuarios.
     *  @param uid objeto de tipo 'userid'.
     *  \post elimina un usuario del conjunto de usuarios ('userMap').  
     *        Devuelve si se ha eliminado correctamente el usuario ('true') o ha habido un problema al eliminar/no existe ('false').
     */
    const bool delete_user(const userid& uid);

    /** @brief Se inscibe a un usuario en un curso.
     *  @param uid identificador de usuario ('userid')
     *  \pre El curso al que se inscribe debe existir.
     *  \post El usuario queda inscrito en el curso si se ha encontrado el usuario y el curso en la base de datos, además, el usuario no puede estrar inscrito. En este caso se devuelve 'true', en los otros, 
     *        se devuelve 'false'. 
     */
    bool inscribe_user(const userid& uid);

    /** @brief Busca un usuario en el conjunto de usuarios.
     *  @param uid identificador de usuario ('userid').
     *  \post devuelve true si se ha asignado correctamente el usuario, en cualquier otro caso, false.
     */
    const bool get_user(const userid& uid, map<userid, Usuario>::iterator& myIter);

    /** @brief Devuelve los iteradores del mapa de problemas 
     *  @param myBeginIterator iterador de la posición inicial.
     *  @param myEndIterator iterador de la posición final.
     *  \post Los argumentos tendran los iteradores correspondientes a la posición inicial y final del mapa de problemas.
     */
    void get_iterators(map<userid, Usuario>::const_iterator& myBeginIterator, map<userid, Usuario>::const_iterator& myEndIterator) const;

    /** @brief Lee un conjunto de usuarios por la entrada 'stdin' y los guarda.
     *  \pre Número de usuarios a leer en la entrada (U > 0), seguido de U usuarios.
     *  \post Se almacenan los datos.
     */
    const void read();
};

#endif