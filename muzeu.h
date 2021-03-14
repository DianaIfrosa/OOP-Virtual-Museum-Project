#ifndef LABORATOR_POO_MUZEU_H
#define LABORATOR_POO_MUZEU_H
#include <vector>
#include <string>
#include <map>
#define NRMAXSALI 7

using namespace std;

class muzeu {

    //date din fisier sau la initializare?
    char nume[30];
    string ore_vizitare[7]; // la fiecare pozitie (zi a sapt)
    //e interval orar de genul 11-18 sau - daca nu se poate vizita in acea zi
    string locatie;
    int pret_zile[7];
    int scor[10]; //fiecare sala are un punctaj rezultat din recenzii
    int nr_sali;
    int a[NRMAXSALI][NRMAXSALI]; //matrice adiacenta pentru graf sali
    //map cu nume personal; departament: nume; numele sunt retinute in vector de stringuri
     map <string, vector<string> > nume_personal;

public:
    void AdaugaPersonal(string,string);
    void AfiseazaPersonal();
    void AdaugaDepartament(string);
    int  PretZi(int nr_zi_saptamana);

    friend class client;

};


#endif //LABORATOR_POO_MUZEU_H
