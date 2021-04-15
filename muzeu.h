#ifndef LABORATOR_POO_MUZEU_H
#define LABORATOR_POO_MUZEU_H
#include "SalaMuzeu.h"
#include "MagazinSuveniruri.h"
#include "sala.h"
#include "primarie.h"
#include <vector>
#include <string>
#include <unordered_map>

const int NRMAXSALI=10;

class muzeu: public primarie {

private:
    std::string nume;
	std::string ore_vizitare[7]; // la fiecare pozitie (zi a sapt)
    //e interval orar de genul 11-18 sau - daca nu se poate vizita in acea zi
    std::string adresa;
    int pret_zile[7];
    double feedback_score;
    //map cu nume personal; departament: nume; numele sunt retinute in vector de stringuri
    std::unordered_map<std::string, std::vector<std::string> > nume_personal;

protected:
	int nr_sali;
	//de facut pointeri ??-------------------------------------------------------------
	SalaMuzeu S[NRMAXSALI];
	MagazinSuveniruri magS;

public:
	muzeu(const std::string& oras, const std::string& nume_primar,const int& fonduri_m,const int& fonduri_t);
    void AdaugaPersonal(const std::string& departament,const std::string& nume);
    void FeedbackScore();
    void AfiseazaPersonal();
    void AdaugaDepartament(const std::string& departament);

    void AdaugaExponat(int nr_sala, std::string nume_exponate="-", std::string data_aducerii="-", int pret=0);

    int  PretZi(int nr_zi_saptamana);
    void StartTour();
    void ShowRoom(int nsala);
    void ReadRoomsData();
    void Despre() override; //se suprascrie functia din clasa parinte
	void PrimesteDonatii(int valoare);

	//de modificat astfel incat sa nu am redundante metodele si pt mag si pt sala-------------------------------------------------------------
	void RenoveazaSala(int nrsala);
	void RenoveazaMagazin();
	//setteri
	void DeschideSala(int nr_sala);
	void DeschideMagazin();

    //overload >>
    friend std::istream &operator >> (std::istream &in, muzeu &M);
    //overload <<
    friend std::ostream &operator <<(std::ostream &out, const muzeu &M);

};

#endif //LABORATOR_POO_MUZEU_H
