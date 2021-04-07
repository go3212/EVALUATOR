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
    map<string, Problema> problemMap;
public:
    /** @brief Constructor por defecto de clase sobrecargado.
     *  \post Número total de problemas es cero. Conjunto de problemas ('problemMap') no definido.
     */ 
    Problemas();

    /** @brief Constructor de clase sobrecargado, añade un problema al instanciar la clase.
     *  @param id identificador del problema.
     *  @param problem objeto del tipo 'Problema'.
     *  \post Se añade un problema y se incializa el conjunto de problemas.
     */ 
    Problemas(const string& id, const Problema& problem);

    /** @brief Añade un nuevo problema a la lista de problemas.
     *  @param id identificador del problema.
     *  @param problem objeto de tipo 'Problema'.
     *  \post añade un problema al objeto 'Problemas' si no existia previamente. Devuelve si el problema se ha añadido ('true') o si ya existia ('false').
     */
    bool add_problem(const string& id, const Problema& problem);


};

#endif