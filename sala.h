#ifndef LABORATOR_POO_SALA_H
#define LABORATOR_POO_SALA_H
#include <string>
#include <iostream>
using namespace std;

class sala {

    int nr_exponate,etaj;
    string nume_sala;
    string *exponate; //numele obiectului expus
    string *date_exponate; //de la ce data se afla in muzeu
    bool stare; //deschisa sau inchisa-  ex: renovare
    int *preturi_exponate; //cu ce suma a fost cumparat

public:
    //constructor
    sala(string nume="-", int etaj=0);
    //destructor
    ~sala();
    //constructor de copiere
    sala (const sala &s);
    //operator =
    sala operator=(const sala &s);

    void AdaugaExponat(string nume_exponate, string data_aducerii, int pret);
    //setteri
    void DeschideSala();
    void InchideSala();
    //getteri
    bool Stare();

    //overload <<
    friend ostream &operator << (ostream &out, const sala &S);
    friend istream &operator >> (istream &in, sala &S);

};


#endif //LABORATOR_POO_SALA_H
