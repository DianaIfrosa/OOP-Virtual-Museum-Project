#ifndef LABORATOR_POO_CLIENT_VIP_H
#define LABORATOR_POO_CLIENT_VIP_H
#include "museum.h"
#include "client.h"

class client_VIP: public client{

public:
	~client_VIP() override=default;
	static void DonateMoney(museum &Muz, int val);
	static void DonateArt(int no_room, const std::string& name, const std::string& date, museum &M);

};

#endif //LABORATOR_POO_CLIENT_VIP_H
