#ifndef LABORATOR_POO_SALA_H
#define LABORATOR_POO_SALA_H

class room {
protected:
	int floor;
	bool state; //inchisa=0 , deschisa=1
public:
	explicit room(int fl=0, bool st=true );
	virtual ~room()=default;

	//setters
	virtual void Close();
	void Open();

	//getter
	bool State() const;

	friend class museum;

};


#endif //LABORATOR_POO_SALA_H
