#ifndef LABORATOR_POO_SALAMUZEU_H
#define LABORATOR_POO_SALAMUZEU_H
#include "sala.h"
#include <vector>
#include <string>
#include<tuple>
#include <iostream>

class SalaMuzeu: public sala {
    int nr_exponate;
    std::string nume_sala;
	std::vector <std::tuple<std::string,std::string,int> > exponate; //nume exponat,de la ce data se afla in muzeu,cu ce suma a fost cumparat

public:
    //constructor
    SalaMuzeu ();
    //destructor
    ~SalaMuzeu() override=default;

    void Inchide() override;

    //overload <<
    friend std::ostream &operator << (std::ostream &out, const SalaMuzeu &S);
    friend std::istream &operator >> (std::istream &in, SalaMuzeu &S);
    friend class muzeu;

};

#endif //LABORATOR_POO_SALAMUZEU_H
