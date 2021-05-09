#include <iostream>
#include "src/tipos.hh"
#include "src/problemas.hh"
#include "src/usuarios.hh"
#include "src/cursos.hh"
#include "src/comandos.hh"
#include "src/timer.hh"

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
