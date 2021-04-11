#ifndef LABORATOR_POO_SALA_H
#define LABORATOR_POO_SALA_H
#include <string>
#include <iostream>

class muzeu;
class sala {

    int nr_exponate,etaj;
    std::string nume_sala;
	std::string *exponate; //numele obiectului expus
	std::string *date_exponate; //de la ce data se afla in muzeu
    bool stare; //deschisa sau inchisa-  ex: renovare (inchisa=0 , deschisa=1)
    int *preturi_exponate; //cu ce suma a fost cumparat

public:
    //constructor
    sala (std::string nume="-", int etaj=0);
    //destructor
    ~sala();
    //constructor de copiere
    sala (const sala &s);
    //operator =
    sala& operator=(const sala &s);

    void AdaugaExponat(std::string nume_exponate, std::string data_aducerii, int pret);
    //setteri
    void DeschideSala();
    void InchideSala();
    //getteri
    bool Stare();

    //overload <<
    friend std::ostream &operator << (std::ostream &out, const sala &S);
    friend std::istream &operator >> (std::istream &in, sala &S);
    friend class muzeu;


};


#endif //LABORATOR_POO_SALA_H
