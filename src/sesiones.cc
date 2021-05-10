#include "sesiones.hh"

using namespace std;

Sesion Sesiones::nullSession = Sesion();

Sesiones::Sesiones()
{
    total = 0;
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

const Sesion& Sesiones::get_session(const sessionid& sid) const
{
    SessionMap::const_iterator sessionIter = sessionMap.find(sid);
    if(sessionIter == sessionMap.end()) return nullSession;
    return sessionIter->second;
}

const Sesion& Sesiones::get_session_with_iterator (const sessionid& sid, SessionMap::const_iterator& mapIter) const
{
    mapIter = sessionMap.find(sid);
    if(mapIter == sessionMap.end()) return nullSession;
    return mapIter->second;
}


void Sesiones::read()
{
    int n; cin >> n;
    total = n;

    sessionid sid;
    while (n != 0)
    {
        cin >> sid;
        sessionMap.insert(make_pair(sid, Sesion(sid)));
        --n;
    }
}