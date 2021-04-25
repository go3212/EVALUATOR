#include "../hh/usuario.hh"
#include <algorithm>

using namespace std;

Usuario::Usuario()
{
    currentCourse = UserCourseData();
    hasUserid = false;
    isInscribed = false;
}

void Usuario::print_all_time_solved_problems() const
{
    int i = 0;
    for (i = 0; i < allCourses.sizeCoursesVect - 1; ++i)
    {
        cout << allCourses.coursesVect[i].pid << ' ';
    }
    if (allCourses.sizeCoursesVect != 0) cout << allCourses.coursesVect[i].pid << endl;
}

bool sort_vect(ProblemData& a, ProblemData& b)
{
    return a.pid < b.pid;
}

/**
 *  \pre Al menos hay un nodo. 
 *  \post Devuelve los elementos no solucionados adyacenetes a nodos solucionados.
 */

void get_session_available_problems(const BinTree<ProblemData>& problemTree, vector<ProblemData>& problemVector)
{
    // Un problema tiene posibilidad de envio si, y solo si, su anterior problema (en la rama) ha sido solucionado, se
    // considera que la raíz (la primera) siempre es solucionable.
    if (!problemTree.value().solved) 
    {
        problemVector.push_back(problemTree.value()); 
        return void();
    }
    BinTree<ProblemData> left = problemTree.left(), right = problemTree.right();
    if (!left.empty())
    {
        if (left.value().solved) get_session_available_problems(left, problemVector);
        else problemVector.push_back(left.value());
    }
    if (!right.empty())
    {
        if (right.value().solved) get_session_available_problems (right, problemVector);
        else problemVector.push_back(right.value());
    }
}

int Usuario::available_problems(vector<ProblemData>& problemVect) const
{
    // Si no está inscrito a ningún curso, no es posible listar problemas a enviar (tenga o no).
    if (!isInscribed) return -1;

    // Los problemas a enviar son aquellos que no han sido solucionados y que son precedidos por problemas solucionados
    // Por defecto, el primer problema de una sesión se puede enviar. 
    for (int i = 0; i < currentCourse.num_problemTree; ++i)
    {
        get_session_available_problems(currentCourse.problemTreeVector[i], problemVect);
    }
    sort(problemVect.begin(), problemVect.end(), sort_vect);
    int size = problemVect.size();  // Optimizar
    return size;
}

bool Usuario::inscribe(const courseid& cid, const Curso& course, Sesiones& sessions)
{
    // Si el usuario ya está inscrito, no se puede volver a inscribir.
    if (isInscribed) return false;
    // En cualquier otro caso, iniciar proceso de inscripción.
    currentCourse = UserCourseData(cid);

    // Primero inicializamos los iteradores del vector de sesiones que pertenecen al curso.
    CourseSessionVector::const_iterator courseSessionVectorBegin, courseSessionVectorEnd;
    course.get_iterators(courseSessionVectorBegin, courseSessionVectorEnd);

    // Incializamos los iteradores de sesion previamente por eficiencia.
    SessionMap::const_iterator sessionIter;
    while (courseSessionVectorBegin != courseSessionVectorEnd)
    {   
        sessions.get_session(*courseSessionVectorBegin, sessionIter);
        currentCourse.problemTreeVector.push_back(sessionIter->second.get_problemTree());
        ++currentCourse.num_problemTree;
        ++courseSessionVectorBegin;
    }

    isInscribed = true;
    return true; 
}

bool Usuario::is_inscribed() const
{
    return isInscribed;
}

courseid Usuario::inscribed_course_id() const
{
    return currentCourse.identifier;
}

void Usuario::write() const
{
    cout << uid << '(' << allCourses.attempts.total;
    cout << ',' << allCourses.attempts.accepted << ',' << allCourses.attempts.unique << ',';
    cout << ((isInscribed) ? currentCourse.identifier : 0) << ')';
}

Usuario::Usuario(const userid& uid)
{
    this->uid = uid;
    currentCourse = UserCourseData();
    hasUserid = true;
    isInscribed = false;
}