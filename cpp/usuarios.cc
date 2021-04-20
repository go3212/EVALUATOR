#include "../hh/usuarios.hh"

using namespace std;

Usuarios::Usuarios()
{
    userMap = map<userid, Usuario>();
}

Usuarios::Usuarios(const Usuario& user)
{

}

void Usuarios::get_iterators(map<userid, Usuario>::const_iterator& myBeginIterator, map<userid, Usuario>::const_iterator& myEndIterator) const
{
    myBeginIterator = userMap.begin();
    myEndIterator = userMap.end();
}

const bool Usuarios::get_user(const userid& uid, map<userid, Usuario>::const_iterator& myIter) const
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