#include "usuario.hh"

using namespace std;

//######################################//
//      FUNCIONES AJENAS A LA CLASE     //
//######################################//
bool sort_vect(ProblemData& a, ProblemData& b)
{
    return a.pid < b.pid;
}

void get_session_available_problems(const BinTree<ProblemData>& problemTree, vector<ProblemData>& problemVector)
{
    // Un problema tiene posibilidad de envio si, y solo si, su anterior problema (en la rama) ha sido solucionado, se
    // considera que la raíz (la primera) siempre es solucionable.
    
    if (!problemTree.value().solved) // El único caso que puede entrar (o no) en este condicional es el primero.
    {
        problemVector.push_back(problemTree.value()); 
        return void(); // No hau que revisar más.
    }
    BinTree<ProblemData> left = problemTree.left(), right = problemTree.right();
    // Para cumplir la precondición, en la recursividad solo se pueden pasar árboles no vacíos.
    if (!left.empty())
    {   
        // Si el problema de la izquierda está solucionado, hay que verificar recursivamente si sus hijos
        // son problemas a solucionar o no. Si no está solucionado, sus hijos no son solucionables.
        if (left.value().solved) get_session_available_problems(left, problemVector);
        else problemVector.push_back(left.value());
    }
    if (!right.empty())
    {
        // Si el problema de la izquierda está solucionado, hay que verificar recursivamente si sus hijos
        // son problemas a solucionar o no. Si no está solucionado, sus hijos no son solucionables.
        if (right.value().solved) get_session_available_problems (right, problemVector);
        else problemVector.push_back(right.value());
    }
}

//######################################//
//        FUNCIONES DE A LA CLASE       //
//######################################//
Usuario::Usuario()
{
    currentCourse = UserCourseData();
    allCourses = UserCoursesData();
    hasUserid = false;
    isInscribed = false;
}

Usuario::Usuario(const userid& uid)
{
    this->uid = uid;
    currentCourse = UserCourseData();
    allCourses = UserCoursesData();
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
    //int numCourses = course.get_number_of_sessions();
    //currentCourse.problemTreeVector = vector<BinTree<ProblemData>>(numCourses);
    // Incializamos los iteradores de sesion previamente por eficiencia.
    SessionMap::const_iterator sessionIter;

    // Inv: todos los *courseSessionVectorBegin pertenecen al conjunto de 'Sesiones'. courseSessionBegin++ tiende a courseSessionVectorEnd.
    while (courseSessionVectorBegin != courseSessionVectorEnd)
    {   
        // Seguro que la sesión a buscar existe.
        sessions.get_session(*courseSessionVectorBegin, sessionIter);
        // Para cada problema del árbol, tenemos que revisar si ha sido solucionado o no.
        // [BORRAR] BinTree<ProblemData> problemTree = sessionIter->second.get_problemTree();
        // Insertamos el árbol de problemas de la sesión en el vector de árboles de problemas del usuario.
        //currentCourse.problemTreeVector[currentCourse.sizeProblemTreeVector] = sessionIter->second.get_problemTree();
        currentCourse.problemTreeVector.push_back(sessionIter->second.get_problemTree());
        //[NOTA] QUIZAS MEJOR HACER UNA FUNCION FETCH??
        currentCourse.numProblems += sessionIter->second.get_number_of_problems();
        ++currentCourse.sizeProblemTreeVector;
        ++courseSessionVectorBegin;
    }
    currentCourse.fetch_solved_problems(allCourses);
    // Seguro que se ha inscrito.
    isInscribed = true;
    if (currentCourse.notsolved_problems() == 0) isInscribed = false;
    return true; 
}

bool Usuario::update_problem(const problemid& pid, const bool& isSolved)
{

    // Asumimos que el problema siempre existe, actualizamos toda su información, la información del problema actual es problemData.
    ProblemData problemData = currentCourse.update_data (pid, isSolved);
    allCourses.update_attempts (problemData, isSolved);

    // Si el usuario ha completado todos los problemas, se desinscribe del curso.
    if (currentCourse.notsolved_problems() == 0) isInscribed = false;
    return isSolved;
}

//[FUNCION CRITICA PARA OPTIMIZAR]
int Usuario::available_problems(vector<ProblemData>& problemVect) const
{
    // Si no está inscrito a ningún curso, no es posible listar problemas a enviar (tenga o no).
    if (!isInscribed) return -1;

    // Los problemas a enviar son aquellos que no han sido solucionados y que son precedidos por problemas solucionados
    // Por defecto, el primer problema de una sesión se puede enviar. 
    // Inv: cada iteración incrementa el tamaño de problemVect.
    for (int i = 0; i < currentCourse.sizeProblemTreeVector; ++i)
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

int Usuario::print_all_time_solved_problems() const
{
    int i = 0;
    for (i = 0; i < allCourses.sizeCoursesVect - 1; ++i)
    {
        cout << allCourses.coursesVect[i].pid << "(" << allCourses.coursesVect[i].attempts.total << ")" << endl;
    }
    if (allCourses.sizeCoursesVect != 0) cout << allCourses.coursesVect[i].pid << "(" << allCourses.coursesVect[i].attempts.total << ")" ;
    return allCourses.sizeCoursesVect;
}

void Usuario::write() const
{
    cout << uid << '(' << allCourses.attempts.total;
    cout << ',' << allCourses.attempts.accepted << ',' << allCourses.unique_attempts << ',';
    cout << ((isInscribed) ? currentCourse.identifier : 0) << ')';
}