//
// Created by Diana on 11.03.2021.
//

#ifndef LABORATOR_POO_MUZEU_H
#define LABORATOR_POO_MUZEU_H
#include <vector>
#include <string>
#include <map>

using namespace std;

class muzeu {

    //date din fisier sau la initializare?
    char nume[30];
    vector <string> ore_vizitare; // la fiecare pozitie (zi a sapt)
    //e interval orar de genul 11-18 sau - daca nu se poate vizita in acea zi
    string locatie;
    vector <int> pret_zile;

    int nr_sali;
    int a[100][100]; //matrice adiacenta pentru graf sali
    //map cu nume personal; departament: nume; numele sunt retinute in vector de stringuri
     map <string, vector<string> > nume_personal;
public:
    void AdaugaPersonal(string,string);
    void AfiseazaPersonal();
    void AdaugaDepartament(string);



};


#endif //LABORATOR_POO_MUZEU_H
