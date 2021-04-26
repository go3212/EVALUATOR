#include "../hh/curso.hh"

using namespace std;

Curso::Curso()
{
    total = 0;
    sessionVector = CourseSessionVector();
    userdata = UserData();
}

Curso::Curso(const courseid& cid)
{
    total = 0;
    sessionVector = CourseSessionVector();
    userdata = UserData();
    this->cid = cid;
}

Curso::UserData::UserData()
{
    inscribed_users = 0;
    alltime_users = 0;
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
    return true;
}
int Curso::inscribed_users() const
{
    return userdata.inscribed_users;
}


void Curso::get_iterators(CourseSessionVector::const_iterator& beginIterator, CourseSessionVector::const_iterator& endIterator) const
{
    beginIterator = sessionVector.begin();
    endIterator = sessionVector.end();
}

bool Curso::is_valid_course(const Sesiones& sessions) const
{
    // Un curso es válido si sus sesiones no comparten problemas entre ellas, es decir,
    // la interseccion de dos conjuntos de sesiones cualquiera es vacía. 
    // [NO IMPLEMENTADO] Además, el curso no debe tener las mismas sesiones que otro.
    
    // Por eficiencia, declaramos las variables del bucle fuera de el.
    SessionMap::const_iterator sessionMap;
    set<problemid> problemSet;
    pair<set<problemid>::iterator, bool> ret;
    ProblemVector problemVector;
    // Inv: 0 <= i <= total.
    for (int i = 0; i < total; ++i)
    {   
        // Primero buscamos la sesión en el conjunto de sesiones.
        sessions.get_session(this->sessionVector[i], sessionMap);
        // Cargamos todos los problemas de la sesion en el vector 'problemVector'.
        int n = (*sessionMap).second.get_problems (problemVector);
        // Inv; 0 <= i <= n.
        for (int k = 0; k < n; ++k)
        {   
            // Insertamos los problemas de la sesión en el 'set', ret.second indica
            // si se ha insertado exitosamente ('true') o si ya existia y no se ha insertado
            // false.
            ret = problemSet.insert(problemVector[k]);
            // Si no se ha podido insertar el problema, significa que al menos una sesión tiene el mismo
            // problema, entonces la interseccion de dos sesiones (no sabemos cuales, solo que existen) no es vacía,
            // por lo que el curso no es válido
            if (ret.second == false) return false;
        }
    }
    return true;
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