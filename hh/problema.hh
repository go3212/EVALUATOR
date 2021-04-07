#ifndef PROBLEMA_HH
#define PROBLEMA_HH

#include <iostream>
#include <vector>
#include <string>

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

/** @class Problem
 *  @brief Class which stores problem's data.
 */
class Problem
{
private:
    string id;
    Attempts attempts;
public:
    /** @brief Overloaded default class constructor.
     *  \post Null problem identifier. All other private <em>int</em> variables are set to zero.
     */ 
    Problem();

    /** @brief Overloaded class constructor.
     *  \post Problem identifier ('this->id') set to the constructor parameter ('id'). All other private <em>int</em> variables are set to zero.
     */ 
    Problem(const string& id);
};

#endif