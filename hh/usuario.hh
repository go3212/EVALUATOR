#ifndef USER_HH
#define USER_HH

#include <iostream>
#include <vector>
#include <string>
#include <set>
#include "hh/problema.hh"

using namespace std;

// N > 0, Sin repeticiones, 

/** @struct Attempts
 *  @brief Holds attempts data.
 */
struct Attempts
{
    int accepted;
    int total;
    int rejected;
};

/** @struct CourseData
 *  @brief Holds current course data, if inscribed.
 */
struct CurrentCourseData
{
    bool is_inscribed;
    int identifier;
    Attempts attempts;
    set<Problema, bool> problems;
};

/** @struct CourseData
 *  @brief Holds current course data, if inscribed.
 */
struct AllCoursesData
{
    Attempts attempts;
    vector<Problema> solved_problems;
};

/** @class User
 *  @brief Holds data for a user: a username ('name') and a sequence of session identifiers ('sessions')
 */
class Usuario
{
private:
    int uid;
    CurrentCourseData current_course;
    AllCoursesData all_courses;

public:

    /** @brief Overloaded default class null constructor.
     *  \post Null user id ('uid'). All other private variables are also undefined.
     */ 
    Usuario();

    /** @brief Overloaded class constructor.
     *  \post Sets the user id ('this->uid') to the constructor parameter ('uid'). All other private variables are left undefined.
     */ 
    Usuario(const int& uid);

    /** @brief Inscribe al usuario en un curso.
     *  @param cid identificador del curso.
     *  \pre El usuario debe tener 'uid' != NULL.
     *  \post Si el usuario no está inscrito en ningún curso se le inscribe al parámetro de la función y se devuelve ('true'), en caso opuesto, no se modifica la inscripción y se devuelve ('false').
     */
    bool inscribe(const int& cid);

    /** @brief Devuelve si el usuario está inscrito en un curso.
     *  \post devuelve 'true' si el usuario está inscrito y 'false' si no lo está.
     */
    bool is_inscribed();
};

#endif