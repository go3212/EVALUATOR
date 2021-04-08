#ifndef PROBLEMA_HH
#define PROBLEMA_HH

#include <iostream>
#include <vector>
#include <string>

typedef string problemid;

using namespace std;

// N > 0, Sin repeticiones, 

/** @struct Attempts
 *  @brief Holds attempts data.
 */
struct Attempts
{
    int accepted;
    int total;
    int rejected;
};

/** @class Problema
 *  @brief Class which stores problem's data.
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
    void updateAttempts(const bool& solved);
};

#endif