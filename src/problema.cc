#include "problema.hh"

ProblemData::ProblemData(const problemid& pid)
{
    solved = false;
    this->pid = pid;
}

ProblemData::ProblemData()
{
    solved = false;
}

bool ProblemData::solve(const bool& isSolved)
{
    solved = isSolved;
    attempts.update_attempts(isSolved);
    return solved;
}

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

void Problema::write() const
{
    cout << pid << '(' << attempts.total << ',' << attempts.accepted;
    cout << ',' << ratio() << ')';
}

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