#include "usuario.hh"

using namespace std;

//######################################//
//      FUNCIONES AJENAS A LA CLASE     //
//######################################//
bool sort_vect(ProblemData& a, ProblemData& b)
{
    return a.pid < b.pid;
}

// void get_session_available_problems(const BinTree<pair<problemid, bool>>& problemTree, int& size, vector<ProblemData>& problemVector)
// {
//     // Un problema tiene posibilidad de envio si, y solo si, su anterior problema (en la rama) ha sido solucionado, se
//     // considera que la raíz (la primera) siempre es solucionable.
    
//     if (!problemTree.value().second) // El único caso que puede entrar (o no) en este condicional es el primero.
//     {
//         problemVector.insert(problemVector.end(), ProblemData(problemTree.value().first));
//         ++size; 
//         return void(); // No hau que revisar más.
//     }
//     BinTree<pair<problemid, bool>> left = problemTree.left(), right = problemTree.right();
//     // Para cumplir la precondición, en la recursividad solo se pueden pasar árboles no vacíos.
//     if (!left.empty())
//     {   
//         // Si el problema de la izquierda está solucionado, hay que verificar recursivamente si sus hijos
//         // son problemas a solucionar o no. Si no está solucionado, sus hijos no son solucionables.
//         if (left.value().second) get_session_available_problems(left, size, problemVector);
//         else problemVector.insert(problemVector.end(), ProblemData(left.value()), ++size; 
//     }
//     if (!right.empty())
//     {
//         // Si el problema de la izquierda está solucionado, hay que verificar recursivamente si sus hijos
//         // son problemas a solucionar o no. Si no está solucionado, sus hijos no son solucionables.
//         if (right.value().second) get_session_available_problems (right, size, problemVector);
//         else problemVector.insert(problemVector.end(), right.value()), ++size; 
//     }
// }

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

bool Usuario::inscribe(const courseid& cid, const CourseVector::iterator& courseIter, Sesiones& sessions)
{
    // Si el usuario ya está inscrito, no se puede volver a inscribir.
    if (isInscribed) return false;
    // En cualquier otro caso, iniciar proceso de inscripción.
    currentCourse = UserCourseData(cid);
    currentCourse.courseIter = courseIter;

    // Primero inicializamos los iteradores del vector de sesiones que pertenecen al curso.
    CourseSessionVector::const_iterator courseSessionVectorBegin, courseSessionVectorEnd;
    int numCourses = courseIter->get_iterators(courseSessionVectorBegin, courseSessionVectorEnd);
    currentCourse.problemTreeVector = vector<BinTree<pair<problemid, bool>>>(numCourses);
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
        sessionIter->second.get_problemTree(currentCourse.problemTreeVector[currentCourse.sizeProblemTreeVector]);
        //[NOTA] QUIZAS MEJOR HACER UNA FUNCION FETCH??
        currentCourse.numProblems += sessionIter->second.get_number_of_problems();
        ++currentCourse.sizeProblemTreeVector;
        ++courseSessionVectorBegin;
    }
    currentCourse.fetch_solved_problems(allCourses);
    // Seguro que se ha inscrito.
    isInscribed = true;
    if (currentCourse.notsolved_problems() == 0) isInscribed = false;

    courseIter->inscribe_user();

    return true; 
}

bool Usuario::update_problem(const problemid& pid, const bool& isSolved)
{

    // Asumimos que el problema siempre existe, actualizamos toda su información, la información del problema actual es problemData.
    ProblemData problemData;
    currentCourse.update_data (pid, problemData, isSolved);
    allCourses.update_attempts (problemData, isSolved);

    // Si el usuario ha completado todos los problemas, se desinscribe del curso.
    if (currentCourse.notsolved_problems() == 0) isInscribed = false;
    currentCourse.courseIter->update_problem(isInscribed);
    return isSolved;
}

// //[FUNCION CRITICA PARA OPTIMIZAR]
// int Usuario::available_problems(vector<ProblemData>& problemVect) const
// {
//     // Si no está inscrito a ningún curso, no es posible listar problemas a enviar (tenga o no).
//     if (!isInscribed) return -1;

//     // Los problemas a enviar son aquellos que no han sido solucionados y que son precedidos por problemas solucionados
//     // Por defecto, el primer problema de una sesión se puede enviar. 
//     // Inv: cada iteración incrementa el tamaño de problemVect.
//     int size = 0;
//     for (int i = 0; i < currentCourse.sizeProblemTreeVector; ++i)
//     {
//         // Se insertan detras de problemVect los problemas a solucionar del problemTreeVector[i].
//         get_session_available_problems(currentCourse.problemTreeVector[i], size, problemVect);
//     }
//     // Ordenamos el vector de problemas crecientemente.
//     sort(problemVect.begin(), problemVect.end(), sort_vect);
//     // El tamaño del vector se devuelve para poder iterar sobre él.
//     return size;
// }

void Usuario::print_available_problems() const
{
    // Si no está inscrito a ningún curso, no es posible listar problemas a enviar (tenga o no).
    if (!isInscribed) return void();

    // Los problemas a enviar son aquellos que no han sido solucionados y que son precedidos por problemas solucionados
    // Por defecto, el primer problema de una sesión se puede enviar. 
    // Inv: cada iteración incrementa el tamaño de problemVect.
    int i;
    for (i = 0; i < currentCourse.sizeAvailableProblems; ++i)
    {
        cout << currentCourse.availableProblems[i].pid << '(' << currentCourse.availableProblems[i].attempts.total << ')' << endl;
    }
    // El tamaño del vector se devuelve para poder iterar sobre él.
}

bool sort_LH_2 (ProblemData& a, ProblemData& b)
{
    return a.pid < b.pid;
}

int Usuario::print_all_time_solved_problems()
{
    int i = 0;
    sort (allCourses.coursesVect.begin(), allCourses.coursesVect.end(), sort_LH_2);
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