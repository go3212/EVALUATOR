/** @file curso.hh
 *  @brief Especificación de la clase 'Curso'.
 */

#ifndef COURSE_HH
#define COURSE_HH

#include <iostream>
#include <vector>
#include <string>
#include "sesion.hh"

typedef int courseid;

using namespace std;

// N > 0, Sin repeticiones, 

/** @class Course
 *  @brief Holds data for a course: course identifier ('id') and a sequence of session identifiers ('sessions')
 */

class Curso
{
private:
    courseid id;
    vector<sessionid> session;

public:

    /** @brief Overloaded default class null constructor.
     *  \post Null course id ('id'). All other private variables are also undefined.
     */ 
    Curso();

    /** @brief Overloaded class constructor.
     *  \post Sets the course id ('this->id') to the constructor parameter ('cid'). All other private variables are left undefined.
     */ 
    Curso(const courseid& cid);

    /** @brief Almacena la infomración de un curso por el 'stdin'
     *  \pre El formato de entrada 'stdin' ha de ser correcto, primero el número total de sesiones (N>0) y después las N sesiones.
     *  \post Las sesiones estaran definidas en el vector. El único parametro no definido será el 'courseid'.
     */
    void read();
};

#endif