#include "../hh/problemas.hh"

using namespace std;

Problemas::Problemas()
{
    total = 0;
    problemMap = map<problemid, Problema>();
}

const int Problemas::get_number_of_problems() const
{
    return total;
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

const bool Problemas::add_problem(const problemid& pid)
{
    pair<ProblemMap::const_iterator, bool> mapPair; 
    mapPair = problemMap.insert(ProblemMapSet(pid, Problema(pid)));
    if(mapPair.second) total += 1;
    return mapPair.second;
}

const void Problemas::write()
{

}

const bool Problemas::get_problem(const problemid& pid, ProblemMap::const_iterator& mapIter) const
{
    mapIter = problemMap.find(pid);
    if (mapIter != problemMap.end()) return true;
    return false;
}

const void Problemas::get_iterators(ProblemMap::const_iterator& beginIterator, ProblemMap::const_iterator& endIterator)
{
    beginIterator = problemMap.begin();
    endIterator = problemMap.end();
}