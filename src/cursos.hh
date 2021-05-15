/** @file cursos.hh
 *  @brief Especificación de la clase 'Cursos'.
 */

#ifndef CURSOS_HH
#define CURSOS_HH

#include "curso.hh"

using namespace std;

// N > 0, Sin repeticiones, 

/** @typedef CourseVector
 *  @brief Vector para almacenar cursos. 
 */
typedef vector<Curso> CourseVector;

/** @class Cursos
 *  @brief Facilita la gestión de un conjunto de cursos (obj. 'Curso').
 * 
 *  Gestiona la información de un conjunto de cursos, puede realizar las siguientes operaciones sobre el conjunto:
 *      - Añadir curso, por entrada o directamente.
 *      - Solicitar número total de cursos.
 *      - Solicitar 'Curso' en específico para operar directamente con él.
 */
class Cursos
{
private:
    int total;                      //!< Número de cursos del vector de cursos.
    CourseVector courseVector;      //!< Vector de cursos.
    static Curso nullCourse;        //!< Curso "nulo". Representa un 'Curso' no válido, se utiliza en los retornos de algunos métodos para indicar
                                    //!< que el 'Curso' a modificar no ha sido encontrado.
public:
    /** @brief Constructor por defecto de clase sobrecargado.
     *  \pre true.
     *  \post Número total de cursos es cero. Vector de cursos vacío.
     */ 
    Cursos();

    /** @brief Función que indica el número de cursos que tiene el objeto.
     *  \pre true.
     *  \post No se modifica ningún objeto de la clase.
     *  @return int: número de cursos.
     */
    int get_number_of_courses() const;

    /** @brief Añade un nuevo curso al vector de cursos.
     *  @param course objeto de tipo 'Curso'.
     *  \pre Las sesiones no tienen intersección de problema
     *  \post añade un curso al vector de cursos ('courses') en la posicion size(courseVector) + 1. Solo añade si no se repiten problemas en el curso.  
     *  @return bool: true si se ha añadido correctamente y false si no se ha añadido correctamente.
     */
    bool add_course(Curso& course);

    /** @brief Devuelve los iteradores del mapa del vector de cursos. 
     *  @param beginIterator iterador de la posición inicial.
     *  @param endIterator iterador de la posición final.
     *  \pre true.
     *  \post Los argumentos tendran los iteradores correspondientes a la posición inicial y final del vector de cursos.
     *  @return 'void'
     */
    void get_iterators(CourseVector::const_iterator& beginIterator, CourseVector::const_iterator& endIterator) const;

    /** @brief Busca un curso en el conjunto de cursos.
     *  @param cid identificador de curso a buscar.
     *  \pre true.
     *  \post No se modifica ningún objeto de la clase..
     *  @return 'Curso&': devuelve el curso solicitado si se ha encontrado en la base de datos y devuelve el 'nullCourse' si no se ha encontrado.
     */
    Curso& get_course(const courseid& cid);

    /** @brief Lee un conjunto de cursos por la entrada 'stdin' y los guarda.
     *  \pre Número de cursos a leer en la entrada (C > 0), seguido de C cursos.
     *  \post Se almacenan los datos.
     *  @return void.
     */
    void read();
};

#endif