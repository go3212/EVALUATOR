#include "../hh/usuario.hh"

using namespace std;

Usuario::Usuario()
{
    hasUserid = false;
}

const bool Usuario::inscribe(const courseid& cid)
{
    if (isInscribed) return false;
    currentCourse.identifier = cid;
    isInscribed = true;
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