#ifndef LABORATOR_POO_MUZEU_H
#define LABORATOR_POO_MUZEU_H
#include "sala.h"
#include <vector>
#include <string>
#include <unordered_map>
const int NRMAXSALI=7;
const int MAX_LENGTH_NAME=30;
using namespace std;

class muzeu {

    char nume[MAX_LENGTH_NAME];
    string ore_vizitare[7]; // la fiecare pozitie (zi a sapt)
    //e interval orar de genul 11-18 sau - daca nu se poate vizita in acea zi
    string adresa;
    int pret_zile[7];
    double feedback_score;
    //map cu nume personal; departament: nume; numele sunt retinute in vector de stringuri
    unordered_map<string, vector<string> > nume_personal;
    int nr_sali;

public:
    void AdaugaPersonal(string departament,string nume);
    void FeedbackScore();
    void AfiseazaPersonal();
    void AdaugaDepartament(string departament);
    int  PretZi(int nr_zi_saptamana);
    void StartTour(sala S[]);
    void ShowRoom(const int nsala, sala S[]);

    //overload >>
    friend istream &operator >> (istream &in, muzeu &M);
    //overload <<
    friend ostream &operator <<(ostream &out, const muzeu &M);
    //pentru a salva scorul dat de client
    friend class client;

};


#endif //LABORATOR_POO_MUZEU_H
