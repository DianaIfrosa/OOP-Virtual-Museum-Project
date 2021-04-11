#ifndef LABORATOR_POO_MUZEU_H
#define LABORATOR_POO_MUZEU_H
#include "sala.h"
#include "primarie.h"
#include <vector>
#include <string>
#include <unordered_map>

const int NRMAXSALI=10;
const int MAX_LENGTH_NAME=30;

class muzeu: public primarie {

    char nume[MAX_LENGTH_NAME];
	std::string ore_vizitare[7]; // la fiecare pozitie (zi a sapt)
    //e interval orar de genul 11-18 sau - daca nu se poate vizita in acea zi
    std::string adresa;
    int pret_zile[7];
    double feedback_score;
    //map cu nume personal; departament: nume; numele sunt retinute in vector de stringuri
    std::unordered_map<std::string, std::vector<std::string> > nume_personal;
    int nr_sali;
    sala S[NRMAXSALI];

public:
    void AdaugaPersonal(std::string departament,std::string nume);
    void FeedbackScore();
    void AfiseazaPersonal();
    void AdaugaDepartament(std::string departament);
    int  PretZi(int nr_zi_saptamana);
    void StartTour();
    void ShowRoom(int nsala);
    void ReadRoomsData();

    //overload >>
    friend std::istream &operator >> (std::istream &in, muzeu &M);
    //overload <<
    friend std::ostream &operator <<(std::ostream &out, const muzeu &M);
    //pentru a salva scorul dat de client
    friend class client;
    friend class sala;

};


#endif //LABORATOR_POO_MUZEU_H
