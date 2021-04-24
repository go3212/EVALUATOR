#include "../hh/usuarios.hh"

using namespace std;

Usuarios::Usuarios()
{
    userMap = UserMap();
}

Usuarios::Usuarios(const Usuario& user)
{

}

const bool Usuarios::add_user (const userid& uid)
{
    UserMap::const_iterator myIter = userMap.find(uid);
    if (myIter == userMap.end())
    {
        userMap[uid] = Usuario(uid);
        total += 1;
        return true;
    }
    return false;
}

const bool Usuarios::delete_user(const userid& uid) 
{
    UserMap::iterator myIter = userMap.find(uid);
    if (myIter != userMap.end())
    {
        userMap.erase(myIter);
        total -= 1;
        return true;
    }
    return false;
}

const int Usuarios::get_number_of_users() const
{
    return total;
}

void Usuarios::get_iterators(UserMap::const_iterator& beginIterator, UserMap::const_iterator& endIterator) const
{
    beginIterator = userMap.begin();
    endIterator = userMap.end();
}

const bool Usuarios::get_user(const userid& uid, UserMap::iterator& mapIter)
{
    mapIter = userMap.find(uid);
    if (mapIter != userMap.end()) return true;
    return false;
}

const void Usuarios::read()
{
    int n; cin >> n;
    total = n;

    userid uid;
    while (n != 0)
    {   
        cin >> uid;
        userMap[uid] = Usuario(uid);
        --n;
    }
}