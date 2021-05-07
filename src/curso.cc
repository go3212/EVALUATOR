#include "curso.hh"
#include <map>

using namespace std;

//######################################//
//      FUNCIONES AJENAS A LA CLASE     //
//######################################//
// bool get_problemDataNode (const problemid& pid, ProblemData& problemData, const BinTree<ProblemData>& problemTree)
// {
//     if (problemTree.empty()) return false;
//     if (problemTree.value().pid == pid)
//     {
//         problemData = problemTree.value();
//         return true;
//     }
//     return (get_problemDataNode (pid, problemData, problemTree.left()) or get_problemDataNode (pid, problemData, problemTree.right()));
// }

//######################################//
//        FUNCIONES DE A LA CLASE       //
//######################################//
Curso::Curso()
{
    total = 0;
    sessionVector = CourseSessionVector();
    userdata = UserData();
    initializedHintMap = false;
    valid = false;
}

Curso::Curso(const courseid& cid)
{
    total = 0;
    sessionVector = CourseSessionVector();
    userdata = UserData();
    this->cid = cid;
    initializedHintMap = false;
    valid = false;
}

void Curso::force_uninscribe()
{
    userdata.inscribed_users -= 1;
}

Curso::UserData::UserData()
{
    inscribed_users = 0;
    alltime_users = 0;
}

courseid Curso::get_cid() const
{
    return cid;
}

bool Curso::set_cid(const courseid& cid)
{
    this->cid = cid;
    return true;
}

bool Curso::inscribe_user() // const userid& uid
{
    userdata.inscribed_users += 1;
    return true;
}

bool Curso::uninscribe_user() // const userid& uid
{
    userdata.inscribed_users -= 1;
    userdata.alltime_users += 1;
    return true;
}
int Curso::inscribed_users() const
{
    return userdata.inscribed_users;
}
//???
void Curso::update_problem (const bool& isInscribed)
{
    // Actualizamos el registro de usuarios (inscritos y los que han superado el curso)
    userdata.alltime_users += 1*(!isInscribed);
    userdata.inscribed_users -= 1*(!isInscribed);
}

int Curso::get_iterators(CourseSessionVector::const_iterator& beginIterator, CourseSessionVector::const_iterator& endIterator) const
{
    beginIterator = sessionVector.begin();
    endIterator = sessionVector.end();
    return total;
}

int Curso::get_number_of_sessions() const
{
    return total;
}

int Curso::vector_session_position_of_problem(const problemid& pid) const
{
    map<problemid, int>::const_iterator it = hintMap.find(pid);
    if (it != hintMap.end()) return (*it).second;
    return -1;
}

bool Curso::is_valid_course(const Sesiones& sessions)
{
    // Un curso es válido si sus sesiones no comparten problemas entre ellas, es decir,
    // la interseccion de dos conjuntos de sesiones cualquiera es vacía. 
    // [NO IMPLEMENTADO] Además, el curso no debe tener las mismas sesiones que otro.
    
    // Por eficiencia, declaramos las variables del bucle fuera de el.
    SessionMap::const_iterator sessionMap;
    pair<map<problemid, int>::iterator, bool> ret;
    ProblemVector problemVector;
    // Inv: 0 <= i <= total.
    for (int i = 0; i < total; ++i)
    {   
        // Primero buscamos la sesión en el conjunto de sesiones.
        sessions.get_session(this->sessionVector[i], sessionMap);
        // Cargamos todos los problemas de la sesion en el vector 'problemVector'.
        vector<problemid>::const_iterator beginIter, endIter;
        (*sessionMap).second.get_problems_iterator(beginIter, endIter);
        // Inv; 0 <= i <= n.
        while(beginIter != endIter)
        {   
            // Insertamos los problemas de la sesión en el 'set', ret.second indica
            // si se ha insertado exitosamente ('true') o si ya existia y no se ha insertado
            // false.
            ret = hintMap.insert(pair<problemid, int>((*beginIter), i));
            // Si no se ha podido insertar el problema, significa que al menos una sesión tiene el mismo
            // problema, entonces la interseccion de dos sesiones (no sabemos cuales, solo que existen) no es vacía,
            // por lo que el curso no es válido
            if (ret.second == false) return false;
            ++beginIter;
        }
    }
    initializedHintMap = true;
    return true;
}

bool Curso::initialized_hintMap() const
{
    return initializedHintMap;
}

void Curso::write() const
{
    cout << cid << ' ' << userdata.alltime_users << ' ';
    cout << userdata.inscribed_users << ' ' << total << " (";
    for (int i = 0; i < total - 1; ++i)
    {
        cout << sessionVector[i];
        cout << ' ';
    }
    cout << sessionVector[total - 1];
    cout << ')';
}   

void Curso::read(const Sesiones& sessions)
{
    int n; cin >> n;
    total = n;

    sessionVector = CourseSessionVector(total);

    sessionid sid;
    while (n != 0)
    {   
        cin >> sid;
        sessionVector[total - n] = sid;

        // Cargamos el hintMap 
        SessionMap::const_iterator sessionMap;
        ProblemVector problemVector;

        // Primero buscamos la sesión en el conjunto de sesiones.
        sessions.get_session(sid, sessionMap);
        // Cargamos todos los problemas de la sesion en el vector 'problemVector'.
        vector<problemid>::const_iterator beginIter, endIter;
        (*sessionMap).second.get_problems_iterator(beginIter, endIter);
        while(beginIter != endIter)
        {   
            // Insertamos los problemas de la sesión en el 'set', ret.second indica
            // si se ha insertado exitosamente ('true') o si ya existia y no se ha insertado
            // false.
            hintMap.insert(pair<problemid, int>((*beginIter), total - n));
            ++beginIter;
        }
        --n;
    }
    valid = true;
}

void Curso::read()
{
    int n; cin >> n;
    total = n;

    sessionVector = CourseSessionVector(total);

    sessionid sid;
    while (n != 0)
    {   
        cin >> sid;
        sessionVector[total - n] = sid;
        --n;
    }
}