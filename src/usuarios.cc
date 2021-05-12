#include "usuarios.hh"

using namespace std;

Usuario Usuarios::nullUser = Usuario();

Usuarios::Usuarios()
{
    total = 0;
    userMap = UserMap();
}

bool Usuarios::add_user (const userid& uid)
{
    // Miramos si el usuario existe, si existe, no añadimos nada.
    UserMap::const_iterator userIter = userMap.find(uid);
    if (userIter != userMap.end()) return false;
    // A partir de aquí, seguro que el usuario no está registrado.
    userMap[uid] = Usuario(uid);
    total += 1;
    return true;
}

bool Usuarios::delete_user(const userid& uid, Cursos& courses)
{
    // Miramos si el usuario existe, si no existe, no eliminamos nada.
    UserMap::iterator userIter = userMap.find(uid);
    if (userIter == userMap.end()) return false;
    // A partir de aquí, seguro que el usuario está registrado.
    userIter->second.force_uninscribe(courses);
    userMap.erase(userIter);
    total -= 1;
    return true;
}

bool Usuarios::delete_user(const UserMap::iterator& userIter)
{
    // Seguro que el iterador es válido, entonces si es el del final del mapa, no podemos eliminar usuario.
    if (userIter == userMap.end()) return false;
    // Seguro que el iterador corresponde a un usuario.
    userMap.erase(userIter);
    total -= 1;
    return true;
}

int Usuarios::get_number_of_users() const
{
    // El número total de usuarios siempre está inicializado.
    return total;
}

void Usuarios::get_iterators(UserMap::const_iterator& beginIterator, UserMap::const_iterator& endIterator) const
{
    beginIterator = userMap.begin();
    endIterator = userMap.end();
}

Usuario& Usuarios::get_user(const userid& uid)
{
    // Buscamos el iterador en el mapa.
    UserMap::iterator userMapIter = userMap.find(uid);
    // Si no existe el usuario en el mapa, devolvemos false.
    if (userMapIter == userMap.end()) return nullUser;
    return (userMapIter->second);
}

void Usuarios::read()
{
    // Se lee el número de usuarios en el 'stdin'. n >= 0
    int n; cin >> n;
    total += n; // Añadimos n usuarios al total.

    userid uid;
    while (n > 0)
    {   
        cin >> uid;
        userMap[uid] = Usuario(uid);
        --n;
    }
}