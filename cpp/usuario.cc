#include "../hh/usuario.hh"

using namespace std;

Usuario::Usuario()
{
    hasUserid = false;
}

Usuario::Usuario(const userid& uid)
{
    this->uid = uid;
    hasUserid = true;
    isInscribed = false;
}