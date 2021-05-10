#include "src/comandos.hh"

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
