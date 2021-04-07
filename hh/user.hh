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
    set<Problem, bool> problems;
};

/** @struct CourseData
 *  @brief Holds current course data, if inscribed.
 */
struct AllCoursesData
{
    Attempts attempts;
    vector<Problem> solved_problems;
};

/** @class User
 *  @brief Holds data for a user: a username ('name') and a sequence of session identifiers ('sessions')
 */
class User
{
private:
    string name;
    CurrentCourseData current_course;
    AllCoursesData all_courses;


public:

    /** @brief Overloaded default class null constructor.
     *  \post Null user id ('id'). All other private variables are also undefined.
     */ 
    User();

    /** @brief Overloaded class constructor.
     *  \post Sets the username ('this->name') to the constructor parameter ('name'). All other private variables are left undefined.
     */ 
    User(const int& name);

};

#endif