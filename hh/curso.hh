#ifndef COURSE_HH
#define COURSE_HH

#include <iostream>
#include <vector>
#include <string>
#include "hh/BinTree.hh"
#include "hh/sesion.hh"

using namespace std;

// N > 0, Sin repeticiones, 

/** @class Course
 *  @brief Holds data for a course: course identifier ('id') and a sequence of session identifiers ('sessions')
 */

class Course
{
private:
    int id;
    vector<Session> sessions;

public:

    /** @brief Overloaded default class null constructor.
     *  \post Null course id ('id'). All other private variables are also undefined.
     */ 
    Course();

    /** @brief Overloaded class constructor.
     *  \post Sets the course id ('this->id') to the constructor parameter ('id'). All other private variables are left undefined.
     */ 
    Course(const int& id);

};

#endif