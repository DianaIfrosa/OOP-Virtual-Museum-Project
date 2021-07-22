#ifndef LABORATOR_POO_SALAMUZEU_H
#define LABORATOR_POO_SALAMUZEU_H
#include "room.h"
#include <vector>
#include <string>
#include <tuple>
#include <iostream>

class MuseumRoom: public room {
    int number_exhibits;
    std::string name_room;
	std::vector <std::tuple<std::string,std::string,int> > exhibits; //nume exponat,de la ce data se afla in muzeu,cu ce suma a fost cumparat

public:
    //constructor
    MuseumRoom ();
    //destructor
    ~MuseumRoom() override=default;

    void Close() override;

    //overload <<
    friend std::ostream &operator << (std::ostream &out, const MuseumRoom &S);
    friend std::istream &operator >> (std::istream &in, MuseumRoom &S);
    friend class museum;

};

#endif //LABORATOR_POO_SALAMUZEU_H
