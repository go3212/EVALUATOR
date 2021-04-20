#include "../hh/problema.hh"

Problema::Problema()
{

}

Problema::Problema(const problemid& pid)
{
    this->pid = pid;
}

const void Problema::write() const
{
    cout << pid << '(' << attempts.total << ',' << attempts.accepted;
    cout << ',' << (attempts.total + 1)/(attempts.accepted + 1) << ')';
}