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

const bool Problemas::get_problem(const problemid& pid, map<problemid, Problema>::const_iterator& myIter) const
{
    myIter = problemMap.find(pid);
    if (myIter != problemMap.end()) return true;
    return false;
}

const void Problemas::get_iterators(map<problemid, Problema>::const_iterator& myBeginIterator, map<problemid, Problema>::const_iterator& myEndIterator)
{
    myBeginIterator = problemMap.begin();
    myEndIterator = problemMap.end();
}