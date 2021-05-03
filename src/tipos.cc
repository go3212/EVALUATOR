#include "../hh/tipos.hh"


const int binary_search_LH (const problemid& item, const vector<ProblemData>& myVect, int vectSize)
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