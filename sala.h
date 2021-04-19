#ifndef LABORATOR_POO_SALA_H
#define LABORATOR_POO_SALA_H

class sala {
protected:
	int etaj;
	bool stare; //deschisa sau inchisa-  ex: renovare (inchisa=0 , deschisa=1)
public:
	explicit sala(int et=0, bool stare=true );
	virtual ~sala()=default;

	virtual void Inchide();
	void Deschide();

	//getteri
	bool Stare() const;

};


#endif //LABORATOR_POO_SALA_H
