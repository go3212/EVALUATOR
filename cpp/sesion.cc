#include "../hh/sesion.hh"

using namespace std;

int read_BinTree(BinTree<problemid>& myTree)
{
    int sum = 0;
    problemid pid; cin >> pid;
    if (pid[0] != '0')
    {
        BinTree<problemid> myTreeLeft;
        sum += read_BinTree(myTreeLeft);
        BinTree<problemid> myTreeRight;
        sum += read_BinTree(myTreeRight);
        myTree = BinTree<problemid>(pid, myTreeLeft, myTreeRight);
        return 1 + sum;
    }
    return sum;

}

void print_BinTree(const BinTree<problemid>& myTree)
{
    if (!myTree.empty())
    {
        cout << '(';
        BinTree<problemid> myTreeLeft = myTree.left();
        print_BinTree(myTreeLeft);
        BinTree<problemid> myTreeRight = myTree.right();
        print_BinTree(myTreeRight);
        cout << myTree.value() << ')';
    }
}

void vectorize_BinTree(int& i, vector<problemid>& myVect, const BinTree<problemid>& myTree)
{
    myVect[i] = myTree.value();
    BinTree<problemid> myTreeLeft = myTree.left();
    BinTree<problemid> myTreeRight = myTree.right();
    if(!myTreeLeft.empty()) vectorize_BinTree (++i, myVect, myTreeLeft);
    if(!myTreeRight.empty()) vectorize_BinTree (++i, myVect, myTreeRight);
}

int vectorize_BinTree(vector<problemid>& myVect, const BinTree<problemid>& myTree)
{   
    int i = 0;
    if (myTree.empty()) return 0;
    myVect[i] = myTree.value();
    BinTree<problemid> myTreeLeft = myTree.left();
    BinTree<problemid> myTreeRight = myTree.right();
    if(!myTreeLeft.empty()) vectorize_BinTree (++i, myVect, myTreeLeft);
    if(!myTreeRight.empty())  vectorize_BinTree(++i, myVect, myTreeRight);

    return 1 + i;
}

Sesion::Sesion()
{
    
}

const int Sesion::get_number_of_problems() const
{
    return n_problems;
}

const int Sesion::get_problems_as_vector(vector<problemid>& pidVect) const
{
    pidVect = vector<problemid>(n_problems);
    return vectorize_BinTree(pidVect, problems);;
}

Sesion::Sesion(const sessionid& sid)
{
    this->sid = sid;
    hasSessionid = true;
    n_problems = read_BinTree(problems);
}

const void Sesion::write() const
{
    cout << sid << ' ' << n_problems << ' ';
    print_BinTree(problems);
}