/** @file curso.hh
 *  @brief Especificación de la clase 'Curso'.
 */

#ifndef COURSE_HH
#define COURSE_HH

#include <iostream>
#include <vector>
#include <string>
#include "tipos.hh"
#include "sesion.hh"

using namespace std;

// N > 0, Sin repeticiones, 

/** @class Curso
 *  @brief Almacena la información de un curso y facilita su gestión.
 */

class Curso
{
private:
    int total;
    courseid cid;
    vector<sessionid> session;

public:

    /** @brief Overloaded default class null constructor.
     *  \post Null course id ('id'). All other private variables are also undefined.
     */ 
    Curso();

    /** @brief Overloaded class constructor.
     *  \post Sets the course id ('this->cid') to the constructor parameter ('cid'). All other private variables are left undefined.
     */ 
    Curso(const courseid& cid);

    /** @brief Almacena la infomración de un curso por el 'stdin'
     *  \pre El formato de entrada 'stdin' ha de ser correcto, primero el número total de sesiones (N>0) y después las N sesiones.
     *  \post Las sesiones estaran definidas en el vector. El único parametro no definido será el 'courseid'.
     */
    const void read();
};

#endif