#include "../hh/cursos.hh"

using namespace std;

Cursos::Cursos()
{
    total = 0;
    courseVector = CourseVector(0);
}

bool Cursos::add_course(Curso& course)
{
    courseVector.push_back(course);
    total += 1;
    courseVector[total - 1].set_cid(total);
    return true;
}

int Cursos::get_number_of_courses() const
{
    return total;
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