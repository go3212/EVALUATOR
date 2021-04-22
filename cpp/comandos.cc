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
    *sessions_p = sessions;

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
        cout << '#' << com << ' ';
        //cout << "command: " << com << "  int: " << commandsMap[com] << endl;
        switch (commandsMap[com])
        {
            case 1:
                //cout << "#nuevo_problema" << endl;
                cin >> pid; cout << pid << endl;
                nuevo_problema(pid);
                break;
            case 2:
                //cout << "#nueva_sesion" << endl;
                cin >> sid; cout << sid << endl;
                nueva_sesion(sid);
                break;
            case 3:
                //cout << "#nuevo_curso" << endl;
                cout << endl;
                nuevo_curso();
                break;
            case 4:
                //cout << "#alta_usuario" << endl;
                cin >> uid; cout << uid << endl;
                alta_usuario(uid);
                break;
            case 5:
                //cout << "#baja_usuario" << endl;
                cin >> uid; cout << uid << endl;
                baja_usuario(uid);
                break;
            case 6:
                //cout << "#inscribir_curso" << endl;
                cin >> uid >> cid; cout << uid << ' ' << cid << endl;
                inscribir_curso(uid, cid);
                break;
            case 7:
                //cout << "#curso_usuario" << endl;
                cin >> uid; cout << uid << endl;
                curso_usuario(uid);
                break;
            case 8:
                //cout << "#sesion_problema" << endl;
                cin >> cid >> pid; cout << cid << ' ' << pid << endl;
                sesion_problema(cid, pid);
                break;
            case 9:
                //cout << "#problemas_resueltos" << endl;
                cin >> uid; cout << uid << endl;
                problemas_resueltos(uid);
                break;
            case 10:
                //cout << "#problemas_enviables" << endl;
                cin >> uid; cout << uid << endl;
                problemas_enviables(uid);
                break;
            case 11:
                //cout << "#envio" << endl;
                cin >> uid >> pid >> r; cout << uid << ' ' << pid << endl;
                envio(uid, pid, r);
                break;
            case 12:
                //cout << "#listar_problemas" << endl;
                cout << endl;
                listar_problemas();
                break;
            case 13:
                //cout << "#escribir_problema" << endl;
                cin >> pid; cout << pid << endl;
                escribir_problema(pid);
                break;
            case 14:
                //cout << "#listar_sesiones" << endl;
                cout << endl;
                listar_sesiones();
                break;
            case 15:
                //cout << "#escribir_sesion" << endl;
                cin >> sid; cout << sid << endl;
                escribir_sesion(sid);
                break;
            case 16:
                //cout << "#listar_cursos" << endl;
                cout << endl;
                listar_cursos();
                break;
            case 17:
                //cout << "#escribir_curso" << endl;
                cin >> cid; cout << cid << endl;
                escribir_curso(cid);
                break;
            case 18:
                //cout << "#listar_usuarios" << endl;
                cout << endl;
                listar_usuarios();
                break;
            case 19:
                //cout << "#escribir_usuario" << endl;
                cin >> uid; cout << uid << endl;
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
    if(problems.add_problem(pid))
    {
        cout << problems.get_number_of_problems();
    }
    else
    {
        cout << "error: el problema ya existe";
    }
    cout << endl;
}

void Comandos::nueva_sesion(const sessionid& sid)
{
    if(sessions.add_session(sid))
    {
        cout << sessions.get_number_of_sessions();
    }
    else
    {
        cout << "error: la sesion ya existe";
    }
    cout << endl;
}

void Comandos::nuevo_curso()
{
    Curso course; course.read();
    if(course.is_valid_course(sessions))
    {
        courses.add_course(course);
        cout << courses.get_number_of_courses();
    }
    else
    {
        cout << "error: el curso no es valido";
    }
    cout << endl;
}

void Comandos::alta_usuario(const userid& uid)
{
    if (users.add_user(uid))
    {
        cout << users.get_number_of_users();
    }
    else
    {
        cout << "error: el usuario ya existe";
    }
    cout << endl;
}

void Comandos::baja_usuario(const userid& uid)
{
    if (users.delete_user(uid))
    {
        cout << users.get_number_of_users();
    }
    else
    {
        cout << "error: el usuario no existe";
    }
    cout << endl;
}

