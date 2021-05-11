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

void Sesion::vectorize_problemTree(ProblemVector& problemVect, const ProblemTree& problemTree, int& index) const
{   
    if (problemTree.empty()) return void();
    problemVect[index] = problemTree.value();
    ProblemTree myTreeLeft = problemTree.left();
    ProblemTree myTreeRight = problemTree.right();
    if(!myTreeLeft.empty()) vectorize_problemTree (problemVect, myTreeLeft, ++index);
    if(!myTreeRight.empty()) vectorize_problemTree(problemVect, myTreeRight, ++index);
    return void();
}

//######################################//
//    MÉTODOS PÚBLICOS DE A LA CLASE    //
//######################################//
Sesion::Sesion() 
{
    isNull = true;
    numProblems = 0;
}

Sesion::Sesion(const sessionid& sid)
{
    isNull = false;
    numProblems = read_problemTree(problemTree);

    this->sid = sid;
    get_problems_as_vector(problemVect);
    sort (problemVect.begin(), problemVect.end());
}

bool Sesion::has_problem(const problemid& pid) const
{
    // Nos garantizan que el vector está ordenado, realizamos busqueda binaria.
    int left = 0, right = numProblems - 1, m;
    while (left <= right)
    {   
        m = (left+right)/2;
        if (problemVect[m] < pid) left = m + 1;
        else if (problemVect[m] > pid) right = m - 1;
        else break;  // Si lo entontramos, salimos del bucle.
    }
    // Si salimos prematuramente del bucle -> left <= right, si no salimos -> left > right. 
    return ((left <= right) ? true : false);
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

bool Sesion::is_null() const
{
    return isNull;
}

int Sesion::get_number_of_problems() const
{
    return numProblems;
}

int Sesion::get_problems_as_vector(ProblemVector& pidVect) const
{
    int index = 0;
    pidVect = ProblemVector(numProblems);
    vectorize_problemTree(pidVect, problemTree, index);
    return numProblems;
}

const BinTree<problemid>& Sesion::get_problemTree() const
{
    return problemTree;
}

const ProblemVector& Sesion::get_problem_vector() const
{
    return problemVect;
}

void Sesion::read()
{
    cin >> sid;
    isNull = false;
    numProblems = read_problemTree(problemTree);
    get_problems_as_vector(problemVect);
    sort (problemVect.begin(), problemVect.end());
}

void Sesion::write() const
{
    cout << sid << ' ' << numProblems << ' ';
    print_problemTree(problemTree);
}
