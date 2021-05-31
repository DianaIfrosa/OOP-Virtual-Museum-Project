#ifndef LABORATOR_POO_MAGAZINSUVENIRURI_H
#define LABORATOR_POO_MAGAZINSUVENIRURI_H

#include "sala.h"
#include <vector>
#include <string>

class MagazinSuveniruri:public sala {

	std::vector <std::pair<std::string,double>> obiecte; //perechi obiect,pret
	MagazinSuveniruri();
	static MagazinSuveniruri* mag;

public:
	//cc si op= sterse
	MagazinSuveniruri(const MagazinSuveniruri&)=delete;
	MagazinSuveniruri& operator=(const MagazinSuveniruri&)=delete;

	static MagazinSuveniruri* get_shop(){
		if(mag==nullptr)
			mag=new MagazinSuveniruri;
		return mag;
	};

	void Inchide() override;
	void Viziteaza(); //TO DO
	friend class muzeu;

};

#endif //LABORATOR_POO_MAGAZINSUVENIRURI_H
