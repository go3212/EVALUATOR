/** @file problema.hh
 *  @brief Especificación de la clase 'Problema'.
 */

#ifndef PROBLEMA_HH
#define PROBLEMA_HH

#include <iostream>
#include <vector>
#include <string>
#include "tipos.hh"

using namespace std;

// N > 0, Sin repeticiones, 

/** @class Problema
 *  @brief Almacena la información de un problema y facilita su gestión.
 */
class Problema
{
private:
    problemid id;
    Attempts attempts;
public:
    /** @brief Overloaded default class constructor.
     *  \post Null problem identifier. All other private <em>int</em> variables are set to zero.
     */ 
    Problema();

    /** @brief Overloaded class constructor.
     *  \post Problem identifier ('this->id') set to the constructor parameter ('pid'). All other private <em>int</em> variables are set to zero.
     */ 
    Problema(const problemid& pid);

    /** @brief Actualiza el número de intentos al problema.
     *  @param solved valor que indica si el problema ha sido solucionado correctamente o no ('bool').
     *  \post Se incrementa el número de intentos totales en uno. En función de si se ha solucionado correctamente se increamentan los intentos correctos o los incorrectos.
     */
    void update_attempts(const bool& solved);

    /** @brief Devuelve los intentos del problema.
     *  \post Se devuelve por referencia un objeto 'Attempts' constante.
     */
    const Attempts& get_attempts() const;
};

#endif