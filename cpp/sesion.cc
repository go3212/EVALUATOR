#include "../hh/sesion.hh"
#include <algorithm>

using namespace std;

int read_BinTree(ProblemTree& myTree)
{
    int sum = 0;
    problemid pid; cin >> pid;
    if (pid[0] != '0')
    {
        ProblemTree myTreeLeft;
        sum += read_BinTree(myTreeLeft);
        ProblemTree myTreeRight;
        sum += read_BinTree(myTreeRight);
        myTree = ProblemTree(ProblemData(pid), myTreeLeft, myTreeRight);
        return 1 + sum;
    }
    return sum;

}

void print_BinTree(const ProblemTree& myTree)
{
    if (!myTree.empty())
    {
        cout << '(';
        ProblemTree myTreeLeft = myTree.left();
        print_BinTree(myTreeLeft);
        ProblemTree myTreeRight = myTree.right();
        print_BinTree(myTreeRight);
        cout << myTree.value().pid << ')';
    }
}

void vectorize_BinTree(int& i, ProblemVector& myVect, const ProblemTree& myTree)
{
    myVect[i] = myTree.value().pid;
    ProblemTree myTreeLeft = myTree.left();
    ProblemTree myTreeRight = myTree.right();
    if(!myTreeLeft.empty()) vectorize_BinTree (++i, myVect, myTreeLeft);
    if(!myTreeRight.empty()) vectorize_BinTree (++i, myVect, myTreeRight);
}

int vectorize_BinTree(ProblemVector& myVect, const ProblemTree& myTree)
{   
    int i = 0;
    if (myTree.empty()) return 0;
    myVect[i] = myTree.value().pid;
    ProblemTree myTreeLeft = myTree.left();
    ProblemTree myTreeRight = myTree.right();
    if(!myTreeLeft.empty()) vectorize_BinTree (++i, myVect, myTreeLeft);
    if(!myTreeRight.empty())  vectorize_BinTree(++i, myVect, myTreeRight);

    return 1 + i;
}

Sesion::Sesion()
{
    
}

sessionid Sesion::session_id() const
{
    return sid;
}

int Sesion::get_number_of_problems() const
{
    return n_problems;
}

ProblemTree Sesion::get_problemTree() const
{
    return problemTree;
}   

int Sesion::get_problems_as_vector(ProblemVector& pidVect) const
{
    pidVect = ProblemVector(n_problems);
    return vectorize_BinTree(pidVect, problemTree);;
}

bool Sesion::has_problem(const problemid& pid) const
{
    return ((problemVect.find(pid) == -1) ? false : true);
}

int Sesion::get_problems (ProblemVector& pidVector) const
{
    pidVector = problemVect;
    return n_problems;
}

Sesion::Sesion(const sessionid& sid)
{
    this->sid = sid;
    hasSessionid = true;
    n_problems = read_BinTree(problemTree);
    get_problems_as_vector(problemVect);
    
}

void Sesion::write() const
{
    cout << sid << ' ' << n_problems << ' ';
    print_BinTree(problemTree);
}