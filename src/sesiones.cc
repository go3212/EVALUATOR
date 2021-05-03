#include "sesiones.hh"

using namespace std;

Sesiones::Sesiones()
{
    total = 0;
    sessionMap = map<sessionid, Sesion>();
}

int Sesiones::get_number_of_sessions() const
{
    return total;
}

bool Sesiones::add_session(const sessionid& sid)
{
    // Para añadir una sesión, 
    pair<SessionMap::const_iterator, bool> mapPair;
    mapPair = sessionMap.insert(SessionMapPair(sid, Sesion(sid)));
    if (mapPair.second) total += 1;
    return mapPair.second;
}

void Sesiones::get_iterators(SessionMap::const_iterator& beginIterator, SessionMap::const_iterator& endIterator) const
{
    beginIterator = sessionMap.begin();
    endIterator = sessionMap.end();
}

bool Sesiones::get_session(const sessionid& sid, SessionMap::const_iterator& mapIter) const
{
    mapIter = sessionMap.find(sid);
    if(mapIter != sessionMap.end()) return true;
    return false;
}

void Sesiones::read()
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