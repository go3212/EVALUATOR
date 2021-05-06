/** @file usuario.hh
 *  @brief Especificación de la clase 'Usuario'.
 */

#ifndef USER_HH
#define USER_HH

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include "tipos.hh"
#include "cursos.hh"
#include "sesiones.hh"
#include "problema.hh"
#include "userdata.hh"

using namespace std;

/** @class Usuario
 *  @brief Almacena la información de un usuario y facilita su gestión.
 */
class Usuario
{
private:
    userid uid;
    bool hasUserid;
    bool isInscribed;
    UserCourseData currentCourse;
    UserCoursesData allCourses;

public:

    /** @brief Constructor por defecto de la clase.
     *  \pre true.
     *  \post Todas las variables son inicializadas excepto el identificador de usuario ('uid').
     */ 
    Usuario();

    /** @brief Constructor sobrecargado de la clase.
     *  @param uid identificador de usuario ('userid').
     *  \pre true.
     *  \post Todas las variables de la clase son inicializadas y el identificador de usuario es el parámetro.
     */ 
    Usuario(const userid& uid);

    /** @brief Función que indica si el usuario tiene identificador.
     *  \pre true.
     *  \post El usuario mantiene el estado que tenia anteriormente.
     *  @return bool: 'true' si el usuario tiene identificador y 'false' si no lo tiene.
     */
    bool has_userid() const;

    /** @brief Función que indica si el usuario está inscrito en un curso.
     *  \pre true.
     *  \post El usuario mantiene el estado que tenia anteriormente.
     *  @return bool: 'true' si el usuario está inscrito y 'false' si no lo está.
     */
    bool is_inscribed() const;

    /**
     * @brief Función que indica el identificador del curso al que está inscrito el usuario.
     * \pre El usuario debe estar inscrito en un curso.
     * \post El usuario mantiene el estado que tenia anteriormente.
     * @return courseid: devuelve el identificador del curso al que está inscrito el usuario.
     */
    courseid inscribed_course_id() const;

    /** @brief Inscribe al usuario en un curso.
     *  @param cid identificador del curso ('courseid').
     *  @param course objeto de tipo 'Curso'.
     *  @param sessions objeto del tipo 'Sesiones'.
     *  \pre El usuario debe tener identificador. El curso al que se quiere inscribir debe existir en el objeto 'Curso' y todas sus sesiones 
     *       deben pertenecer al conjunto de sesiones del objeto 'Sesiones' proporcionado por los parámetros.
     *  \post Si el usuario no está inscrito en ningún curso se le inscribe al parámetro de la función y se devuelve ('true'), 
     *        en caso opuesto, no se modifica la inscripción y se devuelve ('false').
     *  @return bool: 'true' si se ha inscrito al usuario correctamente, 'false' si el usuario ya estaba inscrito en un curso.
     */
    bool inscribe(const courseid& cid, const CourseVector::iterator& courseIter, Sesiones& sessions);

    /**
     * @brief Función que actualiza el conjunto de problemas de acuerdo con las reglas establecidas previamente.
     * \pre El usuario está inscrito y el problema a solucionar no ha sido solucionado previamente y existe en el curso.
     * \post Se actualiza la estructura 'currentCourse' y la estructura 'allCourses'. Se actualiza el estado del curso en el que está inscrito el usuario
     * @return bool: 'true' si el curso se ha completado, 'false' si no ha sido completado.
     */
    bool update_problem(const problemid& pid, const bool& isSolved);

    /**
     * @brief Función que sirve para "visualizar" los problemas que tiene el usuario disponibles a solucionar.
     * @param problemVect objeto que contendrá todos los problemas disponibles (que cumple todos los requisitos) a solucionar por el usuario. 
     * \pre true.
     * \post El vector tiene tamaño superior o igual al inicial. Si el return es diferente de -1, el vector estará ordenado crecientemente, si el return es -1,
     *       el vector no se habrá modificado.
     * @return int: '-1' si el usuario no está inscrito en ningun curso. El tamaño del vector del parámetro tras la ejecución en cualquier otro caso.
     */
    int available_problems(vector<ProblemData>& problemVect) const;

    /** @brief Función que imprime por pantalla todos los cursos solucionados por un usuario.
     *  \pre El usuario debe tener identificador.
     *  \post No se realizan modificaciones en ningún objeto.
     *  @return int: número de problemas resueltos.
     */
    int print_all_time_solved_problems();

    /** @brief Imprime por pantalla información sobre el usuario
     *  \pre true.
     *  \post Se imprime por pantalla la infomación del problema en este formato:
     *        uid(intentos totales, intentos exitosos, problemas intentados (número), courseid)
     *  @return void.
     */
    void write() const;

    void print_available_problems() const;

    //######################################//
    //      FUNCIONES NO IMPLEMENTADAS      //
    //######################################//

    // /** @brief Almacena la información de un usuario.
    //  *  \pre Los datos en 'stdin' deben estar ordenados correctamente: identificador ('userid').
    //  *  \post Se almacena un identificador en el usuario y se establece a 'true' el parámetro implícito ('has_userid').
    //  */
    // void read();

    // /** @brief Actualiza el estado del curso al enviar un problema.
    //  *  @param pid identificador de problema ('problemid').
    //  *  @param solved valor que indica si el problema ha sido solucionado correctamente o no ('bool').
    //  *  \post Actualiza el número de intentos y la lista de problemas disponibles para el usuario. Si no quedan más problemas a solucionar, se desinscribre al usuario del curso.
    //  *        Devuelve 'true' si se ha encontrado el problema en el curso y 'false' si no sse ha encontrado.
    //  */
    // bool update_problems(const problemid& pid, const bool& solved);

};

/**
 * @brief Función con el propósito de ordenar un vector de 'ProblemData' crecientemente según el 'problemid'.
 *        Se utiliza exclusivamente el la función 'sort()' de la libreria '<algorithm>'.
 * @param a objeto del tipo 'ProblemData'.
 * @param b objeto del tipo 'ProblemData'.
 * @return true si a < b y false para el resto de casos.
 */
bool sort_vect(ProblemData& a, ProblemData& b);

/** @brief Funcion que inserta en un vector los problemas a solucionar de un árbol de 'ProblemData'.
 *  @param problemTree árbol binario de objetos del tipo 'BinTree<ProblemData>'. 
 *  @param problemVector vector al que se le insertan los problemas disponibles a solucionar. Tipo de objeto 'vector<ProblemData>'.
 *  \pre Al menos hay un nodo, el árbol no está vacío.
 *  \post Devuelve los elementos no solucionados adyacenetes a nodos solucionados, los inserta en el parámetro 'problemVector'.
 *  @return void
 */
void get_session_available_problems(const BinTree<ProblemData>& problemTree, int& size, vector<ProblemData>& problemVector);

#endif
