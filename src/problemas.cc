#include "problemas.hh"

using namespace std;

Problema Problemas::nullProblem = Problema();

Problemas::Problemas()
{
    total = 0;
}

int Problemas::get_number_of_problems() const
{
    return total;
}

bool Problemas::add_problem(const problemid& pid)
{
    pair<ProblemMap::const_iterator, bool> mapPair; 
    mapPair = problemMap.insert(make_pair(pid, Problema(pid)));  // Insertamos e incializamos el objeto 'Problema' al mismo tiempo para evitar copias.
    if(mapPair.second) total += 1;                               // Si se ha podido insertar el problema, incrementamos el número total de problemas.
    return mapPair.second;
}

Problema& Problemas::get_problem(const problemid& pid)
{
    ProblemMap::iterator problemIter = problemMap.find(pid);    // Buscamos el problema en el mapa de problemas.
    if (problemIter == problemMap.end()) return nullProblem;    // Si el iterador "apunta" al final del mapa, devolvemos el nullProblem, pues nos indica que el problema no se ha encontrado.
    return problemIter->second;
}

void Problemas::get_iterators(ProblemMap::const_iterator& beginIterator, ProblemMap::const_iterator& endIterator) const
{
    beginIterator = problemMap.begin();
    endIterator = problemMap.end();
}

void Problemas::read()
{
    int n; cin >> n;    // Nos entran n problemas.
    total = n;

    problemid pid;
    while (n != 0)
    {
        cin >> pid;
        problemMap[pid] = Problema(pid);
        --n;
    }
}