#ifndef LABORATOR_POO_CLIENT_VIP_H
#define LABORATOR_POO_CLIENT_VIP_H
#include "muzeu.h"
#include "client.h"

class client_VIP: public client{

public:
	void DoneazaBani(muzeu &Muz, int val);
	void DoneazaArta(int nrsala, std::string nume, std::string data, muzeu &M);

};

#endif //LABORATOR_POO_CLIENT_VIP_H
