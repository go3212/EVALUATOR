#include "../hh/usuarios.hh"
#include "../hh/usuario.hh"

using namespace std;

Usuarios::Usuarios()
{
    userMap = UserMap();
    total = 0;
}

// Usuarios::Usuarios(const Usuario& user)
// {

// }

bool Usuarios::add_user (const userid& uid)
{
    UserMap::const_iterator myIter = userMap.find(uid);
    if (myIter == userMap.end())
    {
        //userMap.insert(UserMapPair(uid, Usuario(uid)));
        userMap[uid] = Usuario(uid);
        total += 1;
        return true;
    }
    return false;
}

bool Usuarios::delete_user(const userid& uid, Cursos& courses)
{
    UserMap::iterator myIter = userMap.find(uid);
    if (myIter == userMap.end()) return false;
    
    if ((*myIter).second.is_inscribed())
    {
        CourseVector::iterator courseIter;
        courses.get_course((*myIter).second.inscribed_course_id(), courseIter);
        (*courseIter).uninscribe_user();
    }
    userMap.erase(myIter);
    total -= 1;
    return true;
}

int Usuarios::get_number_of_users() const
{
    return total;
}

void Usuarios::get_iterators(UserMap::const_iterator& beginIterator, UserMap::const_iterator& endIterator) const
{
    beginIterator = userMap.begin();
    endIterator = userMap.end();
}

bool Usuarios::get_user(const userid& uid, UserMap::iterator& mapIter)
{
    mapIter = userMap.find(uid);
    if (mapIter == userMap.end()) return false;
    return true;
}

void Usuarios::read()
{
    int n; cin >> n;
    total = n;

    userid uid;
    while (n != 0)
    {   
        cin >> uid;
        userMap[uid] = Usuario(uid);
        --n;
    }
}