#include "userdata.hh"

void initialize_solved_problems (UserCoursesData& userCoursesData, int& unsolved, BinTree<ProblemData>& problemTree)
{
    if (problemTree.empty()) return void();
    int i = userCoursesData.find(problemTree.value().pid);
    if (i != -1)
    {
        ++unsolved;
        problemTree.value() = userCoursesData.coursesVect[i];
    }
    BinTree<ProblemData> left = problemTree.left(), right = problemTree.right();
    initialize_solved_problems(userCoursesData, unsolved, left);
    initialize_solved_problems(userCoursesData, unsolved, right);
    return void();
}

//##################//
//  UserCoursesData
UserCoursesData::UserCoursesData()
{
    attemptedProblemsVect = vector<problemid>(0);
    coursesVect = vector<ProblemData>(0);
    sizeCoursesVect = 0;
    sizeAttemptedProblemsVect = 0;
    unique_attempts = 0;
}

bool UserCoursesData::insert_attempted_problem(const ProblemData& problemData)
{
    int i = binary_search_LH (problemData.pid, attemptedProblemsVect, sizeAttemptedProblemsVect);
    if (i != -1) return false;
    insertion_sort_LH(problemData.pid, attemptedProblemsVect, sizeAttemptedProblemsVect);
    unique_attempts += 1;
    return true;
}

int UserCoursesData::insert_solved_problem (const ProblemData& problemData)
{
    // Se asume que el problema no existe en el vector.
    coursesVect.push_back(problemData);
    ++sizeCoursesVect;
    int i = sizeCoursesVect - 1; 
    ProblemData temp;
    while(i > 0 && coursesVect[i - 1].pid > coursesVect[i].pid)
    {
        temp = coursesVect[i - 1];
        coursesVect[i - 1] = coursesVect[i];
        coursesVect[i] = temp;
        --i;
    }
    return i;
}

bool UserCoursesData::update_attempts (const ProblemData& problemData, const bool& isSolved)
{
    attempts.update_attempts(isSolved);
    int i = binary_search_LH (problemData.pid, attemptedProblemsVect, sizeAttemptedProblemsVect);
    // En cualquier caso, actualizamos 
    if (i == -1)
    {
        insertion_sort_LH (problemData.pid, attemptedProblemsVect, sizeAttemptedProblemsVect);
        unique_attempts += 1;
    }
    
    // Si se ha solucionado, añadimos problemData al vector de problemas solucionados.
    if (isSolved) insert_solved_problem (problemData);
    return isSolved;
}

int UserCoursesData::find (const problemid& pid)
{
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
    problemTreeVector = vector<BinTree<ProblemData>>(sizeProblemTreeVector);
    // solvedProblems = vector<ProblemData>(0); 
}

UserCourseData::UserCourseData(const courseid& cid)
{
    identifier = cid;
    sizeProblemTreeVector = 0;
    numProblems = 0;
    solvedProblemsSize = 0;
    problemTreeVector = vector<BinTree<ProblemData>>(sizeProblemTreeVector);
    // solvedProblems = vector<ProblemData>(0);
}

int UserCourseData::notsolved_problems() const
{
    return numProblems - solvedProblemsSize;
}

bool UserCourseData::update_tree_problem (const problemid& pid, ProblemData& problemData, const bool& solved, BinTree<ProblemData>& problemTree)
{
    if (problemTree.empty()) return false;
    if (problemTree.value().pid == pid)
    {
        problemTree.value().solve(solved);
        problemData = problemTree.value();
        return true;
    }
    BinTree<ProblemData> left = problemTree.left(), right = problemTree.right();
    return (update_tree_problem (pid, problemData, solved, left) or update_tree_problem (pid, problemData, solved, right));
}

void UserCourseData::fetch_solved_problems(UserCoursesData& userCoursesData)
{
    int solved;
    for (int i = 0; i < sizeProblemTreeVector; ++i)
    {
        solved = 0;
        initialize_solved_problems(userCoursesData, solved, problemTreeVector[i]);
        solvedProblemsSize += solved;
    }
    
}

ProblemData UserCourseData::update_data(const problemid& pid, const bool& isSolved)
{
    ProblemData problemData;
    // Primero actualizamos el número total de intentos. 
    totalAttempts.update_attempts(isSolved);
    // Primero buscamos el problema en curso (árbol de problemas) y actualizamos su información.
    int i = courseIter->vector_session_position_of_problem(pid);
    // Básicamente, como la intersección de conjuntos de sesiones es el vacío, cada problema es único del curso.
    update_tree_problem (pid, problemData, isSolved, problemTreeVector[i]);

    // if (isSolved) insertion_sort_LH (problemData, solvedProblems, solvedProblemsSize);
    if (isSolved) ++solvedProblemsSize;
    return problemData;
}
