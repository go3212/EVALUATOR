#include "../hh/usuario.hh"

using namespace std;

Usuario::Usuario()
{
    hasUserid = false;
}

const void Usuario::write()
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