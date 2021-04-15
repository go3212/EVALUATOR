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

    problems.write();
    sessions.write();

    // Lectura repositorio inicial de sesiones

    // Lectura conjunto inicial de cursos

    // Lectura usuarios iniciales

    // Lee comando

    /**
     * while (comando != 'fin')
     * {
     *      procesar comando
     *      leer comando
     * }
     * */
}