#include <iostream>
#include "muzeu.h"
using namespace std;

int main()
{
    muzeu M;
    M.AdaugaDepartament("Curatenie");
    M.AdaugaDepartament("Management");
    M.AdaugaDepartament("Paza");
    M.AdaugaPersonal("Paza", "A");
    M.AdaugaPersonal("Management", "B");
    M.AfiseazaPersonal();


   return 0;


}


