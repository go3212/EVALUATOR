#include "problema.hh"

//########################//
//       Attempts         //
//########################//
Attempts::Attempts()
{
    total = 0;
    accepted = 0;
    rejected = 0;
}

bool Attempts::update_attempts(const bool& isCorrect)
{
    total += 1;
    if (isCorrect) accepted += 1;
    else rejected += 1;
    return isCorrect;
}

//########################//
//      ProblemData       //
//########################//
ProblemData::ProblemData()
{
    solved = false;
}

ProblemData::ProblemData(const problemid& pid)
{
    solved = false;
    this->pid = pid;
}

void ProblemData::make_attempt(const bool& isSolved)
{
    solved = isSolved;
    attempts.update_attempts(isSolved);
}

//########################//
//       Problema         //
//########################//
Problema::Problema()
{
    isNull = true;
}

Problema::Problema(const problemid& pid)
{
    this->pid = pid;
    isNull = false;
}

void Problema::update_problem(const bool& isSolved)
{
    attempts.update_attempts(isSolved);
}

bool Problema::is_null() const
{
    return isNull;
}

double Problema::ratio() const
{
    return (double)((double)(attempts.total + 1))/((double)(attempts.accepted + 1));
}

const Attempts& Problema::get_attempts() const
{
    return attempts;
}

void Problema::write() const
{
    cout << pid << '(' << attempts.total << ',' << attempts.accepted;
    cout << ',' << ratio() << ')';
}