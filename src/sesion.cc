#include "sesion.hh"
#include <algorithm>

using namespace std;
//######################################//
//      FUNCIONES AJENAS A LA CLASE     //
//######################################//
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
        myTree = ProblemTree(pid, myTreeLeft, myTreeRight);
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
        cout << myTree.value() << ')';
    }
}

void vectorize_BinTree(ProblemVector& myVect, const ProblemTree& myTree)
{   
    if (myTree.empty()) return void();
    myVect.push_back(myTree.value());
    ProblemTree myTreeLeft = myTree.left();
    ProblemTree myTreeRight = myTree.right();
    if(!myTreeLeft.empty()) vectorize_BinTree (myVect, myTreeLeft);
    if(!myTreeRight.empty())  vectorize_BinTree(myVect, myTreeRight);

    return void();
}

void userBinTreeTransform(BinTree<ProblemData>& copyBinTree, const ProblemTree& binTree)
{
    if (binTree.empty()) return void();
    BinTree<ProblemData> copyBinTreeLeft, copyBinTreeRight;

    userBinTreeTransform(copyBinTreeLeft, binTree.left());
    userBinTreeTransform(copyBinTreeRight, binTree.right());

    copyBinTree = BinTree<ProblemData>(ProblemData(binTree.value_cpy()), copyBinTreeLeft, copyBinTreeRight);
}

//######################################//
//        FUNCIONES DE A LA CLASE       //
//######################################//
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

BinTree<ProblemData> Sesion::get_problemTree() const
{
    BinTree<ProblemData> copyBinTree;
    userBinTreeTransform (copyBinTree, problemTree);
    return copyBinTree;
}   

int Sesion::get_problems_as_vector(ProblemVector& pidVect) const
{
    // Hay que solucionar la asignacion de vectores.
    // pidVect = ProblemVector(n_problems);
    vectorize_BinTree(pidVect, problemTree);
    return n_problems;
}

bool Sesion::has_problem(const problemid& pid) const
{
    return ((problemVect.find(pid) != -1) ? true : false);
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
