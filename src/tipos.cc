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

int insertion_sort_LH (const ProblemData& problemData, vector<ProblemData>& myVect, int& vectSize)
{
    myVect.push_back(problemData);
    ++vectSize;
    int i = vectSize - 1; 
    ProblemData temp;
    while(i > 0 && myVect[i - 1].pid > myVect[i].pid)
    {
        temp = myVect[i - 1];
        myVect[i - 1] = myVect[i];
        myVect[i] = temp;
        --i;
    }
    return i;
}

int insertion_sort_LH (const problemid& problemData, vector<problemid>& myVect, int& vectSize)
{
    myVect.push_back(problemData);
    ++vectSize;
    int i = vectSize - 1; 
    problemid temp;
    while(i > 0 && myVect[i - 1]> myVect[i])
    {
        temp = myVect[i - 1];
        myVect[i - 1] = myVect[i];
        myVect[i] = temp;
        --i;
    }
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
