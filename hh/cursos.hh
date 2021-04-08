#ifndef CURSOS_HH
#define CURSOS_HH

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include "hh/curso.hh"

using namespace std;

// N > 0, Sin repeticiones, 

/** @class Cursos
 *  @brief Almacena todos los cursos y permite su gestión.
 */
class Cursos
{
private:
    int total;
    vector<Curso> courses;
public:
    /** @brief Constructor por defecto de clase sobrecargado.
     *  \post Número total de cursos es cero. Vector de cursos ('curso') no definido.
     */ 
    Cursos();

    /** @brief Constructor de clase sobrecargado, añade un curso al instanciar la clase.
     *  @param cid identificador del curso ('courseid').
     *  @param course objeto del tipo 'Curso'.
     *  \post Se añade una curso y se incializa el conjunto de cursos ('courses').
     */ 
    Cursos(const courseid& cid, const Curso& course);

    /** @brief Añade un nuevo curso al vector de cursos.
     *  @param course objeto de tipo 'Sesión'.
     *  \post añade un curso al vector de cursos ('courses') en la posicion size(courses) + 1. Solo añade si no se repiten problemas en el curso.  
     *        Devuelve si se ha añadido correctamente el curso ('true') o ha habido un problema al añadirlo ('false').
     */
    bool add_course(const Curso& course);

    /** @brief Busca un curso en el conjunto de cursos.
     *  @param cid identificador de curso ('courseid')
     *  \post devuelve el objeto 'Curso' por referencia si se ha encontrado, en caso opuesto, devuelve NULL.
     */
    Curso& search_course(const courseid& cid);
};

#endif