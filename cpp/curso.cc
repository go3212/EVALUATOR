#include "../hh/curso.hh"

using namespace std;

Curso::Curso()
{

}

Curso::Curso(const courseid& cid)
{
    this->cid = cid;
}

const void Curso::write() const
{
    cout << cid << ' ' << userdata.alltime_users << ' ';
    cout << userdata.inscribed_users << ' ' << total << " (";
    for (int i = 0; i < total - 1; ++i)
    {
        cout << session[i];
        cout << ' ';
    }
    cout << session[total - 1];
    cout << ')';
}   

const void Curso::read()
{
    int n; cin >> n;
    total = n;

    session = vector<sessionid>(total);

    sessionid sid;
    while (n != 0)
    {   
        cin >> sid;
        session[total - n] = sid;
        --n;
    }
}