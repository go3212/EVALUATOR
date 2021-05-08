#ifndef USERDATA_HH
#define USERDATA_HH

#include <iostream>
#include <algorithm>
#include <map>
#include <set>
#include "tipos.hh"
#include "cursos.hh"
#include "sesiones.hh"

typedef map<problemid, ProblemData> ProblemDataMap;
typedef map<problemid, ProblemDataMap::iterator> ProblemDataIteratorMap;



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
        int numSessions;
        int numProblems;

        CurrentCourse();
        CurrentCourse(const CourseVector::iterator& courseIter, const Sesiones& sessions);
        ~CurrentCourse(); 
    };

    CurrentCourse currentCourse;

    void insert_available_problems(const ProblemTree& problemTree);
public:

    CourseManager();
    ~CourseManager();

    courseid current_course_id() const;
    bool inscribe(const CourseVector::iterator& courseIter, const Sesiones& sessions);
    void fetch_available_problems(const problemid& pid);
    bool uninscribe();
    void force_uninscribe();
    // void fetch_available_problems_rec(const problemid& pid);
    void send_attempt(const problemid& pid, const bool& status);
    void print_available_problems() const;
    void print_solved_problems();
    bool course_finished() const;

    /** EXP */
    void write() const
    {
        cout <<'(' << attempts.total;
        cout << ',' << attempts.accepted << ',' << uniqueAttempts << ',';
        cout << currentCourse.identifier << ')'; 
    }

};



#endif