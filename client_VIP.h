#ifndef LABORATOR_POO_CLIENT_VIP_H
#define LABORATOR_POO_CLIENT_VIP_H
#include "muzeu.h"
#include "client.h"

class client_VIP: public client{

public:
	~client_VIP() override=default;
	static void DoneazaBani(muzeu &Muz, int val);
	static void DoneazaArta(int nrsala, const std::string& nume, const std::string& data, muzeu &M);

};

#endif //LABORATOR_POO_CLIENT_VIP_H
