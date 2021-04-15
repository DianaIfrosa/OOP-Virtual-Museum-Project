#ifndef LABORATOR_POO_MAGAZINSUVENIRURI_H
#define LABORATOR_POO_MAGAZINSUVENIRURI_H

#include "sala.h"
#include <vector>
#include <string>

class MagazinSuveniruri:public sala {

	std::vector <std::pair<std::string,double>> obiecte; //perechi obiect,pret

public:
	MagazinSuveniruri();
	void Renoveaza() override;
	void Viziteaza(); //TO DO
	friend class muzeu;

};

#endif //LABORATOR_POO_MAGAZINSUVENIRURI_H
