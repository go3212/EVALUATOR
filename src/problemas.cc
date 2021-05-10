#include "problemas.hh"

using namespace std;

Problema Problemas::nullProblem = Problema();

Problemas::Problemas()
{
    total = 0;
    problemMap = map<problemid, Problema>();
}

int Problemas::get_number_of_problems() const
{
    return total;
}

void Problemas::read()
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

bool Problemas::add_problem(const problemid& pid)
{
    pair<ProblemMap::const_iterator, bool> mapPair; 
    mapPair = problemMap.insert(ProblemPair(pid, Problema(pid)));
    if(mapPair.second) total += 1;
    return mapPair.second;
}

void Problemas::write()
{

}

Problema& Problemas::get_problem(const problemid& pid)
{
    ProblemMap::iterator problemIter = problemMap.find(pid);
    if (problemIter == problemMap.end()) return nullProblem;
    return problemIter->second;
}

void Problemas::get_iterators(ProblemMap::const_iterator& beginIterator, ProblemMap::const_iterator& endIterator)
{
    beginIterator = problemMap.begin();
    endIterator = problemMap.end();
}
