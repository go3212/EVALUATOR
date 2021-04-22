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

const bool Curso::is_valid_course(const Sesiones& sessions)
{
    set<problemid> mySet;
    map<sessionid, Sesion>::const_iterator myIter;
    pair<set<problemid>::iterator, bool> ret;
    vector<problemid> pidVector;
    for (int i = 0; i < total; ++i)
    {
        sessions.get_session(this->sessions[i], myIter);
        int n = (*myIter).second.get_problems_as_vector(pidVector);
        for (int k = 0; k < n; ++k)
        {   
            ret = mySet.insert(pidVector[k]);
            if (ret.second == false) return false;
        }
    }
    return true;
}

const void Curso::get_iterators(vector<sessionid>::const_iterator& myBeginIterator, vector<sessionid>::const_iterator& myEndIterator) const
{
    myBeginIterator = sessions.begin();
    myEndIterator = sessions.end();
}

const void Curso::write() const
{
    cout << cid << ' ' << userdata.alltime_users << ' ';
    cout << userdata.inscribed_users << ' ' << total << " (";
    for (int i = 0; i < total - 1; ++i)
    {
        cout << sessions[i];
        cout << ' ';
    }
    cout << sessions[total - 1];
    cout << ')';
}   

const void Curso::read()
{
    int n; cin >> n;
    total = n;

    sessions = vector<sessionid>(total);

    sessionid sid;
    while (n != 0)
    {   
        cin >> sid;
        sessions[total - n] = sid;
        --n;
    }
}