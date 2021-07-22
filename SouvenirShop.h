#ifndef LABORATOR_POO_MAGAZINSUVENIRURI_H
#define LABORATOR_POO_MAGAZINSUVENIRURI_H

#include "room.h"
#include <vector>
#include <string>

class SouvenirShop:public room {

private:
	std::vector <std::pair<std::string,std::string>> items; //perechi obiect,pret
	SouvenirShop();
	static SouvenirShop* shop;

public:
	//singleton
	//cc si op= sterse
	SouvenirShop(const SouvenirShop&)=delete;
	SouvenirShop& operator=(const SouvenirShop&)=delete;

	static SouvenirShop* get_shop(){
		if(shop==nullptr)
			shop=new SouvenirShop;
		return shop;
	};

	void Close() override;
	void Visit();
	friend class museum;

};

#endif //LABORATOR_POO_MAGAZINSUVENIRURI_H
