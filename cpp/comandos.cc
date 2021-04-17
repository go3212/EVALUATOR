#include "../hh/comandos.hh"

using namespace std;

Comandos::Comandos()
{
    set_default_commandsMap();
}

Comandos::Comandos(Usuarios& users, Cursos& courses, Problemas& problems, Sesiones& sessions)
{
    Usuarios* users_p = &(this->users);
    Cursos* courses_p = &(this->courses);
    Problemas* problems_p = &(this->problems);
    Sesiones* sessions_p = &(this->sessions);

    *users_p = users;
    *courses_p = courses;
    *problems_p = problems;

    set_default_commandsMap();
}

const bool Comandos::run()
{
    problemid pid; sessionid sid; courseid cid; 
    userid uid;
    bool r;
    bool end = false;

    command com;
    while (!end)
    {
        cin >> com;
        cout << "command: " << com << "  int: " << commandsMap[com] << endl;
        switch (commandsMap[com])
        {
            case 1:
                cout << "#nuevo_problema" << endl;
                cin >> pid;
                nuevo_problema(pid);
                break;
            case 2:
                cout << "#nueva_sesion" << endl;
                cin >> sid;
                nueva_sesion(sid);
                break;
            case 3:
                cout << "#nuevo_curso" << endl;
                nuevo_curso();
                break;
            case 4:
                cout << "#alta_usuario" << endl;
                cin >> uid;
                alta_usuario(uid);
                break;
            case 5:
                cout << "#baja_usuario" << endl;
                cin >> uid;
                baja_usuario(uid);
                break;
            case 6:
                cout << "#inscribir_curso" << endl;
                cin >> uid >> cid;
                inscribir_curso(uid, cid);
                break;
            case 7:
                cout << "#curso_usuario" << endl;
                cin >> uid;
                curso_usuario(uid);
                break;
            case 8:
                cout << "#sesion_problema" << endl;
                cin >> cid >> pid;
                sesion_problema(cid, pid);
                break;
            case 9:
                cout << "#problemas_resueltos" << endl;
                cin >> uid;
                problemas_resueltos(uid);
                break;
            case 10:
                cout << "#problemas_enviables" << endl;
                cin >> uid;
                problemas_enviables(uid);
                break;
            case 11:
                cout << "#envio" << endl;
                cin >> uid >> pid >> r;
                envio(uid, pid, r);
                break;
            case 12:
                cout << "#listar_problemas" << endl;
                listar_problemas();
                break;
            case 13:
                cout << "#escribir_problema" << endl;
                cin >> pid;
                escribir_problema(pid);
                break;
            case 14:
                cout << "#listar_sesiones" << endl;
                listar_sesiones();
                break;
            case 15:
                cout << "#escribir_sesion" << endl;
                cin >> sid;
                escribir_sesion(sid);
                break;
            case 16:
                cout << "#listar_cursos" << endl;
                listar_cursos();
                break;
            case 17:
                cout << "#escribir_curso" << endl;
                cin >> cid;
                escribir_curso(cid);
                break;
            case 18:
                cout << "#listar_usuarios" << endl;
                listar_usuarios();
                break;
            case 19:
                cout << "#escribir_usuario" << endl;
                cin >> uid;
                escribir_usuario(uid);
                break;
            case 20:
                end = true;
                break;
            default:
                cout << "NOT REGISTERED /MAYBE -------- ";
                break;
        }
        
    }
    return end;
}

void Comandos::nuevo_problema(const problemid& pid)
{

}

void Comandos::nueva_sesion(const sessionid& sid)
{

}

void Comandos::nuevo_curso()
{

}

void Comandos::alta_usuario(const userid& uid)
{

}

void Comandos::baja_usuario(const userid& uid)
{

}

void Comandos::inscribir_curso(const userid& uid, const courseid& cid)
{

}

void Comandos::curso_usuario(const userid& uid)
{

}

void Comandos::sesion_problema(const courseid& cid, const problemid& pid)
{

}

void Comandos::problemas_resueltos(const userid& uid)
{

}

void Comandos::problemas_enviables(const userid& uid)
{

}

void Comandos::envio(const userid& uid, const problemid& pid, const bool& solved)
{

}

void Comandos::listar_problemas()
{
    map<problemid, Problema>::iterator myBeginIterator, myEndIterator;
    problems.get_iterators(myBeginIterator, myEndIterator);

    while (myBeginIterator != myEndIterator)
    {
        (myBeginIterator->second).write();
        cout << endl; 
        ++myBeginIterator;
    }
}

void Comandos::escribir_problema(const problemid& pid)
{

}

void Comandos::listar_sesiones()
{

}

void Comandos::escribir_sesion(const sessionid& sid)
{

}

void Comandos::listar_cursos()
{

}

void Comandos::escribir_curso(const courseid& cid)
{

}

void Comandos::listar_usuarios()
{
    map<userid, Usuario>::iterator myBeginIterator, myEndIterator;
    users.get_iterators(myBeginIterator, myEndIterator);

    while (myBeginIterator != myEndIterator)
    {
        (myBeginIterator->second).write();
        cout << endl; 
        ++myBeginIterator;
    }
}

void Comandos::escribir_usuario(const userid& uid)
{

}

const void Comandos::set_default_commandsMap()
{

    commandsMap["nuevo_problema"] = 1;
    commandsMap["np"] = 1;

    commandsMap["nueva_sesion"] = 2;
    commandsMap["ns"] = 2;
    
    commandsMap["nuevo_curso"] = 3;
    commandsMap["nc"] = 3;

    commandsMap["alta_usuario"] = 4;
    commandsMap["a"] = 4;

    commandsMap["baja_usuario"] = 5;
    commandsMap["b"] = 5;
    
    commandsMap["inscribir_curso"] = 6;
    commandsMap["i"] = 6;

    commandsMap["curso_usuario"] = 7;
    commandsMap["cu"] = 7;

    commandsMap["sesion_problema"] = 8;
    commandsMap["sp"] = 8;

    commandsMap["problemas_resueltos"] = 9;
    commandsMap["pr"] = 9;

    commandsMap["problemas_enviables"] = 10;
    commandsMap["pe"] = 10;

    commandsMap["envio"] = 11;
    commandsMap["e"] = 11;

    commandsMap["listar_problemas"] = 12;
    commandsMap["lp"] = 12;

    commandsMap["escribir_problema"] = 13;
    commandsMap["ep"] = 13;

    commandsMap["listar_sesiones"] = 14;
    commandsMap["ls"] = 14;

    commandsMap["escribir_sesion"] = 15;
    commandsMap["es"] = 15;

    commandsMap["listar_cursos"] = 16;
    commandsMap["ls"] = 16;

    commandsMap["escribir_curso"] = 17;
    commandsMap["ec"] = 17;

    commandsMap["listar_usuarios"] = 18;
    commandsMap["lu"] = 18;

    commandsMap["escribir_usuario"] = 19;
    commandsMap["eu"] = 19;

    commandsMap["fin"] = 20;
    //commandsMap[""] = 20;
}