#include "cursos.hh"

using namespace std;

Curso Cursos::nullCourse = Curso();

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

Curso& Cursos::get_course(const courseid& cid)
{
    if (cid <= 0 or cid > total) return nullCourse;
    return *(courseVector.begin() + cid - 1);
}

void Cursos::read()
{
    int n; cin >> n;
    total = n;
    
    courseVector = CourseVector(total);

    while (n != 0)
    {
        courseVector[total - n] = Curso(total - n + 1);
        courseVector[total - n].read();
        
        --n;
    }
}