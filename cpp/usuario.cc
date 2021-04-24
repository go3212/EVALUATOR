#include "../hh/usuario.hh"

using namespace std;

Usuario::Usuario()
{
    hasUserid = false;
}

const void Usuario::print_all_time_solved_problems() const
{
    int i = 0;
    for (i = 0; i < allCourses.sizeCoursesVect - 1; ++i)
    {
        cout << allCourses.coursesVect[i] << ' ';
    }
    if (allCourses.sizeCoursesVect != 0) cout << allCourses.coursesVect[i] << endl;
}

const bool Usuario::inscribe(const courseid& cid, const Curso& course, Sesiones& sessions)
{
    if (isInscribed) return false;
    currentCourse.identifier = cid;
    isInscribed = true;

    // vector<sessionid>::const_iterator myBeginIter, myEndIter;
    // map<sessionid, Sesion>::const_iterator sessionIter;
    // //pair<sessionid, BinTree<pair<bool, problemid>>> vectPair;
    // course.get_iterators(myBeginIter, myEndIter);
    // while (myBeginIter != myEndIter)
    // {
    //     //sessions.get_session((*myBeginIter), sessionIter);
    //     //vectPair.first = (*myBeginIter);
    //     //vectPair.second = (*sessionIter).second.get_problemsTree();
    //     //currentCourse.sessions.push_back(vectPair);
    //     //++myBeginIter;
    // }

    return true; 
}

const bool Usuario::is_inscribed() const
{
    return isInscribed;
}

const bool Usuario::inscribed_course_id() const
{
    return currentCourse.identifier;
}

const void Usuario::write() const
{
    cout << uid << '(' << allCourses.attempts.total;
    cout << ',' << allCourses.attempts.accepted << ',' << allCourses.attempts.unique << ',';
    cout << ((isInscribed) ? currentCourse.identifier : 0) << ')';
}

Usuario::Usuario(const userid& uid)
{
    this->uid = uid;
    hasUserid = true;
    isInscribed = false;
}