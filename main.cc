#include <iostream>
#include "hh/tipos.hh"
#include "hh/problemas.hh"
#include "hh/usuarios.hh"
#include "hh/cursos.hh"
#include "hh/comandos.hh"

using namespace std;

int main ()
{
    Problemas problems; problems.read();
    Sesiones sessions; sessions.read();
    Cursos courses; courses.read();
    Usuarios users; users.read();

    /**
     * while (comando != 'fin')
     * {
     *      procesar comando
     *      leer comando
     * }
     * */
}