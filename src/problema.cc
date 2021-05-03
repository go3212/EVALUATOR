#include "problema.hh"

Problema::Problema()
{

}

Problema::Problema(const problemid& pid)
{
    this->pid = pid;
}

void Problema::update_attempts(const bool& isSolved)
{
    attempts.update_attempts(isSolved);
}

const double Problema::ratio() const
{
    return (double)((double)(attempts.total + 1))/((double)(attempts.accepted + 1));
}

void Problema::write() const
{
    cout << pid << '(' << attempts.total << ',' << attempts.accepted;
    cout << ',' << ratio() << ')';
}