#include "coursemanager.hh"

bool fast_comp(const pair<problemid, int>& a, const pair<problemid, int>& b)
{
    return a.first < b.first;
}

CourseManager::CourseManager()
{
    sizeSolvedProblems = 0;
    uniqueAttempts = 0;
}

CourseManager::CurrentCourse::CurrentCourse()
{
    identifier = 0;
    numProblems = 0;
}

CourseManager::CurrentCourse::CurrentCourse(const CourseVector::iterator& courseIter, const Sesiones& sessions)
{
    // Cuando se inscribe al usuario en un curso, utilizamos el propio constructor de la clase para hacerlo.
    identifier = courseIter->get_cid();
    sessionProblemMapIter = vector<SessionMap::const_iterator>(courseIter->get_number_of_sessions()); // Definimos el tamaño del vector de sesiones.
    CourseSessionVector::const_iterator beginIter, endIter;                                            
    courseIter->get_iterators(beginIter, endIter);
    numSessions = 0; 
    numProblems = 0;
    // En el bucle, tomaremos las sesiones del curso e insertaremos los iteradores en un vector externo para tener acceso rápido a su información.
    while (beginIter != endIter)
    {
        sessions.get_session_with_iterator(*beginIter, sessionProblemMapIter[numSessions]);
        ++numSessions;
        ++beginIter;
    }
    this->courseIter = courseIter;  // Guardamos el iterador para recurrir a él cuando necesitemos actualizar la información del curso.
}

courseid CourseManager::current_course_id() const
{
    return currentCourse.identifier;
}

bool CourseManager::course_finished() const
{
    return currentCourse.numProblems == 0;
}

void CourseManager::inscribe(const CourseVector::iterator& courseIter, const Sesiones& sessions)
{
    currentCourse = CurrentCourse(courseIter, sessions);
    courseIter->inscribe_user();
    int numProblemsAvailable = 0;
    for (int i = 0; i < currentCourse.numSessions; ++i)
    {
        currentCourse.not_solved_problems(numProblemsAvailable, problemDataMap, currentCourse.sessionProblemMapIter[i]->second.get_problemTree()); //[CAMBIAR A VECTOR]
    }
    currentCourse.numProblems = numProblemsAvailable;
}

void CourseManager::CurrentCourse::insert_available_problems(const ProblemDataMap& problemDataMap, int& sum, vector<pair<problemid, int>>& myVect, const ProblemTree& problemTree) const
{
    // Queremos ver si el problema se puede insertar o no, si no se puede, buscar todos los insertables.
    // Primero miramos si la raíz ha sido "solucionada", si lo ha sido, insertamos el problema a la lista de disponibles.
    if(problemTree.empty()) return void();
    auto ret = problemDataMap.find(problemTree.value());
    if (ret == problemDataMap.end()) 
    {
        myVect.insert(myVect.end(), make_pair(problemTree.value(), 0));
        sum += 1;
        return void();
    }
    if (!ret->second.solved)
    {
        myVect.insert(myVect.end(), make_pair(problemTree.value(), ret->second.attempts.total));
        sum += 1;
        return void();
    }
    
    insert_available_problems(problemDataMap, sum, myVect, problemTree.left());
    insert_available_problems(problemDataMap, sum, myVect, problemTree.right());
    return void();
}

//[MAYBE CONVERTIR A FUNCION DE TIPO INT?]
void CourseManager::CurrentCourse::not_solved_problems(int& sum, const ProblemDataMap& problemDataMap, const ProblemTree& problemTree) const
{   
    if (problemTree.empty()) return void();
    auto ret = problemDataMap.find(problemTree.value());
    if (ret == problemDataMap.end()) sum += 1;
    else if (!ret->second.solved) sum += 1;
    not_solved_problems(sum, problemDataMap, problemTree.left());
    not_solved_problems(sum, problemDataMap, problemTree.right());
    return void();
}

bool CourseManager::uninscribe()
{
    if (currentCourse.identifier == 0) return false;
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

void CourseManager::send_attempt(const problemid& pid, const bool& status)
{
    // Siempre que hagamos un envio, actualizamos las stats del curso y los
    // intentos totales
    attempts.update_attempts(status);

    // Insertamos el problema en el mapa.
    auto ret = problemDataMap.insert(make_pair(pid, ProblemData()));
    // Nos garantizan que siempre el problema enviado está disponible.
    ret.first->second.make_attempt(status);
    if (ret.first->second.attempts.total == 1) uniqueAttempts += 1;
    if (ret.first->second.solved)
    {
        solvedProblems.insert(solvedProblems.end(), make_pair(pid, ret.first->second.attempts.total));
        --currentCourse.numProblems;
    }
}



void CourseManager::print_available_problems() const
{
    vector<pair<problemid, int>> availableProblems;
    int n = 0;
    for (int i = 0; i < currentCourse.numSessions; ++i)
    {
        currentCourse.insert_available_problems(problemDataMap, n, availableProblems, currentCourse.sessionProblemMapIter[i]->second.get_problemTree());  // [CAMBIAR A VECTOR]
    }
    sort (availableProblems.begin(), availableProblems.end(), fast_comp);

    for (int i = 0; i < n; ++i)
    {
        cout << availableProblems[i].first;
        cout << '(' << availableProblems[i].second << ')';
        cout << endl;
    }
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
