#include "../hh/usuarios.hh"

using namespace std;

Usuarios::Usuarios()
{
    userMap = map<userid, Usuario>();
}

Usuarios::Usuarios(const Usuario& user)
{

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