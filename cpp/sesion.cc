#include "../hh/sesion.hh"

using namespace std;

void read_BinTree(BinTree<problemid>& myTree)
{
    problemid pid; cin >> pid;
    if (pid[0] != '0')
    {
        BinTree<problemid> myTreeLeft;
        read_BinTree(myTreeLeft);
        BinTree<problemid> myTreeRight;
        read_BinTree(myTreeRight);
        myTree = BinTree<problemid>(pid, myTreeLeft, myTreeRight);
    }
}

void print_BinTree(BinTree<problemid>& myTree)
{
    if (!myTree.empty())
    {
        cout << myTree.value() << ' ';
        BinTree<problemid> myTreeLeft = myTree.left();
        print_BinTree(myTreeLeft);
        BinTree<problemid> myTreeRight = myTree.right();
        print_BinTree(myTreeRight);
    }
}

Sesion::Sesion()
{
    
}

Sesion::Sesion(const sessionid& sid)
{
    this->sid = sid;
    hasSessionid = true;
    read_BinTree(problems);
}

const void Sesion::write()
{
    print_BinTree(problems);
}

