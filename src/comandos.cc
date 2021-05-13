#include "comandos.hh"

using namespace std;

Comandos::Comandos(Usuarios& users, Cursos& courses, Problemas& problems, Sesiones& sessions) : users(users), courses(courses), problems(problems), sessions(sessions) {};

const vector<string> Comandos::errors = 
{
    "el problema ya existe",               //1
    "el problema no existe",               //2
    "el problema no pertenece al curso",   //3
    "la sesion ya existe",                 //4
    "la sesion no existe",                 //5
    "el curso no existe",                  //6
    "curso mal formado",                   //7
    "el usuario ya existe",                //8
    "el usuario no existe",                //9
    "usuario inscrito en otro curso",      //10
    "usuario no inscrito en ningun curso"  //11
};

const map<command, int> Comandos::commandsMap = 
{
    {"nuevo_problema", 1},
    {"np", 1},
    {"nueva_sesion", 2},
    {"ns", 2},
    {"nuevo_curso", 3},
    {"nc", 3},
    {"alta_usuario", 4},
    {"a", 4},
    {"baja_usuario", 5},
    {"b", 5},
    {"inscribir_curso", 6},
    {"i", 6},
    {"curso_usuario", 7},
    {"cu", 7},
    {"sesion_problema", 8},
    {"sp", 8},
    {"problemas_resueltos", 9},
    {"pr", 9},
    {"problemas_enviables", 10},
    {"pe", 10},
    {"envio", 11},
    {"e", 11},
    {"listar_problemas", 12},
    {"lp", 12},
    {"escribir_problema", 13},
    {"ep", 13},
    {"listar_sesiones", 14},
    {"ls", 14},
    {"escribir_sesion", 15},
    {"es", 15},
    {"listar_cursos", 16},
    {"lc", 16},
    {"escribir_curso", 17},
    {"ec", 17},
    {"listar_usuarios", 18},
    {"lu", 18},
    {"escribir_usuario", 19},
    {"eu", 19},
    {"fin", 20}
};

void Comandos::run()
{
    problemid pid; sessionid sid; courseid cid; userid uid; bool r;
    command com;
    int error = 0;
    
    bool end = false;
    while (!end)
    {
        cin >> com;
        if (com == "fin") break;
        cout << '#' << com;
        
        switch (commandsMap.find(com)->second)
        {
            case 1:
                cin >> pid; cout << ' ' << pid << endl;
                error = nuevo_problema(pid);
                break;
            case 2:
                cin >> sid; cout <<  ' ' << sid << endl;
                error = nueva_sesion(sid);
                break;
            case 3:
                cout << endl;
                error = nuevo_curso();
                break;
            case 4:
                cin >> uid; cout <<  ' ' << uid << endl;
                error = alta_usuario(uid);
                break;
            case 5:
                cin >> uid; cout <<  ' ' << uid << endl;
                error = baja_usuario(uid);
                break;
            case 6:
                cin >> uid >> cid; cout <<  ' ' << uid << ' ' << cid << endl;
                error = inscribir_curso(uid, cid);
                break;
            case 7:
                cin >> uid; cout <<  ' ' << uid << endl;
                error = curso_usuario(uid);
                break;
            case 8:
                cin >> cid >> pid; cout <<  ' ' << cid << ' ' << pid << endl;
                error = sesion_problema(cid, pid);
                break;
            case 9:
                cin >> uid; cout <<  ' ' << uid << endl;
                error = problemas_resueltos(uid);
                break;
            case 10:
                cin >> uid; cout <<  ' ' << uid << endl;
                error = problemas_enviables(uid);
                break;
            case 11:
                cin >> uid >> pid >> r; cout <<  ' ' << uid << ' ' << pid << ' ' << r << endl;
                error = envio(uid, pid, r);
                break;
            case 12:
                cout << endl;
                error = listar_problemas();
                break;
            case 13:
                cin >> pid; cout <<  ' ' << pid << endl;
                error = escribir_problema(pid);
                break;
            case 14:
                cout << endl;
                error = listar_sesiones();
                break;
            case 15:
                cin >> sid; cout <<  ' ' << sid << endl;
                error = escribir_sesion(sid);
                break;
            case 16:
                cout << endl;
                error = listar_cursos();
                break;
            case 17:
                cin >> cid; cout <<  ' ' << cid << endl;
                error = escribir_curso(cid);
                break;
            case 18:
                cout << endl;
                error = listar_usuarios();
                break;
            case 19:
                cin >> uid; cout <<  ' ' << uid << endl;
                error = escribir_usuario(uid);
                break;
        }
        if (error != 0) cout << "error: " << errors[error-1] << endl; 
    }
}

int Comandos::nuevo_problema(const problemid& pid)
{
    if(!problems.add_problem(pid)) return 1;
    cout << problems.get_number_of_problems() << endl;
    return 0;
}

int Comandos::nueva_sesion(const sessionid& sid)
{
    if(!sessions.add_session(sid)) return 4;
    cout << sessions.get_number_of_sessions() << endl;
    return 0;
}

int Comandos::nuevo_curso()
{
    Curso course; course.read();
    course.initialize_hintMap(sessions);
    if(!course.is_hintMap_initialized()) return 7;
    courses.add_course(course);
    cout << courses.get_number_of_courses() << endl;
    return 0;
}

