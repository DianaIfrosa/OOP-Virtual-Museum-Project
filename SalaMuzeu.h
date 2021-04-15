#ifndef LABORATOR_POO_SALAMUZEU_H
#define LABORATOR_POO_SALAMUZEU_H
#include "sala.h"
#include <string>
#include <iostream>

class SalaMuzeu: public sala {

    int nr_exponate;
    std::string nume_sala;
	std::string *exponate; //numele obiectului expus
	std::string *date_exponate; //de la ce data se afla in muzeu
    int *preturi_exponate; //cu ce suma a fost cumparat

public:
    //constructor
    SalaMuzeu ();
    //destructor
    ~SalaMuzeu();
    //constructor de copiere
    SalaMuzeu (const SalaMuzeu &s);
    //operator =
    SalaMuzeu& operator=(const SalaMuzeu &s);

    void AdaugaExponat(std::string nume_exponate="-", std::string data_aducerii="-", int pret=0);
    void Renoveaza() override;

    //overload <<
    friend std::ostream &operator << (std::ostream &out, const SalaMuzeu &S);
    friend std::istream &operator >> (std::istream &in, SalaMuzeu &S);
    friend class muzeu;

};

#endif //LABORATOR_POO_SALAMUZEU_H
