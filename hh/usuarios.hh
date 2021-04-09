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
     *  @param user objeto de tipo 'Usuario'.
     *  \post añade un usuario al conjunto de usuarios ('userMap') si no existe otro usuario con el mismo identificador.  
     *        Devuelve si se ha añadido correctamente el usuario ('true') o ha habido un problema al añadirlo ('false').
     */
    bool add_user(const Usuario& user);

    /** @brief Elimina un usuario del conjunto de usuarios.
     *  @param uid objeto de tipo 'userid'.
     *  \post elimina un usuario del conjunto de usuarios ('userMap').  
     *        Devuelve si se ha eliminado correctamente el usuario ('true') o ha habido un problema al eliminar/no existe ('false').
     */
    bool delete_user(const userid& uid);

    /** @brief Se inscibe a un usuario en un curso.
     *  @param uid identificador de usuario ('userid')
     *  \post El usuario queda inscrito en el curso si se ha encontrado el usuario y el curso en la base de datos, además, el usuario no puede estrar inscrito. En este caso se devuelve 'true', en los otros, 
     *        se devuelve 'false'. 
     */
    bool inscribe_user(const userid& uid);

    /** @brief Busca un usuario en el conjunto de usuarios.
     *  @param uid identificador de usuario ('userid').
     *  \post devuelve el objeto 'Usuario' por referencia si se encuentra, en caso contrario, devuelve NULL.
     */
    const Usuario& get_user(const userid& uid) const;
};

#endif