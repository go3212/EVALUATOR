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

}

void Problemas::get_iterators(map<problemid, Problema>::iterator& myBeginIterator, map<problemid, Problema>::iterator& myEndIterator)
{
    myBeginIterator = problemMap.begin();
    myEndIterator = problemMap.end();
}