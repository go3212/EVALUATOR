#include "userdata.hh"

CourseManager::CourseManager()
{
    sizeSolvedProblems = 0;
    uniqueAttempts = 0;
    currentCourse = CurrentCourse();
}

CourseManager::~CourseManager()
{
    if (currentCourse.identifier != 0)
    {
        currentCourse.courseIter->force_uninscribe();
    }
}

CourseManager::CurrentCourse::CurrentCourse()
{
    identifier = 0;
}

void CourseManager::insert_available_problems(const ProblemTree& problemTree)
{
    // Queremos ver si el problema se puede insertar o no, si no se puede, buscar todos los insertables.
    // Primero miramos si la raíz ha sido "solucionada", si lo ha sido, insertamos el problema a la lista de disponibles.
    if(problemTree.empty()) return void();
    auto ret = problemDataMap.insert(make_pair(problemTree.value(), ProblemData(problemTree.value())));
    if (ret.second) 
    {
        currentCourse.availableProblems.insert(make_pair(problemTree.value(), ret.first));
        return void();
    }

    insert_available_problems(problemTree.left());
    insert_available_problems(problemTree.right());
}

CourseManager::CurrentCourse::CurrentCourse(const CourseVector::iterator& courseIter, const Sesiones& sessions)
{
    identifier = courseIter->get_cid();
    sessionProblemMapIter = vector<SessionMap::const_iterator>(courseIter->get_number_of_sessions());
    CourseSessionVector::const_iterator beginIter, endIter;
    courseIter->get_iterators(beginIter, endIter);
    numSessions = 0; 
    while (beginIter != endIter)
    {
        sessions.get_session(*beginIter, sessionProblemMapIter[numSessions]);
        ++numSessions;
        ++beginIter;
    }
    this->courseIter = courseIter;
}

bool CourseManager::inscribe(const CourseVector::iterator& courseIter, const Sesiones& sessions)
{
    currentCourse = CurrentCourse(courseIter, sessions);
    courseIter->inscribe_user();
    ProblemTree temp; 
    for (int i = 0; i < currentCourse.numSessions; ++i)
    {
        ProblemTree temp;   
        currentCourse.sessionProblemMapIter[i]->second.get_problemTree(temp);
        insert_available_problems(temp);
    }
    return true;
}

bool CourseManager::uninscribe()
{
    currentCourse.courseIter->uninscribe_user();
    currentCourse = CurrentCourse();
    return true;
}

void CourseManager::fetch_available_problems(const problemid& pid)
{
    // Para buscar los problemas, tenemos que acceder primero al hintMap
    // de la clase para saber en que sesion está, despues, simplemente capturamos
    // el fragmento de bintree corresponiente.
    int i = currentCourse.courseIter->vector_session_position_of_problem(pid);
    TreeNode temp;
    currentCourse.sessionProblemMapIter[i]->second.get_next_problem(pid, temp);
    insert_available_problems(temp.root);
}

void CourseManager::send_attempt(const problemid& pid, const bool& status)
{
    // Siempre que hagamos un envio, actualizamos las stats del curso y los
    // intentos totales
    attempts.update_attempts(status);

    // Ahora queda buscar el problema y modificar el estado de los problemas resueltos
    // y disponibles
    auto ret = currentCourse.availableProblems.find(pid);
    // Nos garantizan que siempre el problema enviado está disponible.
    (*ret).second->second.solve(status);
    if ((*ret).second->second.attempts.total == 1) uniqueAttempts += 1;

    // Si el problema está solucionado, tenemos que eliminarlo del mapa y hacer fetch
    if (status)
    {
        solvedProblems.insert(make_pair(ret->first, ret->second));
        currentCourse.availableProblems.erase(ret);
        fetch_available_problems(pid);
    }
}

void CourseManager::print_available_problems() const
{
    ProblemDataIteratorMap::const_iterator beginIter, endIter;
    beginIter = currentCourse.availableProblems.begin();
    endIter =  currentCourse.availableProblems.end();

    while (endIter != beginIter)
    {
        cout << beginIter->first;
        cout << '(' << beginIter->second->second.attempts.total << ')';
        cout << endl;
        ++beginIter;
    }
}

void CourseManager::print_solved_problems() const
{
    ProblemDataIteratorMap::const_iterator beginIter, endIter;
    beginIter = solvedProblems.begin();
    endIter =  solvedProblems.end();

    while (endIter != beginIter)
    {
        cout << beginIter->first;
        cout << '(' << beginIter->second->second.attempts.total << ')';
        cout << endl;
        ++beginIter;
    }
}

courseid CourseManager::current_course_id() const
{
    return currentCourse.identifier;
}

bool CourseManager::course_finished() const
{
    return currentCourse.availableProblems.empty();
}