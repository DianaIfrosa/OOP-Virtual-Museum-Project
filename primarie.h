#ifndef LABORATOR_POO_PRIMARIE_H
#define LABORATOR_POO_PRIMARIE_H
#include <string>
#include <memory>

class primarie {
private:
	int fonduri_totale;
	std::shared_ptr<std::string> nume_primar;

public:
	explicit primarie(const int& fonduri_t=0,const int& fonduri_m=0,const std::string& nume_oras="",const std::string& primar="");
	virtual void Despre();

protected:
	std::shared_ptr<std::string> oras;
	int fonduri_muzeu;

};

#endif //LABORATOR_POO_PRIMARIE_H
