#ifndef SESION_HH
#define SESION_HH

#include <iostream>
#include <vector>
#include <string>
#include "hh/BinTree.hh"
#include "hh/problema.hh"

typedef string sessionid;

using namespace std;

// N > 0, Sin repeticiones, 

/** @class Session
 *  @brief Holds data for a session: session name ('name') and a binary tree of problems ('problems') 
 */

class Sesion
{
private:
    sessionid id;
    int n_problems;
    BinTree<problemid> problems;

public:

    /** @brief Overloaded default class null constructor.
     *  \post Null session name. All other private variables are also undefined.
     */ 
    Sesion();

    /** @brief Overloaded class constructor.
     *  \post Sets the session id ('this->id') to the constructor parameter ('sid'). All other private <em>int</em> variables are set to zero.
     */ 
    Sesion(const sessionid& sid);

};

#endif