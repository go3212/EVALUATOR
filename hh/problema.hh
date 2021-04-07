#ifndef PROBLEMAS_HH
#define PROBLEMAS_HH

#include <iostream>
#include <vector>
#include <string>

using namespace std;

// N > 0, Sin repeticiones, 

/** @struct Attempts
 *  @brief Estructura que almacena el número de intentos.
 */
struct Attempts
{
    int accepted;
    int total;
    int rejected;
};

/** @class Problem
 *  @brief Clase que almancena toda la información de un problema: identificador, intentos y intentos correctos.
 */
class Problem
{
private:
    string id;
    Attempts attempts;
public:
    /** @brief
     *  \pre
     *  \post
     */ 


    /** @brief
     *  \pre
     *  \post
     */ 
    Problem();
};

#endif