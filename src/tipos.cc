#include "tipos.hh"
#include <algorithm>

using namespace std;

int binary_search_LH (const problemid& item, const vector<ProblemData>& myVect, int vectSize)
{
    int left = 0, right = vectSize - 1, m;
    while (left <= right)
    {
        m = (left+right)/2;
        if (myVect[m].pid < item) left = m + 1;
        else if (myVect[m].pid > item) right = m - 1;
        else return m;
    }
    return -1;
}

int binary_search_LH (const problemid& item, const vector<problemid>& myVect, int vectSize)
{
    int left = 0, right = vectSize - 1, m;
    while (left <= right)
    {
        m = (left+right)/2;
        if (myVect[m] < item) left = m + 1;
        else if (myVect[m] > item) right = m - 1;
        else return m;
    }
    return -1;   
}

int binary_search_LH (const problemid& item, const vector<BinTree<ProblemData>>& myVect, int vectSize)
{
    int left = 0, right = vectSize - 1, m;
    while (left <= right)
    {
        m = (left+right)/2;
        if (myVect[m].value().pid < item) left = m + 1;
        else if (myVect[m].value().pid > item) right = m - 1;
        else return m;
    }
    return -1;   
}

int insertion_sort_LH (const ProblemData& problemData, vector<ProblemData>& myVect, int& vectSize)
{
    myVect.insert(myVect.end(), problemData);
    ++vectSize;
    int i = vectSize - 1; 
    while(i > 0 && myVect[i - 1].pid > problemData.pid)
    {
        myVect[i] = myVect[i - 1];
        --i;
    }
    myVect[i] = problemData;
    return i;
}

int insertion_sort_LH (const BinTree<ProblemData>& problemData, vector<BinTree<ProblemData>>& myVect, int& vectSize)
{
    myVect.insert(myVect.end(), problemData);
    ++vectSize;
    int i = vectSize - 1; 
    while(i > 0 && myVect[i - 1].value().pid > problemData.value().pid)
    {
        myVect[i] = myVect[i - 1];
        --i;
    }
    myVect[i] = problemData;
    return i;
}

int insertion_sort_LH (const problemid& problemData, vector<problemid>& myVect, int& vectSize)
{
    myVect.insert(myVect.end(), problemData);
    ++vectSize;
    int i = vectSize - 1; 
    while(i > 0 && myVect[i - 1]> problemData)
    {
        myVect[i] = myVect[i - 1];
        --i;
    }
    myVect[i] = problemData;
    return i;
}


//##################################//
//      ESTRUCTURAS DE DATOS        //
//##################################//

//##################//
//  Attempts
Attempts::Attempts()
{
    total = 0;
    accepted = 0;
    rejected = 0;
}

bool Attempts::update_attempts(const bool& isCorrect)
{
    total += 1;
    if (isCorrect) accepted += 1;
    else rejected += 1;
    return isCorrect;
}

//##################//
//  ProblemData

ProblemData::ProblemData()
{
    solved = false;
}

ProblemData::ProblemData(const problemid& pid)
{
    solved = false;
    this->pid = pid;
}

bool ProblemData::solve(const bool& isSolved)
{
    solved = isSolved;
    attempts.update_attempts(isSolved);
    return solved;
}
