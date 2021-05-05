#include "cursos.hh"

using namespace std;

Cursos::Cursos()
{
    total = 0;
    courseVector = CourseVector();
}

int Cursos::get_number_of_courses() const
{
    return total;
}

bool Cursos::add_course(Curso& course)
{
    // Añadimos el curso al final del vector de cursos.
    courseVector.insert(courseVector.end(), course);
    // Aumentamos el tamaño del vector de cursos y asignamos el identificador correspondiente al 
    // nuevo curso.
    total += 1;
    courseVector[total - 1].set_cid(total);
    return true;
}

void Cursos::get_iterators(CourseVector::const_iterator& beginIterator, CourseVector::const_iterator& endIterator) const
{
    beginIterator = courseVector.begin();
    endIterator = courseVector.end();
}

bool Cursos::get_course(const courseid& cid, CourseVector::iterator& vectorIter)
{
    if (cid <= 0 or cid > total) return false;

    vectorIter = courseVector.begin() + cid - 1;
    return true;
}

void Cursos::read(const Sesiones& sessions)
{
    int n; cin >> n;
    total = n;
    
    courseVector = CourseVector(total);

    //courseid cid;
    while (n != 0)
    {
        courseVector[total - n] = Curso(total - n + 1);
        courseVector[total - n].read(sessions);
        
        --n;
    }
}

void Cursos::read()
{
    int n; cin >> n;
    total = n;
    
    courseVector = CourseVector(total);

    //courseid cid;
    while (n != 0)
    {
        courseVector[total - n] = Curso(total - n + 1);
        courseVector[total - n].read();
        
        --n;
    }
}