void Comandos::inscribir_curso(const userid& uid, const courseid& cid)
{
    vector<Curso>::iterator courseIter;
    if(courses.get_course(cid, courseIter))
    {
        map<userid, Usuario>::iterator userIter;
        if(users.get_user(uid, userIter))
        {
            if ((*userIter).second.inscribe(cid))
            {
                (*courseIter).inscribe_user(uid);
                cout << (*courseIter).inscribed_users();
            } else cout << "error: usuario inscrito en otro curso";
        } else cout << "error: el usuario no existe";
    } else cout << "error: el curso no existe";
    cout << endl;
}

void Comandos::curso_usuario(const userid& uid)
{
    map<userid, Usuario>::iterator userIter;
    if (users.get_user(uid, userIter))
    {
        cout << (((*userIter).second.is_inscribed()) ? (*userIter).second.inscribed_course_id() : 0);
    } else cout << "error: el usuario no existe";
    cout << endl;
}

void Comandos::sesion_problema(const courseid& cid, const problemid& pid)
{
    bool found = false;
    vector<Curso>::iterator courseIter;
    map<problemid, Problema>::const_iterator problemIter;
    if(!problems.get_problem(pid, problemIter)) 
    {
        cout << "error: el problema no existe" << endl;
        return void();
    }
    if (courses.get_course(cid, courseIter))
    {
        map<sessionid, Sesion>::const_iterator sessionIter;
        vector<problemid> problemVect;
        vector<sessionid>::const_iterator courseIterBegin, courseIterEnd;
        (*courseIter).get_iterators(courseIterBegin, courseIterEnd);
        int n;
        while(!found && courseIterBegin != courseIterEnd)
        {
            sessions.get_session((*courseIterBegin), sessionIter);
            n = (*sessionIter).second.get_problems_as_vector(problemVect);
            for (int i = 0; i < n && !found; ++i)
            {
                if (problemVect[i] == pid) 
                {
                    found = true;
                    cout << (*sessionIter).second.session_id();
                }
            }
            ++courseIterBegin;
        }   
        if (!found) cout << "error: el problema no pertenece al curso";
    } else cout << "error: el curso no existe";
    cout << endl;
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
    map<problemid, Problema>::const_iterator myBeginIterator, myEndIterator;
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
    map<problemid, Problema>::const_iterator myIter;
    if(problems.get_problem(pid, myIter))
    {
        (*myIter).second.write();
    }
    else
    {
        cout << "error: el problema no existe";
    }
    cout << endl;
}

void Comandos::listar_sesiones()
{
    map<sessionid, Sesion>::const_iterator myBeginIterator, myEndIterator;
    sessions.get_iterators(myBeginIterator, myEndIterator);

    while (myBeginIterator != myEndIterator)
    {
        (*myBeginIterator).second.write();
        cout << endl;
        ++myBeginIterator;
    }
}

void Comandos::escribir_sesion(const sessionid& sid)
{
    map<sessionid, Sesion>::const_iterator myIter;
    if (sessions.get_session(sid, myIter))
    {
        (*myIter).second.write();
    }
    else
    {
        cout << "error: la sesion no existe";
    }
    cout << endl;
}

void Comandos::listar_cursos()
{
   vector<Curso>::const_iterator myBeginIterator, myEndIterator;
   courses.get_iterators(myBeginIterator, myEndIterator);

   while (myBeginIterator != myEndIterator)
   {
       (*myBeginIterator).write();
       cout << endl;
       ++myBeginIterator;
   }
}

void Comandos::escribir_curso(const courseid& cid)
{
    vector<Curso>::iterator myIter;
    if(courses.get_course(cid, myIter))
    {
        (*myIter).write();
    }
    else
    {
        cout << "error: el curso no existe";
    }
    cout << endl;
}

void Comandos::listar_usuarios()
{
    map<userid, Usuario>::const_iterator myBeginIterator, myEndIterator;
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
    map<userid, Usuario>::iterator myIter;
    if(users.get_user(uid, myIter))
    {
        (*myIter).second.write();
    }
    else
    {
        cout << "error: el usuario no existe";
    }
    cout << endl;
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
    commandsMap["lc"] = 16;

    commandsMap["escribir_curso"] = 17;
    commandsMap["ec"] = 17;

    commandsMap["listar_usuarios"] = 18;
    commandsMap["lu"] = 18;

    commandsMap["escribir_usuario"] = 19;
    commandsMap["eu"] = 19;

    commandsMap["fin"] = 20;
    //commandsMap[""] = 20;
}