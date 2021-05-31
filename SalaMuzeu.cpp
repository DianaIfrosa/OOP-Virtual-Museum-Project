#include <string>
#include <iostream>

#include "SalaMuzeu.h"

using namespace std;

//constructor
SalaMuzeu::SalaMuzeu() : sala(){

	nr_exponate = 0;
}

ostream &operator<<(ostream &out, const SalaMuzeu &S) {
	out << "The room named " << S.nume_sala << " has " << S.nr_exponate << " exhibit(s) and is on floor " << S.etaj
	    << ".\n";
	return out;
}

istream &operator>>(istream &in, SalaMuzeu &S) {

	in >> S.nume_sala >> S.etaj;
	return in;
}
void SalaMuzeu::Inchide() {

	cout<<"This museum room has been closed!\n";
	stare=false;

}

