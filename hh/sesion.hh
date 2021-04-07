#ifndef SESION_HH
#define SESION_HH

#include <iostream>
#include <vector>
#include <string>
#include "hh/BinTree.hh"
#include "hh/problema.hh"

using namespace std;

// N > 0, Sin repeticiones, 

struct Session
{
    string nombre;
};

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


};

#endif