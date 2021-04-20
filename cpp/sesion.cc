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

Sesion::Sesion()
{
    
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

const void Sesion::cout_sid() const
{
    cout << sid;
}