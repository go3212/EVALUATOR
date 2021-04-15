#include "../hh/curso.hh"

using namespace std;

Curso::Curso()
{

}

Curso::Curso(const courseid& cid)
{
    this->cid = cid;
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