#include "../hh/sesiones.hh"

using namespace std;

Sesiones::Sesiones()
{
    total = 0;
    sessionMap = map<sessionid, Sesion>();
}

const int Sesiones::get_number_of_sessions() const
{
    return total;
}

const bool Sesiones::add_session(const sessionid& sid)
{
    pair<map<sessionid, Sesion>::const_iterator, bool> myPair;
    myPair = sessionMap.insert(pair<sessionid, Sesion>(sid, Sesion(sid)));
    if (myPair.second) total += 1;
    return myPair.second;
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