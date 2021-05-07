#include "sesion.hh"
#include <algorithm>
#include "tipos.hh"

using namespace std;
//######################################//
//      FUNCIONES AJENAS A LA CLASE     //
//######################################//
int read_BinTree(ProblemTree& myTree, ProblemMapNode& myMap)
{
    int sum = 0;
    problemid pid; cin >> pid;
    if (pid[0] != '0')
    {
        ProblemTree myTreeLeft;
        sum += read_BinTree(myTreeLeft, myMap);
        ProblemTree myTreeRight;
        sum += read_BinTree(myTreeRight, myMap);
        myTree = ProblemTree(pid, myTreeLeft, myTreeRight);
        myMap.insert(make_pair(pid, TreeNode(myTree)));
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

 void Sesion::get_next_problem(const problemid& pid, TreeNode& treeNode) const
 {
    treeNode = problemMap.find(pid)->second;
 }

void Sesion::get_problemTree(ProblemTree& problemTree) const
{
    problemTree = this->problemTree;
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

int Sesion::get_problems_iterator(vector<problemid>::const_iterator& beginIter, vector<problemid>::const_iterator& endIter) const
{
    problemVect.begin_iterator(beginIter);
    problemVect.end_iterator(endIter);
    return n_problems;
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
    n_problems = read_BinTree(problemTree, problemMap);
    get_problems_as_vector(problemVect);
    
}

void Sesion::write() const
{
    cout << sid << ' ' << n_problems << ' ';
    print_BinTree(problemTree);
}
