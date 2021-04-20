#include "../hh/sesiones.hh"

using namespace std;

Sesiones::Sesiones()
{
    total = 0;
    sessionMap = map<sessionid, Sesion>();
}

void Sesiones::get_iterators(map<sessionid, Sesion>::const_iterator& myBeginIterator, map<sessionid, Sesion>::const_iterator& myEndIterator) const
{
    myBeginIterator = sessionMap.begin();
    myEndIterator = sessionMap.end();
}

const bool Sesiones::get_session(const sessionid& sid, map<userid, Sesion>::const_iterator& myIter) const
{
    myIter = sessionMap.find(sid);
    if(myIter != sessionMap.end()) return true;
    return false;
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