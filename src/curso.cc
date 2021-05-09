#include "curso.hh"


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
    isHintMapInitialized = false;
}

Curso::Curso(const courseid& cid)
{
    this->cid = cid;
    total = 0;
    isHintMapInitialized = false;
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

sessionid Curso::get_problem_session (const problemid& pid) const
{
    map<problemid, sessionid>::const_iterator it = hintMap.find(pid);
    if (it != hintMap.end()) return (*it).second;
    return "0";
}

bool Curso::initialize_hintMap(const Sesiones& sessions)
{
    // Por eficiencia, declaramos las variables del bucle fuera de el.
    SessionMap::const_iterator sessionMap;
    pair<map<problemid, sessionid>::iterator, bool> ret;
    ProblemVector problemVector;
    vector<problemid>::const_iterator beginIter, endIter;
    // Inv: 0 <= i <= total.
    for (int i = 0; i < total; ++i)
    {   
        // Primero buscamos la sesión en el conjunto de sesiones.
        sessions.get_session(this->sessionVector[i], sessionMap);
        // Cargamos todos los problemas de la sesion en el vector 'problemVector'.
        (*sessionMap).second.get_problem_vector_iterators(beginIter, endIter);
        // Inv; 0 <= i <= n.
        while(beginIter != endIter)
        {   
            // Insertamos los problemas de la sesión en el 'set', ret.second indica
            // si se ha insertado exitosamente ('true') o si ya existia y no se ha insertado
            // false.
            ret = hintMap.insert(make_pair(*beginIter, sessionVector[i]));
            // Si no se ha podido insertar el problema, significa que al menos una sesión tiene el mismo
            // problema, entonces la interseccion de dos sesiones (no sabemos cuales, solo que existen) no es vacía,
            // por lo que el curso no es válido
            if (ret.second == false) return false;
            ++beginIter;
        }
    }
    isHintMapInitialized = true;
    return true;
}

bool Curso::is_hintMap_initialized() const
{
    return isHintMapInitialized;
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