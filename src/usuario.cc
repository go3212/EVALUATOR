#include "usuario.hh"

using namespace std;

//######################################//
//        FUNCIONES DE A LA CLASE       //
//######################################//
Usuario::Usuario() : uid(), isNull(true), isInscribed(false) {}

Usuario::Usuario(const userid& uid) : uid(uid), isNull(false), isInscribed(false) {}

bool Usuario::is_null() const
{
    return isNull;
}

void Usuario::force_uninscribe(Cursos& courses)
{
    courseManager.force_uninscribe(courses);
}

bool Usuario::is_inscribed() const
{
    return isInscribed;
}

courseid Usuario::inscribed_course_id() const
{
    return courseManager.current_course_id();
}

bool Usuario::inscribe(Curso& course, Sesiones& sessions)
{
    // Primero miramos si el usuario está inscrito en un curso:
    if (isInscribed) return false;

    // Ahora, seguro que el usuario se puede inscribir. 
    courseManager.inscribe(course, sessions);

    // Si el usuario no tiene problemas a solucionar, ha acabado el curso.
    isInscribed = true;
    if (courseManager.course_finished()) isInscribed = false;
    return true; 
}

bool Usuario::update_problem(const problemid& pid, const bool& isSolved, Cursos& courses)
{
    courseManager.send_attempt(pid, isSolved);
    if (courseManager.course_finished()) courseManager.uninscribe(courses), isInscribed = false;
    return true;
}

void Usuario::print_available_problems() const
{
    courseManager.print_available_problems();
}

int Usuario::print_all_time_solved_problems()
{
    courseManager.print_solved_problems();
    return true;
}

void Usuario::write() const
{
    cout << uid;
    courseManager.print_course_info();
}