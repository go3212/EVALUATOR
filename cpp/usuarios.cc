#include "../hh/usuarios.hh"

using namespace std;

Usuarios::Usuarios()
{
    userMap = map<userid, Usuario>();
}

Usuarios::Usuarios(const Usuario& user)
{

}

void Usuarios::get_iterators(map<userid, Usuario>::iterator& myBeginIterator, map<userid, Usuario>::iterator& myEndIterator)
{
    myBeginIterator = userMap.begin();
    myEndIterator = userMap.end();
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