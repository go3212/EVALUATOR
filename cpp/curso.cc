#include "../hh/curso.hh"

using namespace std;

Curso::Curso()
{

}

Curso::Curso(const courseid& cid)
{
    this->cid = cid;
}

const bool Curso::set_cid(const courseid& cid)
{
    this->cid = cid;
    return true;
}

const int Curso::inscribed_users() const
{
    return userdata.inscribed_users;
}

const bool Curso::inscribe_user(const userid& uid)
{
    userdata.inscribed_users += 1;
    return true;
}

const bool Curso::is_valid_course(const Sesiones& sessions)
{
    SessionMap::const_iterator sessionMap;
    set<problemid> problemSet;
    pair<set<problemid>::iterator, bool> ret;
    ProblemVector problemVector;
    for (int i = 0; i < total; ++i)
    {
        sessions.get_session(this->sessionVector[i], sessionMap);
        int n = (*sessionMap).second.get_problems (problemVector);
        for (int k = 0; k < n; ++k)
        {   
            ret = problemSet.insert(problemVector[k]);
            if (ret.second == false) return false;
        }
    }
    return true;
}

const void Curso::get_iterators(CourseSessionVector::const_iterator& beginIterator, CourseSessionVector::const_iterator& endIterator) const
{
    beginIterator = sessionVector.begin();
    endIterator = sessionVector.end();
}

const void Curso::write() const
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

const void Curso::read()
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