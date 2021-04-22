#include "../hh/usuarios.hh"

using namespace std;

Usuarios::Usuarios()
{
    userMap = map<userid, Usuario>();
}

Usuarios::Usuarios(const Usuario& user)
{

}

const bool Usuarios::add_user (const userid& uid)
{
    map<userid, Usuario>::const_iterator myIter = userMap.find(uid);
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
    map<userid, Usuario>::iterator myIter = userMap.find(uid);
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

void Usuarios::get_iterators(map<userid, Usuario>::const_iterator& myBeginIterator, map<userid, Usuario>::const_iterator& myEndIterator) const
{
    myBeginIterator = userMap.begin();
    myEndIterator = userMap.end();
}

const bool Usuarios::get_user(const userid& uid, map<userid, Usuario>::iterator& myIter)
{
    myIter = userMap.find(uid);
    if (myIter != userMap.end()) return true;
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