#include "../hh/sesiones.hh"

using namespace std;

Sesiones::Sesiones()
{
    total = 0;
    sessionMap = map<sessionid, Sesion>();
}

const void Sesiones::read()
{
    int n; cin >> n;
    total = n;

    sessionid sid;
    while (n != 0)
    {
        cin >> sid;
        sessionMap[sid] = Sesion(sid);
        --n;
    }
}

const void Sesiones::write()
{
    cout << "#listar_sesiones" << endl;
    map<problemid, Sesion>::iterator it = sessionMap.begin();

    for (it = sessionMap.begin(); it != sessionMap.end(); ++it)
    {
        cout << it->first << " ";
        (it->second).write();
        cout << endl;
    }
}