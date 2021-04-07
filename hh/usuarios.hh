#ifndef USUARIOS_HH
#define USUARIOS_HH

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include "hh/usuario.hh"

using namespace std;

// N > 0, Sin repeticiones, 

/** @class Usuarios
 *  @brief Almacena todos los usuarios y permite su gestión.
 */
class Usuarios
{
private:
    int total;
    map<int, Usuario> userMap;

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
     *  @param user objeto de tipo 'Usuario'.
     *  \post elimina un usuario del conjunto de usuarios ('userMap').  
     *        Devuelve si se ha eliminado correctamente el usuario ('true') o ha habido un problema al eliminar/no existe ('false').
     */
    bool delete_user(const Usuario& user);

    /** @brief Se inscibe a un usuario en un curso.
     *  @param uid identificador de usuario ('int')
     *  @param cid identificador de curso ('int').
     *  \post el usuario queda inscrito en el curso si se ha encontrado el usuario y el curso en la base de datos, además, el usuario no puede estrar inscrito. En este caso se devuelve 'true', en los otros, 
     *        se devuelve 'false'. 
     */
    bool inscribe_user(const int& uid, const int& cid);

    /** @brief Busca un usuario en el conjunto de usuarios.
     *  @param uid identificador de usuario ('int').
     *  \post devuelve el objeto 'Usuario' por referencia si se encuentra, en caso contrario, devuelve NULL.
     */
    Usuario& get_user(const int& uid);
};

#endif