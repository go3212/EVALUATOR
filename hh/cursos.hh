/** @file cursos.hh
 *  @brief Especificación de la clase 'Cursos'.
 */

#ifndef CURSOS_HH
#define CURSOS_HH

#include <iostream>
#include "tipos.hh"
#include "curso.hh"

using namespace std;

// N > 0, Sin repeticiones, 

typedef vector<Curso> CourseVector;

/** @class Cursos
 *  @brief Facilita la gestión de un conjunto de cursos (obj. 'Curso').
 */
class Cursos
{
private:
    int total;
    CourseVector courseVector;
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
     *  @param course objeto de tipo 'Curso'.
     *  \pre Las sesiones no tienen intersección de problema
     *  \post añade un curso al vector de cursos ('courses') en la posicion size(courses) + 1. Solo añade si no se repiten problemas en el curso.  
     *        Devuelve si se ha añadido correctamente el curso ('true') o ha habido un problema al añadirlo ('false').
     */
    bool add_course(Curso& course);

    /** @brief Adquirir iteradores del vector de cursos. 
     *  @param myBeginIterator iterador de la posición inicial.
     *  @param myEndIterator iterador de la posición final.
     *  \post Los argumentos tendran los iteradores correspondientes a la posición inicial y final del vector de cursos.
     */
    void get_iterators(CourseVector::const_iterator& beginIterator, CourseVector::const_iterator& endIterator) const;

    int get_number_of_courses() const;

    /** @brief Busca un curso en el conjunto de cursos.
     *  @param cid identificador de curso ('courseid')
     *  \post devuelve el objeto 'Curso' por referencia si se ha encontrado, en caso opuesto, devuelve NULL.
     */
    bool get_course(const courseid& cid, CourseVector::iterator& vectorIter);

    /** @brief Lee un conjunto de cursos por la entrada 'stdin' y los guarda.
     *  \pre Número de cursos a leer en la entrada (C > 0), seguido de C cursos.
     *  \post Se almacenan los datos.
     */
    void read();
};

#endif