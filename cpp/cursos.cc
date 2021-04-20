#include "../hh/cursos.hh"

using namespace std;

Cursos::Cursos()
{

}

void Cursos::get_iterators(vector<Curso>::const_iterator& myBeginIterator, vector<Curso>::const_iterator& myEndIterator) const
{
    myBeginIterator = courses.begin();
    myEndIterator = courses.end();
}

const bool Cursos::get_course(const courseid& cid, vector<Curso>::const_iterator& myIter) const
{
    if (cid != 0 and cid <= total)
    {
        myIter = courses.begin() + cid - 1;
        return true;
    }
    return false;
   
}

const void Cursos::read()
{
    int n; cin >> n;
    total = n;
    
    courses = vector<Curso>(total);

    courseid cid;
    while (n != 0)
    {
        courses[total - n] = Curso(total - n + 1);
        courses[total - n].read();
        --n;
    }
}