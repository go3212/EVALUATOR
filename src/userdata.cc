#include "userdata.hh"
#include <algorithm>


void imm_insert_available_problems(const BinTree<pair<problemid, bool>>& problemTree, int& size, vector<ProblemData>& problemVector)
{
    BinTree<pair<problemid, bool>> left = problemTree.left(), right = problemTree.right();
    if (!left.empty())
    {   
        // Si el problema de la izquierda está solucionado, hay que verificar recursivamente si sus hijos
        // son problemas a solucionar o no. Si no está solucionado, sus hijos no son solucionables.
        if (left.value().second) insert_available_problems(left, size, problemVector);
        else insertion_sort_LH(ProblemData(left.value().first), problemVector, size); 
    }
    if (!right.empty())
    {
        // Si el problema de la izquierda está solucionado, hay que verificar recursivamente si sus hijos
        // son problemas a solucionar o no. Si no está solucionado, sus hijos no son solucionables.
        if (right.value().second) insert_available_problems (right, size, problemVector);
        else insertion_sort_LH(ProblemData(right.value().first), problemVector, size); 
    }
}

void insert_available_problems (const BinTree<pair<problemid, bool>>& problemTree, int& size, vector<ProblemData>& problemVector)
{
    // Un problema tiene posibilidad de envio si, y solo si, su anterior problema (en la rama) ha sido solucionado, se
    // considera que la raíz  (la primera) siempre es solucionable.
    
    if (!problemTree.value().second) // El único caso que puede entrar (o no) en este condicional es el primero.
    {
        insertion_sort_LH(ProblemData(problemTree.value().first), problemVector, size); 
        return void(); // No hau que revisar más.
    }
    BinTree<pair<problemid, bool>> left = problemTree.left(), right = problemTree.right();
    // Para cumplir la precondición, en la recursividad solo se pueden pasar árboles no vacíos.
    if (!left.empty())
    {   
        // Si el problema de la izquierda está solucionado, hay que verificar recursivamente si sus hijos
        // son problemas a solucionar o no. Si no está solucionado, sus hijos no son solucionables.
        if (left.value().second) imm_insert_available_problems(left, size, problemVector);
        else insertion_sort_LH(ProblemData(left.value().first), problemVector, size); 
    }
    if (!right.empty())
    {
        // Si el problema de la izquierda está solucionado, hay que verificar recursivamente si sus hijos
        // son problemas a solucionar o no. Si no está solucionado, sus hijos no son solucionables.
        if (right.value().second) imm_insert_available_problems (right, size, problemVector);
        else insertion_sort_LH(ProblemData(right.value().first), problemVector, size); 
    }
}

void initialize_solved_problems (UserCoursesData& userCoursesData, int& unsolved, BinTree<pair<problemid, bool>>& problemTree)
{
    if (problemTree.empty()) return void();
    int i = userCoursesData.find(problemTree.value().first);
    if (i != -1)
    {
        ++unsolved;
        problemTree.value().second = true;
    }
    BinTree<pair<problemid, bool>> left = problemTree.left(), right = problemTree.right();
    initialize_solved_problems(userCoursesData, unsolved, left);
    initialize_solved_problems(userCoursesData, unsolved, right);
    return void();
}


//##################//
//  UserCoursesData
UserCoursesData::UserCoursesData()
{
    coursesVect = vector<ProblemData>(0);
    sizeCoursesVect = 0;
    unique_attempts = 0;
}


int UserCoursesData::insert_solved_problem (const ProblemData& problemData)
{
    // Se asume que el problema no existe en el vector.
    coursesVect.insert(coursesVect.end(), ProblemData());
    ++sizeCoursesVect;
    int i = sizeCoursesVect - 1; 
    while(i > 0 && coursesVect[i - 1].pid > problemData.pid)
    {
        coursesVect[i] = coursesVect[i - 1];
        --i;
    }
    coursesVect[i] = problemData;
    return i;
}

bool UserCoursesData::update_attempts (ProblemData& problemData, const bool& isSolved)
{
    attempts.update_attempts(isSolved);
    // En cualquier caso, actualizamos 
    if (problemData.attempts.total == 1)
    {
        unique_attempts += 1;
    }
    // Si se ha solucionado, añadimos problemData al vector de problemas solucionados.
    // if (isSolved) insert_solved_problem (problemData);
    if (isSolved) coursesVect.insert(coursesVect.end(), problemData), ++sizeCoursesVect;
    return isSolved;
}

bool sort_LH (const ProblemData& a, const ProblemData& b)
{
    return a.pid < b.pid;
}

int UserCoursesData::find (const problemid& pid)
{
    //if (sizeCoursesVect == 0) return -1;
    sort (coursesVect.begin(), coursesVect.end(), sort_LH);
    int i = binary_search_LH (pid, coursesVect, sizeCoursesVect);
    if (i == -1) return -1;
    return i;
}

//##################//
//  UserCourseData
UserCourseData::UserCourseData()
{
    sizeProblemTreeVector = 0;
    numProblems = 0;
    solvedProblemsSize = 0;
    problemTreeVector = vector<BinTree<pair<problemid, bool>>>(sizeProblemTreeVector);
    sizeAvailableProblems = 0;
}

UserCourseData::UserCourseData(const courseid& cid)
{
    identifier = cid;
    sizeProblemTreeVector = 0;
    numProblems = 0;
    solvedProblemsSize = 0;
    problemTreeVector = vector<BinTree<pair<problemid, bool>>>(sizeProblemTreeVector);
    sizeAvailableProblems = 0;
}

int UserCourseData::notsolved_problems() const
{
    return numProblems - solvedProblemsSize;
}

bool UserCourseData::update_tree_problem (const problemid& pid, ProblemData& problemData, const bool& solved, BinTree<pair<problemid, bool>>& problemTree)
{
    if (problemTree.empty()) return false;
    if (problemTree.value().first == pid)
    {
        problemTree.value().second = solved;
        if (solved) insert_available_problems(problemTree, sizeAvailableProblems, availableProblems);
        return true;
    }
    BinTree<pair<problemid, bool>> left = problemTree.left(), right = problemTree.right();
    return (update_tree_problem (pid, problemData, solved, left) or update_tree_problem (pid, problemData, solved, right));
}

void UserCourseData::fetch_solved_problems(UserCoursesData& userCoursesData)
{
    int solved;
    for (int i = 0; i < sizeProblemTreeVector; ++i)
    {
        solved = 0;
        initialize_solved_problems(userCoursesData, solved, problemTreeVector[i]);
        insert_available_problems(problemTreeVector[i], sizeAvailableProblems, availableProblems);
        solvedProblemsSize += solved;
    }
    
}

void UserCourseData::update_data(const problemid& pid, ProblemData& problemData, const bool& isSolved)
{
    //// Primero buscamos el problema en curso (árbol de problemas) y actualizamos su información.
    //// Básicamente, como la intersección de conjuntos de sesiones es el vacío, cada problema es único del curso.
    int i = binary_search_LH(pid, availableProblems, sizeAvailableProblems);
    availableProblems[i].solve(isSolved);
    problemData = availableProblems[i];

    if (isSolved) 
    {
        availableProblems.erase(availableProblems.begin() + i);
        --sizeAvailableProblems;    
        update_tree_problem (pid, problemData, isSolved, problemTreeVector[courseIter->vector_session_position_of_problem(pid)]);
        ++solvedProblemsSize;
    }
}