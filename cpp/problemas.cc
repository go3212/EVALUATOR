#include "hh/problemas.hh"

using namespace std;

Problema::Problema()
{
    int n; cin >> n;
    problema = vector<string> (n);
    for (int i = 0; i < n; ++i) cin >> problema[i];
}