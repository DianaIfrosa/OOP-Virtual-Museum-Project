#ifndef LABORATOR_POO_CLIENT_H
#define LABORATOR_POO_CLIENT_H
#include <string>
#include <iostream>
using namespace std;

class client {

    string nume, prenume;
    string tip; //1- adult, 2-student, 3-child =>se acorda reduceri in functie de tip; adult->0%, 2->20%, 3->50%

public:
    //constructor
    client(string nume="-", string prenume="-", string tip="-");
    void Feedback();
    int Tip();
    friend ostream &operator<<(ostream &out, const client &C);
    friend istream &operator>>(istream &in, client &C);
    friend class sala;

};


#endif //LABORATOR_POO_CLIENT_H
