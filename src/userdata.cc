#include "userdata.hh"
#include <algorithm>

CourseManager::CourseManager()
{
    sizeSolvedProblems = 0;
    uniqueAttempts = 0;
}

CourseManager::~CourseManager()
{

}

CourseManager::CurrentCourse::~CurrentCourse()
{

}

CourseManager::CurrentCourse::CurrentCourse()
{
    identifier = 0;
    numProblems = 0;
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
        numProblems += sessionProblemMapIter[numSessions]->second.get_number_of_problems();
        ++numSessions;
        ++beginIter;
    }
    this->courseIter = courseIter;
}

bool CourseManager::inscribe(const CourseVector::iterator& courseIter, const Sesiones& sessions)
{
    currentCourse = CurrentCourse(courseIter, sessions);
    courseIter->inscribe_user();
    return true;
}

bool CourseManager::uninscribe()
{
    currentCourse.courseIter->uninscribe_user();
    currentCourse = CurrentCourse();
    return true;
}

void CourseManager::force_uninscribe()
{
    if (currentCourse.identifier != 0)
    {
        currentCourse.courseIter->force_uninscribe();
    }
    currentCourse = CurrentCourse();
}

void CourseManager::fetch_available_problems(const problemid& pid)
{
    // Para buscar los problemas, tenemos que acceder primero al hintMap
    // de la clase para saber en que sesion está, despues, simplemente capturamos
    // el fragmento de bintree corresponiente.
    int i = currentCourse.courseIter->vector_session_position_of_problem(pid);
    const TreeNode& temp = currentCourse.sessionProblemMapIter[i]->second.get_next_problem(pid);
    insert_available_problems(temp.root);
}

void CourseManager::send_attempt(const problemid& pid, const bool& status)
{
    // Siempre que hagamos un envio, actualizamos las stats del curso y los
    // intentos totales
    attempts.update_attempts(status);

    // Insertamos el problema en el mapa.
    auto ret = problemDataMap.insert(make_pair(pid, ProblemData()));
    // Nos garantizan que siempre el problema enviado está disponible.
    ret.first->second.solve(status);
    if (ret.first->second.attempts.total == 1) uniqueAttempts += 1;
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

bool fast_comp(const pair<problemid, int>& a, const pair<problemid, int>& b)
{
    return a.first < b.first;
}

void CourseManager::print_solved_problems() 
{
    sort (solvedProblems.begin(), solvedProblems.end(), fast_comp);
    auto beginIter = solvedProblems.begin(), endIter = solvedProblems.end();

    while (endIter != beginIter)
    {
        cout << beginIter->first;
        cout << '(' << beginIter->second << ')';
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