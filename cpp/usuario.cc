#include "../hh/usuario.hh"
#include <algorithm>

using namespace std;

// Funciones que no son de la clase.
bool sort_vect(ProblemData& a, ProblemData& b)
{
    return a.pid < b.pid;
}

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

// Funciones de la clase.
Usuario::Usuario()
{
    currentCourse = UserCourseData();
    hasUserid = false;
    isInscribed = false;
}

Usuario::Usuario(const userid& uid)
{
    this->uid = uid;
    currentCourse = UserCourseData();
    hasUserid = true;
    isInscribed = false;
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
    return currentCourse.identifier;
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
    // Inv: todos los *courseSessionVectorBegin pertenecen al conjunto de 'Sesiones'. courseSessionBegin++ tiende a courseSessionVectorEnd.
    while (courseSessionVectorBegin != courseSessionVectorEnd)
    {   
        // Seguro que la sesión a buscar existe.
        sessions.get_session(*courseSessionVectorBegin, sessionIter);
        // Insertamos el árbol de problemas de la sesión en el vector de árboles de problemas del usuario.
        currentCourse.problemTreeVector.push_back(sessionIter->second.get_problemTree());
        ++currentCourse.num_problemTree;
        ++courseSessionVectorBegin;
    }
    // Seguro que se ha inscrito.
    isInscribed = true;
    return true; 
}

int Usuario::available_problems(vector<ProblemData>& problemVect) const
{
    // Si no está inscrito a ningún curso, no es posible listar problemas a enviar (tenga o no).
    if (!isInscribed) return -1;

    // Los problemas a enviar son aquellos que no han sido solucionados y que son precedidos por problemas solucionados
    // Por defecto, el primer problema de una sesión se puede enviar. 
    // Inv: cada iteración incrementa el tamaño de problemVect.
    for (int i = 0; i < currentCourse.num_problemTree; ++i)
    {
        // Se insertan detras de problemVect los problemas a solucionar del problemTreeVector[i].
        get_session_available_problems(currentCourse.problemTreeVector[i], problemVect);
    }
    // Ordenamos el vector de problemas crecientemente.
    sort(problemVect.begin(), problemVect.end(), sort_vect);
    // El tamaño del vector se devuelve para poder iterar sobre él.
    int size = problemVect.size();  // Optimizar
    return size;
}

void Usuario::write() const
{
    cout << uid << '(' << allCourses.attempts.total;
    cout << ',' << allCourses.attempts.accepted << ',' << allCourses.attempts.unique << ',';
    cout << ((isInscribed) ? currentCourse.identifier : 0) << ')';
}


// void Usuario::print_all_time_solved_problems() const
// {
//     int i = 0;
//     for (i = 0; i < allCourses.sizeCoursesVect - 1; ++i)
//     {
//         cout << allCourses.coursesVect[i].pid << ' ';
//     }
//     if (allCourses.sizeCoursesVect != 0) cout << allCourses.coursesVect[i].pid << endl;
// }