int Comandos::alta_usuario(const userid& uid)
{
    if (!users.add_user(uid)) return 8;
    cout << users.get_number_of_users() << endl;
    return 0;
}

int Comandos::baja_usuario(const userid& uid)
{
    if (!users.delete_user(uid, courses)) return 9;
    cout << users.get_number_of_users() << endl;
    return 0;
}

int Comandos::inscribir_curso(const userid& uid, const courseid& cid)
{
    Usuario& user = users.get_user(uid);
    if(user.is_null()) return 9;
    Curso& course = courses.get_course(cid);
    if (course.is_null()) return 6;
    if (!user.inscribe(courses.get_course(cid), sessions)) return 10;
    cout << course.inscribed_users() << endl;
    return 0;
}

int Comandos::curso_usuario(const userid& uid)
{
    Usuario& user = users.get_user(uid);
    if (user.is_null()) return 9;
    cout << ((user.is_inscribed()) ? user.inscribed_course_id() : 0) << endl;
    return 0;
}

int Comandos::sesion_problema(const courseid& cid, const problemid& pid)
{
    Curso& course = courses.get_course(cid);
    if(course.is_null()) return 6;
    Problema& problem = problems.get_problem(pid);
    if(problem.is_null()) return 2;
    if(!course.is_hintMap_initialized()) course.initialize_hintMap(sessions);
    sessionid sid = course.get_problem_session(pid);
    if(sid == "0") return 3;
    cout << sid << endl;
    return 0;
}

int Comandos::problemas_resueltos(const userid& uid)
{
    Usuario& user = users.get_user(uid);
    if(user.is_null()) return 9;
    user.print_all_time_solved_problems();
    return 0;
}

int Comandos::problemas_enviables(const userid& uid)
{
    Usuario& user = users.get_user(uid);
    if(user.is_null()) return 9;
    if(!user.is_inscribed()) return 11;
    user.print_available_problems();
    return 0;    
}

int Comandos::envio(const userid& uid, const problemid& pid, const bool& solved)
{
    // Se garantiza que uid está inscrito y el problema pid pertenece a el curso al que uid esta inscrito
    // Además, u cumple los prerrequisitos de pid.
    UserMap::iterator userIter;
    ProblemMap::iterator problemIter;
    
    Usuario& user = users.get_user(uid);
    Problema& problem = problems.get_problem(pid);
    
    user.update_problem(pid, solved, courses);
    problem.update_problem(solved);
    return 0;
}

bool problemVectorSort(const ProblemMap::const_iterator& a, const ProblemMap::const_iterator& b)
{
    if (a->second.ratio() < b->second.ratio()) return true;
    else if (a->second.ratio() == b->second.ratio()) return (a->first < b->first);
    return false;
}

int Comandos::listar_problemas()
{
    ProblemMap::const_iterator beginIterator, endIterator;
    problems.get_iterators(beginIterator, endIterator);
    vector<ProblemMap::const_iterator> problemVector(problems.get_number_of_problems());
    int size = 0;
    while (beginIterator != endIterator)
    {
        problemVector[size] = beginIterator;
        ++size;
        ++beginIterator;
    }

    sort(problemVector.begin(), problemVector.end(), problemVectorSort);

    for (int i = 0; i < size; ++i) problemVector[i]->second.write(), cout << endl;
    return 0;
}

int Comandos::escribir_problema(const problemid& pid)
{
    Problema& problem = problems.get_problem(pid);
    if(problem.is_null()) return 2;
    problem.write(); cout << endl;
    return 0;
}

int Comandos::listar_sesiones()
{
    SessionMap::const_iterator beginIterator, endIterator;
    sessions.get_iterators(beginIterator, endIterator);

    while (beginIterator != endIterator)
    {
        (*beginIterator).second.write();
        cout << endl;
        ++beginIterator;
    }
    return 0;
}

int Comandos::escribir_sesion(const sessionid& sid)
{
    const Sesion& session = sessions.get_session(sid);
    if (session.is_null()) return 5;
    session.write(); cout << endl;
    return 0;
}

int Comandos::listar_cursos()
{
   CourseVector::const_iterator beginIterator, endIterator;
   courses.get_iterators(beginIterator, endIterator);
   while (beginIterator != endIterator)
   {
       (*beginIterator).write();
       cout << endl;
       ++beginIterator;
   }
   return 0;
}

int Comandos::escribir_curso(const courseid& cid)
{
    Curso& course = courses.get_course(cid);
    if(course.is_null()) return 6;
    course.write(); cout << endl;
    return 0;
}

int Comandos::listar_usuarios()
{
    UserMap::const_iterator beginIterator, endIterator;
    users.get_iterators(beginIterator, endIterator);
    while (beginIterator != endIterator)
    {
        (beginIterator->second).write();
        cout << endl; 
        ++beginIterator;
    }
    return 0;
}

int Comandos::escribir_usuario(const userid& uid)
{
    Usuario& user = users.get_user(uid);
    if(user.is_null()) return 9;
    user.write();  cout << endl;
    return 0;
}