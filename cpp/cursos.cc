#include "../hh/cursos.hh"

using namespace std;

Cursos::Cursos()
{

}

const void Cursos::read()
{
    int n; cin >> n;
    total = n;
    
    courses = vector<Curso>(total);

    courseid cid;
    while (n != 0)
    {
        courses[total - n] = Curso(total - n);
        courses[total - n].read();
        --n;
    }
}