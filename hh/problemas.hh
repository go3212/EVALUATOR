#ifndef PROBLEMAS_HH
#define PROBLEMAS_HH

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include "hh/problema.hh"

using namespace std;

class Problemas
{
private:
    int total;
    map<problemid, Problema> problemMap;
public:
    /** @brief Constructor por defecto de clase sobrecargado.
     *  \post Número total de problemas es cero. Conjunto de problemas ('problemMap') no definido.
     */ 
    Problemas();

    /** @brief Constructor de clase sobrecargado, añade un problema al instanciar la clase.
     *  @param pid identificador del problema ('problemid').
     *  @param problem objeto del tipo 'Problema'.
     *  \post Se añade un problema y se incializa el conjunto de problemas.
     */ 
    Problemas(const problemid& pid, const Problema& problem);

    /** @brief Añade un nuevo problema a la lista de problemas.
     *  @param pid identificador del problema ('problemid').
     *  @param problem objeto de tipo 'Problema'.
     *  \post añade un problema al objeto 'Problemas' si no existia previamente. Devuelve si el problema se ha añadido ('true') o si ya existia ('false').
     */
    bool add_problem(const problemid& pid, const Problema& problem);

    /** @brief Busca un problema en el conjunto de problemas.
     *  @param pid identificador de problema ('problemid').
     *  \post devuelve el objeto 'Problema' por referencia si se ha encontrado, en caso opuesto, devuelve NULL.
     */
    Problema& search_problem(const problemid& pid);

    /** @brief Función que busca problemas y devuelve un puntero.
     *  @param pid identificador de problema ('problemid').
     *  \post Devuelve un puntero al objeto 'Problema' buscado. Si no se ha encontrado, devuelve NULL. 
     */
    Problema& get_problem(const problemid& pid);

    /** @brief Función que actualiza el número de intentos a un problema.
     *  @param pid identificador de problema ('problemid').
     *  \post Devuelve 'true' si el problema a actualizar se ha encontrado y 'false' si no se ha encontrado.
     */
    bool updateProblemAttempt(const problemid& pid);
};

#endif