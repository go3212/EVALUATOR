#include <iostream>
#include "hh/tipos.hh"
#include "hh/problemas.hh"
#include "hh/usuarios.hh"
#include "hh/cursos.hh"
#include "hh/comandos.hh"
#include "hh/timer.hh"

using namespace std;

int main ()
{
    Problemas problems; problems.read();
    Sesiones sessions; sessions.read();
    Cursos courses; courses.read();
    Usuarios users; users.read();
    
    Comandos commands(users, courses, problems, sessions);
    commands.run();

}