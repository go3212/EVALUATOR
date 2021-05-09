#include "sesion.hh"

using namespace std;

//######################################//
//     MÉTODOS PRIVADOS DE LA CLASE     //
//######################################//
int Sesion::read_problemTree(ProblemTree& problemTree)
{
    int sum = 0;
    problemid pid; cin >> pid;
    if (pid[0] == '0') return sum;
    ProblemTree myTreeLeft;
    sum += read_problemTree(myTreeLeft);
    ProblemTree myTreeRight;
    sum += read_problemTree(myTreeRight);
    problemTree = ProblemTree(pid, myTreeLeft, myTreeRight);
    return 1 + sum;
}

void Sesion::print_problemTree(const ProblemTree& problemTree) const
{
    if (problemTree.empty()) return void();
    cout << '(';
    ProblemTree myTreeLeft = problemTree.left();
    print_problemTree(myTreeLeft);
    ProblemTree myTreeRight = problemTree.right();
    print_problemTree(myTreeRight);
    cout << problemTree.value() << ')';
    return void();
}

void Sesion::vectorize_problemTree(ProblemVector& problemVect, const ProblemTree& problemTree) const
{   
    if (problemTree.empty()) return void();
    problemVect.push_back(problemTree.value());
    ProblemTree myTreeLeft = problemTree.left();
    ProblemTree myTreeRight = problemTree.right();
    if(!myTreeLeft.empty()) vectorize_problemTree (problemVect, myTreeLeft);
    if(!myTreeRight.empty())  vectorize_problemTree(problemVect, myTreeRight);
    return void();
}

//######################################//
//    MÉTODOS PÚBLICOS DE A LA CLASE    //
//######################################//
Sesion::Sesion() 
{
    hasSessionid = false;
    numProblems = 0;
}

Sesion::Sesion(const sessionid& sid)
{
    this->sid = sid;
    hasSessionid = true;
    numProblems = read_problemTree(problemTree);
    get_problems_as_vector(problemVect);
}

bool Sesion::has_problem(const problemid& pid) const
{
    return ((problemVect.find(pid) != -1) ? true : false);
}

sessionid Sesion::get_sessionid() const
{
    return sid;
}

int Sesion::get_problems (ProblemVector& pidVector) const
{
    pidVector = problemVect;
    return numProblems;
}

int Sesion::get_number_of_problems() const
{
    return numProblems;
}

int Sesion::get_problems_as_vector(ProblemVector& pidVect) const
{
    // Hay que solucionar la asignacion de vectores.
    // pidVect = ProblemVector(numProblems);
    vectorize_problemTree(pidVect, problemTree);
    return numProblems;
}

const BinTree<problemid>& Sesion::get_problemTree() const
{
    return problemTree;
}

int Sesion::get_problem_vector_iterators(vector<problemid>::const_iterator& beginIter, vector<problemid>::const_iterator& endIter) const
{
    problemVect.begin_iterator(beginIter);
    problemVect.end_iterator(endIter);
    return numProblems;
}

void Sesion::read()
{
    cin >> sid;
    hasSessionid = true;
    numProblems = read_problemTree(problemTree);
    get_problems_as_vector(problemVect);
}

void Sesion::write() const
{
    cout << sid << ' ' << numProblems << ' ';
    print_problemTree(problemTree);
}
