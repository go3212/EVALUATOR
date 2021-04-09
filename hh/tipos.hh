/** @file tipos.hh
 *  @brief Archivo que contiene todos los tipos de variable diferentes utilizados en la practica.
 */

#ifndef TIPOS_HH
#define TIPOS_HH

#include <iostream>
#include <string>

using namespace std;

typedef string sessionid;
typedef int userid;
typedef int courseid;

/** @struct ProblemData
 *  @brief Almacena el número de intentos (total) al problema, y su identificador. 
 */
struct ProblemData
{
    Attempts attempts;
    problemid pid;
};

/** @struct CourseData
 *  @brief Holds current course data, if inscribed.
 */
struct CourseData
{
    courseid identifier;
    Attempts totalAttempts;
    vector<ProblemData> solvedProblems;
    vector<ProblemData> availableProblems;
};

/** @struct CourseData
 *  @brief Holds current course data, if inscribed.
 */
struct AllCoursesData
{
    Attempts attempts;
    vector<CourseData> course;
};


#endif