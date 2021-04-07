#ifndef SESION_HH
#define SESION_HH

#include <iostream>
#include <vector>
#include <string>
#include "hh/BinTree.hh"
#include "hh/problema.hh"

using namespace std;

// N > 0, Sin repeticiones, 

/** @class Session
 *  @brief Holds data for a session: session name ('name') and a binary tree of problems ('problems') 
 */

class Session
{
private:
    string name;
    int n_problems;
    BinTree<Problem> problems;

public:

    /** @brief Overloaded default class null constructor.
     *  \post Null session name. All other private variables are also undefined.
     */ 
    Session();

    /** @brief Overloaded class constructor.
     *  \post Sets the session name ('this->name') to the constructor parameter ('name'). All other private <em>int</em> variables are set to zero.
     */ 
    Session(const string& name);

};

#endif