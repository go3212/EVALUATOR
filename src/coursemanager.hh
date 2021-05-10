#ifndef COURSEMANAGER_HH
#define COURSEMANAGER_HH

#include "cursos.hh"

typedef map<problemid, ProblemData> ProblemDataMap;
typedef map<problemid, ProblemDataMap::const_iterator> ProblemDataIteratorMap;



/** @struct UserCoursesData
 *  @brief Almacena información genérica sobre todos los 'Curso' que ha cursado un 'Usuario'.
 */
class CourseManager
{
private:
    Attempts attempts;
    ProblemDataMap problemDataMap;
    vector<pair<problemid, int>> solvedProblems;
    int sizeSolvedProblems;
    int uniqueAttempts;

    /** @struct UserCourseData
    *  @brief Almacena información genérica sobre 'Curso' que cursa un 'Usuario'.
    */
    struct CurrentCourse
    {
        courseid identifier;
        CourseVector::iterator courseIter;
        vector<SessionMap::const_iterator> sessionProblemMapIter;
        ProblemDataIteratorMap availableProblems;
        vector<pair<problemid, ProblemDataMap::iterator>> availableProblemsVect;
        int numSessions;
        int numProblems;

        CurrentCourse();
        CurrentCourse(const CourseVector::iterator& courseIter, const Sesiones& sessions);
        void not_solved_problems(int& sum, const ProblemDataMap& problemDataMap, const ProblemTree& problemTree) const;
    };

    CurrentCourse currentCourse;

    void insert_available_problems(int& sum, vector<pair<problemid, int>>& myVect, const ProblemTree& problemTree) const;
public:

    CourseManager();

    courseid current_course_id() const;
    bool inscribe(const CourseVector::iterator& courseIter, const Sesiones& sessions);
    void fetch_available_problems(const problemid& pid);
    bool course_finished() const;
    bool uninscribe();
    void force_uninscribe();
    // void fetch_available_problems_rec(const problemid& pid);
    void send_attempt(const problemid& pid, const bool& status);
    void print_available_problems() const;
    void print_solved_problems();

    /** EXP */
    void write() const
    {
        cout <<'(' << attempts.total;
        cout << ',' << attempts.accepted << ',' << uniqueAttempts << ',';
        cout << currentCourse.identifier << ')'; 
    }

};



#endif