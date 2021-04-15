#include "../hh/problemas.hh"

using namespace std;

Problemas::Problemas()
{
    total = 0;
    problemMap = map<problemid, Problema>();
}

const void Problemas::read()
{
    int n; cin >> n;
    total = n;

    problemid pid; 
    while (n != 0)
    {
        cin >> pid;
        problemMap[pid] = Problema(pid);
        --n;
    }
}

const void Problemas::write()
{
    cout << "#listar_problemas" << endl;
    map<problemid, Problema>::iterator it = problemMap.begin();

    for (it = problemMap.begin(); it != problemMap.end(); ++it)
    {
        cout << it->first << endl;
    }
}