#include "usuario.hh"

using namespace std;

//######################################//
//      FUNCIONES AJENAS A LA CLASE     //
//######################################//
bool sort_vect(ProblemData& a, ProblemData& b)
{
    return a.pid < b.pid;
}

void write_data (const ProblemData& problemData)
{
    cout << problemData.pid;
    cout << '(' << problemData.attempts.total << ')';
    cout << endl;
}

void print_session_available_problems(const BinTree<ProblemData>& problemTree)
{
    // Un problema tiene posibilidad de envio si, y solo si, su anterior problema (en la rama) ha sido solucionado, se
    // considera que la raíz (la primera) siempre es solucionable.
    
    if (!problemTree.value().solved) // El único caso que puede entrar (o no) en este condicional es el primero.
    {
        write_data(problemTree.value());
        return void(); // No hau que revisar más.
    }
    BinTree<ProblemData> left = problemTree.left(), right = problemTree.right();
    // Para cumplir la precondición, en la recursividad solo se pueden pasar árboles no vacíos.
    if (!left.empty())
    {   
        // Si el problema de la izquierda está solucionado, hay que verificar recursivamente si sus hijos
        // son problemas a solucionar o no. Si no está solucionado, sus hijos no son solucionables.
        if (left.value().solved) print_session_available_problems(left);
        else write_data(left.value()); 
    }
    if (!right.empty())
    {
        // Si el problema de la izquierda está solucionado, hay que verificar recursivamente si sus hijos
        // son problemas a solucionar o no. Si no está solucionado, sus hijos no son solucionables.
        if (right.value().solved) print_session_available_problems (right);
        else write_data(right.value()); 
    }
}

//######################################//
//        FUNCIONES DE A LA CLASE       //
//######################################//

Usuario::Usuario()
{
    hasUserid = false;
    isInscribed = false;
    courseManager = CourseManager();
}

Usuario::Usuario(const userid& uid)
{
    this->uid = uid;
    hasUserid = true;
    isInscribed = false;
    courseManager = CourseManager();
}

Usuario::~Usuario()
{

}

bool Usuario::has_userid() const
{
    return hasUserid;
}

bool Usuario::is_inscribed() const
{
    return isInscribed;
}

courseid Usuario::inscribed_course_id() const
{
    return courseManager.current_course_id();
}

bool Usuario::inscribe(const courseid& cid, const CourseVector::iterator& courseIter, Sesiones& sessions)
{
    // Primero miramos si el usuario está inscrito en un curso:
    if (isInscribed) return false;

    // Ahora, seguro que el usuario se puede inscribir. 
    courseManager.inscribe(courseIter, sessions);

    // Si el usuario no tiene problemas a solucionar, ha acabado el curso.
    if (courseManager.course_finished()) return false;
    isInscribed = true;
    return true; 
}

bool Usuario::update_problem(const problemid& pid, const bool& isSolved)
{
    courseManager.send_attempt(pid, isSolved);
    if (courseManager.course_finished()) courseManager.uninscribe(), isInscribed = false;
    return true;
}

void Usuario::print_available_problems() const
{
    courseManager.print_available_problems();
}

bool sort_LH_2 (ProblemData& a, ProblemData& b)
{
    return a.pid < b.pid;
}

int Usuario::print_all_time_solved_problems()
{
    courseManager.print_solved_problems();
    return true;
}

void Usuario::write() const
{
    cout << uid;
    courseManager.write();
}